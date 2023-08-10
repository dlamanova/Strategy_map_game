#include "../include/mob.hpp"
#include "../include/structures.hpp"
#include "../include/libraries.hpp"


int Mob::getID()
{
    return this->ID;
}

int Mob::getVelocity()
{
    return this->velocity;
}

int Mob::getAttackRange()
{
    return this->attackRange;
}

bool Mob::getIsEnemy()
{
    return this->isEnemy;
}

char Mob::getType()
{
    return this->type;
}

int Mob::getX()
{
    return this->coords.x;
}

int Mob::getY()
{
    return this->coords.y;
}

void Mob::setCoords(int x, int y)
{
    this->coords.x = x;
    this->coords.y = y;
}

bool Mob::readData(std::ifstream& fin)
{
    fin >> this->ID;
    if(!fin.good() && !fin.eof())
    {
        return fileNotOk(fin, "Error reading ID");
    }
    fin >> this->coords.x;
    if(!fin.good() && !fin.eof())
    {
        return fileNotOk(fin, "Error reading x coordinate");
    }
    fin >> this->coords.y;
    if(!fin.good()&& !fin.eof())
    {
        return fileNotOk(fin, "Error reading y coordinate");
    }

    fin >> this->hitPoint;
    if(!fin.good() && !fin.eof())
    {
        return fileNotOk(fin, "Error reading hit points");
    }
    return true;
}

void Mob::setIsEnemy(bool ie){
    this->isEnemy = ie;
};

bool Mob::writeData(std::ostream& fout){
    fout << "Type: " << type << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing type");
    }
    fout << "Is Enemy: " << isEnemy << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing isEnemy");
    }
    fout << "ID: " << ID << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing ID");
    }
    fout << "HP: " << hitPoint << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing hit points");
    }
    fout << "Velocity: " << velocity << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing velocity");
    }
    fout << "Cost: " << cost << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing cost");
    }
    fout << "Attack range: " << attackRange << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing attack range");
    }
    fout << "Build time: " << buildTime << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing build time");
    }

    fout  <<"Coords: "  << coords.x << "   " << coords.y << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing coordinates");
    }
    fout << endl;

    return true;
}

bool Mob::isProduct(){
    return false;
}

int Mob::attack()
{
    int dmg = 0;
    switch(this->type)
    {
        case A:
            dmg = attacks.archer;
        break;
        case B:
            dmg = attacks.base;
        break;
        case C:
            dmg = attacks.catapult;
        break;
        case K:
            dmg = attacks.knight;
        break;
        case P:
            dmg = attacks.pikeman;
        break;
        case R:
            dmg = attacks.ram;
        break;
        case S:
            dmg = attacks.swordsman;
        break;
        case W:
            dmg = attacks.worker;
        break;
        default:
            dmg = 0;
    }
    return dmg;
}