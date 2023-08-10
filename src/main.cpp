#include "../include/libraries.hpp"
#include "../include/game.hpp"
#include "../include/mob.hpp"

int main(int argc, const char* argv[])
{
    if(argc !=  4 && argc != 5)
    {
        cerr << "Invalid number of arguments. Pass /.name mapa.txt status.txt rozkazy.txt" << "\t" ;
        return 100;
    }

    int desiredTimeInSeconds = 5;

    if(argc == 5)
    {
        desiredTimeInSeconds = atoi(argv[4]);
    }
    auto startTime = std::chrono::steady_clock::now();

    std::ifstream map(argv[1]);
    if(!map.good())
    {
        cerr << "Error opening file mapa.txt " << "\t";
        map.ignore();
        map.clear();
        map.close();
        return 101;
    }

    std::ifstream status(argv[2]);
    if(!status.good())
    {
        cerr << "Error opening file status.txt " << "\t";
        status.ignore();
        status.clear();
        status.close();
        return 101;
    }

    std::ofstream commands(argv[3]);
    if(!commands.good())
    {
        cerr << "Error opening file rozkazy.txt " << "\t";
        commands.clear();
        commands.close();
        return 103;
    }

    while (true)
    {
        auto currentTime = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = currentTime - startTime;
        double elapsedTimeInSeconds = elapsed.count();

        if (elapsedTimeInSeconds >= desiredTimeInSeconds)
        {
            map.close();
            status.close();
            commands.close();
            break;
        }

    Game game(map);
    game.modifyMap(status);
    game.makeCommands(commands);

    map.close();
    status.close();
    commands.close();
    break;
    }

return 0;
}