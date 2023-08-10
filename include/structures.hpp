#pragma once
#include "libraries.hpp"

/**
 * @struct Coordinates
 * @brief Represents a 2D point with integer coordinates.
 */
struct Coordinates {
    int x; /**< The X-coordinate of the point. */
    int y; /**< The Y-coordinate of the point. */
};

/**
 * @struct Attacks
 * @brief Stores damage taken by various types of units.
 */
struct Attacks {
    int archer;     /**< Damage taken by archer. */
    int base;       /**< Damage taken by base. */
    int catapult;   /**< Damage taken by catapult. */
    int knight;     /**< Damage taken by knight. */
    int pikeman;    /**< Damage taken by pikeman. */
    int ram;        /**< Damage taken by ram. */
    int swordsman;  /**< Damage taken by swordsman. */
    int worker;     /**< Damage taken by worker. */

    /**
     * @brief Sets the damage taken by different unit types.
     * @param a Damage taken by archer.
     * @param b Damage taken by base.
     * @param c Damage taken by catapult.
     * @param k Damage taken by knight.
     * @param p Damage taken by pikeman.
     * @param r Damage taken by ram.
     * @param s Damage taken by swordsman.
     * @param w Damage taken by worker.
     */
    void setAttacks(int a, int b, int c, int k, int p, int r, int s, int w);

    /**
     * @brief Default constructor. Initializes all damage values to 0.
     */
    Attacks(): archer(0), base(0), catapult(0), knight(0), pikeman(0), ram(0), swordsman(0), worker(0) {};
};

/**
 * @enum TYPE
 * @brief Enumerates different types of units using character codes.
 */
enum TYPE
{
    A = 65, /**< Archer type. */
    B = 66, /**< Base type. */
    C = 67, /**< Catapult type. */
    E = 69, /**< Empty type. */
    K = 75, /**< Knight type. */
    P = 80, /**< Pikeman type. */
    R = 82, /**< Ram type. */
    S = 83, /**< Swordsman type. */
    W = 87  /**< Worker type. */
};

/**
 * @enum MONEY
 * @brief Enumerates different money ranges for classification.
 */
enum MONEY
{
    LESS_THAN_100 = 1, /**< Money less than 100. */
    LESS_THAN_250 = 2, /**< Money less than 250. */
    LESS_THAN_400 = 3, /**< Money less than 400. */
    LESS_THAN_500 = 4, /**< Money less than 500. */
    LESS_THAN_800 = 5, /**< Money less than 800. */
    MORE_THAN_800 = 6  /**< Money more than 800. */
};

/**
 * @brief Checks if an input file stream is in a good state.
 * @param fin Input file stream to check.
 * @param message Error message to display if the stream is not in a good state.
 * @return True if the file stream is not good, false otherwise.
 */
bool fileNotOk(std::ifstream& fin, std::string message);

/**
 * @brief Checks if an output stream is in a good state.
 * @param fin Output stream to check.
 * @param message Error message to display if the stream is not in a good state.
 * @return True if the output stream is not good, false otherwise.
 */
bool fileNotOk(std::ostream& fin, std::string message);

/**
 * @brief Determines the case based on the amount of money.
 * @param money The amount of money.
 * @return Case value based on the MONEY enumeration.
 */
int makeCase(long int money);

/**
 * @brief Calculates the Euclidean distance between two points.
 */
double calculateDistance(int x1, int y1, int x2, int y2);
