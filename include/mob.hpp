#pragma once
#include "libraries.hpp"
#include "structures.hpp"

/**
 * @class Mob
 * @brief Base class representing a mobile unit in the game.
 */
class Mob
{
protected:
    char type;          /**< Type of the mob. */
    bool isEnemy;       /**< Flag indicating if the mob is an enemy. */
    int ID;             /**< Unique identifier for the mob. */
    int hitPoint;       /**< Health points of the mob. */
    int velocity;       /**< Velocity of the mob. */
    int cost;           /**< Cost of the mob. */
    int attackRange;    /**< Attack range of the mob. */
    int buildTime;      /**< Build time for creating the mob. */
    Attacks attacks;    /**< Damage values taken by the mob. */
    Coordinates coords; /**< Coordinates of the mob. */
public:

    /**
     * @brief Constructor for the Mob class.
     * @param t Type of the mob.
     * @param id Unique identifier for the mob.
     * @param hp Health points of the mob.
     * @param v Velocity of the mob.
     * @param c Cost of the mob.
     * @param ar Attack range of the mob.
     * @param bt Build time for creating the mob.
     */
    Mob(char t, int id, int hp, int v, int c, int ar, int bt)
    : type(t), isEnemy(false), ID(id), hitPoint(hp), velocity(v), cost(c), attackRange(ar), buildTime(bt){
        attacks.setAttacks(0, 0, 0, 0, 0, 0, 0, 0);
        this->coords.x = 0;
        this->coords.y = 0;
    };

    /**
     * @brief Reads mob data from an input stream.
     * @param fin Input stream to read from.
     * @return True if data reading is successful, false otherwise.
     */
    virtual bool readData(std::ifstream&);

    /**
     * @brief Writes mob data to an output stream.
     * @param fin Output stream to write to.
     * @return True if data writing is successful, false otherwise.
     */
    virtual bool writeData(std::ostream&);

    /**
     * @brief Sets the enemy status of the mob.
     * @param enemy True if the mob is an enemy, false otherwise.
     */
    virtual void setIsEnemy(bool);

    /**
     * @brief Checks if the mob is a product of a base.
     * @return True if the mob is a product, false otherwise.
     */
    virtual bool isProduct();

    /**
     * @brief Sets the coordinates of the mob.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     */
    void setCoords(int x, int y);

    /**
     * @brief Performs an attack action.
     * @return The result of the attack action.
     */
    int attack();

    /**
     * @brief Gets the unique identifier of the mob.
     * @return The unique identifier.
     */
    int getID();

    /**
     * @brief Gets the velocity of the mob.
     * @return The velocity.
     */
    int getVelocity();

    /**
     * @brief Gets the attack range of the mob.
     * @return The attack range.
     */
    int getAttackRange();

    /**
     * @brief Gets the enemy status of the mob.
     * @return True if the mob is an enemy, false otherwise.
     */
    bool getIsEnemy();

    /**
     * @brief Gets the type of the mob.
     * @return The mob type.
     */
    char getType();

    /**
     * @brief Gets the X-coordinate of the mob.
     * @return The X-coordinate.
     */
    int getX();

    /**
     * @brief Gets the Y-coordinate of the mob.
     * @return The Y-coordinate.
     */
    int getY();

    /**
     * @brief Destructor for the Mob class.
     */
    virtual ~Mob() = default;
};

/**
 * @class Base
 * @brief Represents a base in the game.
 */
class Base : public Mob
{
    char product; /**< The product type of the base. */
    public:

    /**
     * @brief Constructor for the Base class.
     * @param fin Input stream to read from.
     */
    Base(std::ifstream& fin) : Mob(B, 0, 0, 0, 0, 0, 0), product(0)
    {
        readData(fin);
    };

    /**
     * @brief Reads base data from an input stream.
     * @param fin Input stream to read from.
     * @return True if data reading is successful, false otherwise.
     */
    bool readData(std::ifstream&) override;

    /**
     * @brief Writes base data to an output stream.
     * @param fin Output stream to write to.
     * @return True if data writing is successful, false otherwise.
     */
    bool writeData(std::ostream&) override;

    /**
     * @brief Checks if the mob is a product of a base.
     * @return True if the mob is a product, false otherwise.
     */
    bool isProduct() override;
};

/**
 * @class Knight
 * @brief Represents a knight unit in the game.
 */
class Knight : public Mob
{
    public:

    /**
     * @brief Constructor for the Knight class.
     * @param fin Input stream to read from.
     */
    Knight(std::ifstream& fin) : Mob(K, 0, 70, 5, 400, 1, 5)
    {
        readData(fin);
        attacks.setAttacks(35, 35, 35, 35, 35, 50, 35, 35);
    };
};

/**
 * @class Swordsman
 * @brief Represents a swordsman unit in the game.
 */
class Swordsman : public Mob
{
    public:

    /**
     * @brief Constructor for the Swordsman class.
     * @param fin Input stream to read from.
     */
    Swordsman(std::ifstream& fin) : Mob(S, 0, 60, 2, 250, 1, 3)
    {
        readData(fin);
        attacks.setAttacks(30, 30, 20, 30, 20, 30, 30, 30);
    };
};

/**
 * @class Archer
 * @brief Represents an archer unit in the game.
 */
class Archer : public Mob
{
    public:

    /**
     * @brief Constructor for the Archer class.
     * @param fin Input stream to read from.
     */
    Archer(std::ifstream& fin) : Mob(A, 0, 40, 2, 250, 5, 3)
    {
        readData(fin);
        attacks.setAttacks(15, 15, 10, 15, 10, 15, 15, 15);
    };
};

/**
 * @class Pikeman
 * @brief Represents a pikeman unit in the game.
 */
class Pikeman : public Mob
{
    public:

    /**
     * @brief Constructor for the Pikeman class.
     * @param fin Input stream to read from.
     */
    Pikeman(std::ifstream& fin) : Mob(P, 0, 50, 2, 200, 2, 3)
    {
        readData(fin);
        attacks.setAttacks(15, 10, 15, 35, 15, 10, 15, 15);
    };
};

/**
 * @class Ram
 * @brief Represents a ram unit in the game.
 */
class Ram : public Mob
{
    public:

    /**
     * @brief Constructor for the Ram class.
     * @param fin Input stream to read from.
     */
    Ram(std::ifstream& fin) : Mob(R, 0, 90, 2, 500, 1, 4)
    {
        readData(fin);
        attacks.setAttacks(10, 50, 10, 10, 10, 10, 10, 10);
    };
};

/**
 * @class Catapult
 * @brief Represents a catapult unit in the game.
 */
class Catapult : public Mob
{
    public:

    /**
     * @brief Constructor for the Catapult class.
     * @param fin Input stream to read from.
     */
    Catapult(std::ifstream& fin) : Mob(C, 0, 50, 2, 800, 7, 6)
    {
        readData(fin);
        attacks.setAttacks(40, 50, 40, 40, 40, 40, 40, 40);
    };
};

/**
 * @class Worker
 * @brief Represents a worker unit in the game.
 */
class Worker : public Mob
{
    public:

    /**
     * @brief Constructor for the Worker class.
     * @param fin Input stream to read from.
     */
    Worker(std::ifstream& fin) : Mob(W, 0, 20, 2, 100, 1, 2)
    {
        readData(fin);
        attacks.setAttacks(5, 1, 5, 5, 5, 5, 5, 5);
    };
};
