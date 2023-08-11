#include "../include/mob.hpp"
#include "../include/libraries.hpp"


bool Base::readData(std::ifstream& fin){

    fin >> this->ID;
    if(!fin.good() && !fin.eof()){
        return fileNotOk(fin, "Error reading ID");
    }
    fin >> this->coords.x;
    if(!fin.good() && !fin.eof()){
        return fileNotOk(fin, "Error reading x coordinate");
    }
    fin >> this->coords.y;
    if(!fin.good() && !fin.eof()){
        return fileNotOk(fin, "Error reading y coordinate");
    }

    fin >> this->hitPoint;
    if(!fin.good() && !fin.eof()){
        return fileNotOk(fin, "Error reading hit points");
    }

    fin >> this->product;
    if(!fin.good() && !fin.eof()){
        return fileNotOk(fin, "Error reading hit points");
    }

    return true;
}

bool Base::writeData(std::ostream& fout){
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

    fout << "Product: " << product << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing product");
    }

    fout  <<"Coords: "  << coords.x << "   " << coords.y << endl;
    if(!fout.good()){
        return fileNotOk(fout, "Error writing coordinates");
    }
    fout << endl;

    return true;
}

bool Base::isProduct()
{
    if(this->product == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

char Base::getProduct()
{
    return this->product;
}
