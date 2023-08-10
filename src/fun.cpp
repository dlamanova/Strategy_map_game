#include "../include/structures.hpp"
#include "../include/libraries.hpp"

void Attacks::setAttacks(int a, int b, int c, int k, int p, int r, int s, int w)
{
    archer = a;
    base = b;
    catapult = c;
    knight = k;
    pikeman = p;
    ram = r;
    swordsman = s;
    worker = w;
}

bool fileNotOk(std::ifstream& fin, std::string message)
{
    cerr<< message << endl;
    fin.ignore();
    fin.clear();
    fin.close();
    return false;
}
bool fileNotOk(std::ostream& fout, std::string message)
{
    cerr<< message << endl;
    fout.clear();
    return false;
}

bool fileNotOk(std::ofstream& fout, std::string message)
{
    cerr<< message << endl;
    fout.clear();
    fout.close();
    return false;
}

int makeCase(long int money)
{
    if(money < 100) return 1;
    else if(money >= 100 && money < 250) return 2;
    else if(money >= 250 && money < 400) return 3;
    else if(money >= 400 && money < 500) return 4;
    else if(money >= 500 && money < 800) return 5;
    else if(money >= 800) return 6;
    else
    {
        cerr << "Wrong amount of money!" << endl;
        return 0;
    }
}

double calculateDistance(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}