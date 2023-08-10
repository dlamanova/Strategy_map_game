#include "../include/game.hpp"
#include "../include/structures.hpp"

Game::Game(std::ifstream& fin)
{
    fin>>map;
    if(!fin.good()&& !fin.eof())
    {
        fileNotOk(fin, "Error reading ID");
    }
    //cout<<map;

    setMapSizeX(int(countX()));
    setMapSizeY(int(countY()));

    setMoney(0);
}

int Game::countY()
{
    return map.size();
}

int Game::countX()
{
    return map[0].size();
}

void Game::setMapSizeX(int x)
{
    this->mapSizeX = x;
}

void Game::setMapSizeY(int y)
{
    this->mapSizeY = y;
}

bool Game::readStatus(std::ifstream& fin)
{
    std::string line;

    fin >> this->money;
    if(!fin.good()&& !fin.eof())
    {
        return fileNotOk(fin, "Error reading ID");
    }
    int i = 0;
    while(getline(fin, line)){

        char enemy;
        fin >> enemy;
        if(!fin.good()&& !fin.eof())
        {
            return fileNotOk(fin, "Error reading ID");
        }
        char type;
        fin >> type;
        if(!fin.good()&& !fin.eof())
        {
            return fileNotOk(fin, "Error reading ID");
        }
        switch(type)
        {
            case A:
                mobs.push_back(std::unique_ptr<Mob>(new Archer(fin)));
            break;
            case C:
                mobs.push_back(std::unique_ptr<Mob>(new Catapult(fin)));
            break;
            case K:
                mobs.push_back(std::unique_ptr<Mob>(new Knight(fin)));
            break;
            case P:
                mobs.push_back(std::unique_ptr<Mob>(new Pikeman(fin)));
            break;
            case R:
                mobs.push_back(std::unique_ptr<Mob>(new Ram(fin)));
            break;
            case S:
                mobs.push_back(std::unique_ptr<Mob>(new Swordsman(fin)));
            break;
            case W:
                mobs.push_back(std::unique_ptr<Mob>(new Worker(fin)));
            break;
            default:
                mobs.push_back(std::unique_ptr<Mob>(new Base(fin)));
        }
        if(enemy == E)
        {
        mobs[i]->setIsEnemy(true);
        }
        ++i;
    }
    return true;
}

void Game::setMoney(long int money)
{
    this->money = money;
}

void Game::modifyMap(std::ifstream& fin)
{
    if(readStatus(fin)){
        for (const auto& it : mobs)
        {
            if(it->getIsEnemy())
            {
                if(it->getX() < mapSizeX && it->getY() < mapSizeY)
                {
                    map[it->getY()][it->getX()] = it->getType()+32;
                }
            }
            else
            {
                if(it->getX() < mapSizeX && it->getY() < mapSizeY)
                {
                    map[it->getY()][it->getX()] = it->getType();
                }
            }
        }
        //cout<<map;
    }
}

bool Game::isWorker()
{
    for(const auto& it : mobs)
    {
        if(it->getType() == W && !it->getIsEnemy()) return true;
    }
    return false;
}

bool Game::isSwordsman()
{
    for(const auto& it : mobs)
    {
        if(it->getType() == S && !it->getIsEnemy()) return true;
    }
    return false;
}

std::string Game::build() {
    std::string command = "";

    for (const auto& it : mobs) {
        int id = it->getID();
        command += std::to_string(id) + " B ";
        if (findMyBase() >= 0 && it->isProduct()) {
            command += createBuildCommand();
            return command;
        }
    }

    return command;
}

std::string Game::createBuildCommand() {
    long int mon = this->money;
    int cs = makeCase(mon);

    switch (cs) {
        case LESS_THAN_100:
            return "";
        case LESS_THAN_250:
            return "W";
        case LESS_THAN_400:
            return createWorkerSwordsmanArcher();
        case LESS_THAN_500:
            return createUnitBasedOnSize(4, "K", "A");
        case LESS_THAN_800:
            return createUnitBasedOnSize(6, "R", "A");
        default:
            return createUnitBasedOnSize(12, "R", "K");
    }
}

std::string Game::createWorkerSwordsmanArcher() {
    if (!isWorker()) return "W";
    if (!isSwordsman()) return "S";
    return "A";
}

std::string Game::createUnitBasedOnSize(int maxSize, const std::string& fallbackUnit, const std::string& finalUnit) {
    if (int(mobs.size()) <= maxSize) {
        if (!isWorker()) return "W";
        return finalUnit;
    } else {
        return fallbackUnit;
    }
}

int Game::findMyBase()
{
    for (const auto& it : mobs)
    {
        if(it->getType() == B && it->getIsEnemy() == false)
        {
            return it->getID();
        }
    }
    return -1;
}

Coordinates Game::findEnemyBase()
{
    Coordinates eBase = {-1, -1};
    for(const auto& it : mobs)
    {
        if(it->getType() == B && it->getIsEnemy() == true)
        {
            eBase = {it->getY(), it->getX()};
        }
    }
    if(eBase.x == -1 && eBase.y == -1)
    {
        for (int y = 0; y < mapSizeY; ++y) {
            for (int x = 0; x < mapSizeX; ++x) {
                if (map[y][x]=='2')
                {
                    eBase = {x, y};
                }
            }
        }
    }
    return eBase;
}

std::string Game::move(int id, int x, int y, int targetX, int targetY, int velocity)
{
    std::string command = "";
    Coordinates findCoords;

    findCoords = findEmptyPlace(x, y, targetX, targetY, velocity);

    if(findCoords.x != -1 && findCoords.y != -1)
    {
        command += std::to_string(id);
        command += " M ";
        command += std::to_string(findCoords.x);
        command += " ";
        command += std::to_string(findCoords.y);
        return command;
    }
    return command;
}

bool Game::addToCommands(int ID, int x, int y, int targetX, int targetY, int vel, std::vector<std::string> &comms)
{
    std::string command;
    command = move(ID, x, y, targetX, targetY, vel);
    if(!command.empty())
    {
        comms.push_back(command);
        return true;
    }
    return false;
}

// Generates commands based on the game state and outputs them to the specified output file stream.
void Game::makeCommands(std::ofstream& fout) {
    // Vector to store generated commands
    std::vector<std::string> comms;

    // Find player's base, enemy base, and mining location
    int idBase = findMyBase();
    Coordinates findCoords;
    Coordinates enemyBase = findEnemyBase();
    Coordinates mine = findMine();
    std::string command = "";

    // Generate a build command if player's base is available
    if (idBase >= 0)
    {
        command = build();
        if (!command.empty())
        {
            comms.push_back(command);
            command.erase();
        }
    }

    // Iterate through the player's units
    for (const auto& it : mobs)
    {
        if (!it->getIsEnemy() && it->getType() != B)
        {
            // Generate move commands for worker and combat units
            if (it->getType() == W)
            {
                addToCommands(it->getID(), it->getX(), it->getY(), mine.x, mine.y, it->getVelocity(), comms);
            }
            else if (it->getType() == C || it->getType() == R)
            {
                addToCommands(it->getID(), it->getX(), it->getY(), enemyBase.x, enemyBase.y, it->getVelocity(), comms);
            }
            else if (it->getType() != C && it->getType() != R && it->getType() != W)
            {
                // Generate attack and move commands for other units
                command = attack(it->getID(), it->getX(), it->getY(), it->getAttackRange());
                if (command.empty())
                {
                    findCoords = findUnit(it->getX(), it->getY(), it->getVelocity());
                    if (findCoords.x != -1 && findCoords.y != -1)
                    {
                        if (addToCommands(it->getID(), it->getX(), it->getY(), findCoords.x, findCoords.y, it->getVelocity() - 1, comms))
                        {
                            command = attack(it->getID(), it->getX(), it->getY(), it->getAttackRange());
                            if (!command.empty())
                            {
                                comms.push_back(command);
                                command.erase();
                            }
                        }
                    }
                }
                else
                {
                    comms.push_back(command);
                    command.erase();
                }
            }
            else
            {
                // Generate move command for other unit types
                command = move(it->getID(), it->getX(), it->getY(), enemyBase.x, enemyBase.y, it->getVelocity());
                if (!command.empty())
                {
                    comms.push_back(command);
                    command.erase();
                }
            }
        }
    }
    // Write generated commands to the output file
    for (const std::string& str : comms)
    {
        fout << str << endl;
    }
}

Coordinates Game::findUnit(int currentX, int currentY, int range)
{
    // Initialize coordinates for the nearest unit and set an initial minimum range
    Coordinates nearestUnit = {-1, -1};
    int minRange = std::numeric_limits<int>::max();

    // Iterate over the entire map to find valid units within the given range
    for (int y = 0; y < mapSizeY; ++y)
    {
        for (int x = 0; x < mapSizeX; ++x)
        {
            // Check if the current cell contains a valid unit to consider
            if ((x != currentX || y != currentY) &&
                map[y][x] != '0' && map[y][x] != '6' && map[y][x] != '9' &&
                map[y][x] != A && map[y][x] != B && map[y][x] != C &&
                map[y][x] != K && map[y][x] != S && map[y][x] != R &&
                map[y][x] != W && map[y][x] != P)
                {
                // Calculate the Manhattan distance between the current unit and the target cell
                int dystans = calculateDistance(currentX, currentY, x, y);

                // Update the nearestUnit and minRange if the unit is within range and closer than previous units
                if (range >= dystans  && range < minRange)
                {
                    minRange = dystans;
                    nearestUnit = {x, y};
                }
            }
        }
    }

    // Return the coordinates of the nearest valid unit within the specified range
    return nearestUnit;
}

Coordinates Game::findMine()
{
    Coordinates mine = {-1, -1};
    for (int y = 0; y < mapSizeY; ++y) {
        for (int x = 0; x < mapSizeX; ++x) {
            if (map[y][x]=='6')
            {
                mine = {x, y};
            }
        }
    }
    return mine;
}

// Generates an attack command based on the game state and target position.
std::string Game::attack(int id, int x, int y, int range)
{
    std::string command = "";
    Coordinates findCoords;
    int eId;

    // Attempt to find a valid enemy unit within the attack range
    findCoords = findUnit(x, y, range);

    if (findCoords.x < mapSizeX && findCoords.y < mapSizeY)
    {
        if (findCoords.x != -1 && findCoords.y != -1)
        {
            for (const auto& i : mobs)
            {
                if (i->getX() == findCoords.x && i->getY() == findCoords.y && i->getIsEnemy())
                {
                    eId = i->getID();
                    // Construct the attack command
                    command += std::to_string(id);
                    command += " A ";
                    command += std::to_string(eId);
                    return command;
                }
            }
        }
    }
    // If no valid enemy target found, return an empty command
    command.erase();
    return command;
}



Coordinates Game::findEmptyPlace(int currentX, int currentY, int targetX, int targetY, int range)
{
    // Initialize coordinates for the nearest empty place and set an initial minimum distance
    Coordinates nearestZero = {-1, -1};
    int distanceToTarget = calculateDistance(currentX, currentY, targetX, targetY);

    // Iterate over the entire map to find empty places within the specified range
    for (int y = 0; y < mapSizeY; ++y)
    {
        for (int x = 0; x < mapSizeX; ++x)
        {
            // Check if the current cell is empty (contains '0')
            if (map[y][x] == '0')
            {
                // Calculate the distance from the current unit to the empty cell
                int distanceFromCurrent = calculateDistance(currentX, currentY, x, y);

                // Check if the empty cell is within the given range
                if (distanceFromCurrent <= range)
                {
                    // Calculate the minimum remaining distance to the target
                    int minDistanceToTarget = distanceToTarget - distanceFromCurrent;

                    // Update nearestZero if this empty cell leads closer to the target
                    if (minDistanceToTarget > 0)
                    {
                        nearestZero = {x, y};
                        range = static_cast<int>(distanceFromCurrent);
                    }
                }
            }
        }
    }

    // Return the coordinates of the nearest empty place that leads closer to the target
    return nearestZero;
}
