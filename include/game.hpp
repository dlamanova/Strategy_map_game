#pragma once

#include "libraries.hpp"
#include "mob.hpp"

#define BUILD

/**
 * @brief The core Game class that manages the game environment, entities, and actions.
 */
class Game {
    long int money; /**< Current amount of in-game currency. */
    int mapSizeX; /**< X axe of map. */
    int mapSizeY; /**< Y axe of map. */
    std::vector<std::vector<char>> map; /**< The game map grid. */
    std::vector<std::unique_ptr<Mob>> mobs; /**< Collection of active game entities. */

public:
    /**
     * @brief Constructor that initializes the game state from a file stream.
     * @param fin Input file stream containing game state data.
     */
    Game(std::ifstream& fin);

    /**
     * @brief counts the number of columns
     */
    int countX();

    /**
     * @brief counts the number of rows
     */
    int countY();

    /**
     * @brief Set the amount of in-game currency.
     * @param money The new amount of in-game currency.
     */
    void setMoney(long int money);

    /**
     * @brief Set the X-lenght of the map.
     * @param x The new X-lenght of the map.
     */
    void setMapSizeX(int x);

    /**
     * @brief Set the Y-lenght of the map.
     * @param y The new Y-lenght of the map.
     */
    void setMapSizeY(int y);

    /**
     * @brief Read and update the game status from a file stream.
     * @param fin Input file stream containing updated game status.
     * @return True if the status was successfully read, false otherwise.
     */
    bool readStatus(std::ifstream& fin);

    /**
     * @brief Modify the game map based on information from a file stream.
     * @param fin Input file stream containing map modification data.
     */
    void modifyMap(std::ifstream& fin);

    /**
     * @brief Generate commands for game actions and write them to an output file stream.
     * @param fout Output file stream to write commands.
     */
    void makeCommands(std::ofstream& fout);

    /**
     * @brief Find the base location of the player.
     * @return The index of the player's base location on the map.
     */
    int findMyBase();

    /**
     * @brief Find the mine location of the map.
     * @return The coordinates of the mine location on the map.
     */
    Coordinates findMine();

    /**
     * @brief Find the enemy base location of the map.
     * @return The coordinates of the enemy base location on the map.
     */
    Coordinates findEnemyBase();

    /**
     * @brief Check if a mob is a worker.
     * @return True if the mob is a worker, false otherwise.
     */
    bool isWorker();

    /**
     * @brief Check if a mob is a swordsman.
     * @return True if the mob is a swordsman, false otherwise.
     */
    bool isSwordsman();

    /**
     * @brief Find the coordinates of a specific unit within a radius.
     * @param currentX Current X coordinate.
     * @param currentY Current Y coordinate.
     * @param radius The search radius.
     * @return Coordinates of the found unit, or (-1, -1) if not found.
     */
    Coordinates findUnit(int currentX, int currentY, int radius);

    /**
     * @brief Find an empty place within a specified range, considering a target destination.
     * @param currentX Current X coordinate.
     * @param currentY Current Y coordinate.
     * @param targetX Target X coordinate.
     * @param targetY Target Y coordinate.
     * @param range The search range.
     * @return Coordinates of an empty place, or (-1, -1) if not found.
     */
    Coordinates findEmptyPlace(int currentX, int currentY, int targetX, int targetY, int range);

    /**
     * @brief Generates a build command based on the current game state.
     * Iterates through non-enemy mobs, checks their eligibility to build units,
     * and constructs the appropriate build command if conditions are met.
     * @return The constructed build command string or an empty string if no command is to be issued.
     */
    std::string createBuildCommand();

    /**
     * @brief Determines the specific type of unit to build based on the current money and mob count.
     * Chooses a build strategy by evaluating the available money and mob count,
     * then delegates to helper functions to make the appropriate decision.
     * @return The command string representing the chosen unit to build, or an empty string if no unit is to be built.
     */
    std::string createWorkerSwordsmanArcher();

    /**
     * @brief Decides which type of unit to build based on the total mob count and a maximum limit.
     * Evaluates the mob count and worker availability, then determines whether to build
     * the final unit type or the fallback unit type.
     * @param maxSize The maximum mob count for determining the unit type.
     * @param fallbackUnit The unit type to build when mob count is above maxSize.
     * @param finalUnit The unit type to build when mob count is below or equal to maxSize.
     * @return The command string representing the chosen unit to build (W, finalUnit, or fallbackUnit).
     */
    std::string createUnitBasedOnSize(int maxSize, const std::string& fallbackUnit, const std::string& finalUnit);

    /**
     * @brief Adds a unit movement command to the list of commands.
    * Generates a movement command for the specified unit to move from its current position
    * to the given target position with the specified velocity, and appends the command to the provided command vector.
    */
    bool addToCommands(int ID, int x, int y, int targetX, int targetY, int vel, std::vector<std::string> &coms);

    /**
     * @brief Initiate the construction of a new structure.
     * @return A string representing the construction command.
     */
    std::string build();

    /**
     * @brief Command a mob to move to a specified location with given parameters.
     * @param id ID of the mob.
     * @param x Current X coordinate.
     * @param y Current Y coordinate.
     * @param targetX Target X coordinate.
     * @param targetY Target Y coordinate.
     * @param velocity Movement velocity.
     * @return A string representing the movement command.
     */
    std::string move(int id, int x, int y, int targetX, int targetY, int velocity);

    /**
     * @brief Command a mob to attack a target location within a certain range.
     * @param id ID of the mob.
     * @param x Current X coordinate.
     * @param y Current Y coordinate.
     * @param range Attack range.
     * @return A string representing the attack command.
     */
    std::string attack(int id, int x, int y, int range);

    /**
     * @brief Overloaded stream extraction operator for vector input.
     * @tparam T Type of vector elements.
     * @param in Input stream.
     * @param v Vector to populate.
     * @return Reference to the input stream after extraction.
     */
    template<typename T>
    friend std::istream& operator>>(std::istream& in, std::vector<T>& v);

    /**
     * @brief Overloaded stream extraction operator for vector of vectors input.
     * @tparam T Type of vector elements.
     * @param in Input stream.
     * @param v Vector of vectors to populate.
     * @return Reference to the input stream after extraction.
     */
    template<typename T>
    friend std::istream& operator>>(std::istream& in, std::vector<std::vector<T>>& v);

    /**
     * @brief Overloaded stream insertion operator for vector output.
     * @tparam T Type of vector elements.
     * @param out Output stream.
     * @param v Vector to output.
     * @return Reference to the output stream after insertion.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, const std::vector<T>& v);

    /**
     * @brief Overloaded stream insertion operator for vector of vectors output.
     * @tparam T Type of vector elements.
     * @param out Output stream.
     * @param v Vector of vectors to output.
     * @return Reference to the output stream after insertion.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v);
};

template<typename T>
std::istream &operator>>(std::istream &in, std::vector<T> &v)
{
    std::copy(std::istream_iterator<T>(in), std::istream_iterator<T>(), std::back_inserter(v));
    return in;
}

template<typename T>
std::istream &operator>>(std::istream &in, std::vector<std::vector<T> > &v)
{
    for (std::string line; std::getline(in, line);)
    {
        std::istringstream iss(line);
        std::vector<T> row;
        iss >> row;
        v.push_back(row);
    }
    return in;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &v)
{
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<T>(out, " "));
    return out;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<T> > &v)
{
    for (const auto &i : v)
    {
        out << i << '\n';
    }
    return out;
}