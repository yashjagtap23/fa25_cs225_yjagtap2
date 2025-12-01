/**
 * @file puzzle.cpp
 * Implementation of puzzle class.
 */
#include "puzzle.h"

#include <array>
#include <cstdint>
#include <functional>
#include <sstream>
#include <string>
#include <vector>


PuzzleState();
//default constructor which creates the solution state initially


//row major order 0 indexed s
PuzzleState(const std::array<char, 16> state);

//convert puzle satate ingto a array 

std::array<char, 16> asArray() const;

//equal when value of each tile is the same
//simple for loop and iterate through and check? 
//first make sure the size is the same
//then u can use two nested loops to check 
bool operator==(const PuzzleState &rhs) const;
//same as aboce 
bool operator!=(const PuzzleState &rhs) const;

//at the first diff (index i) return if A < B or vice versa if all equal then that mean return false since operator == would ve true so maybe check with that one first 
bool operator<(const PuzzleState &rhs) const;

//neighbor if invalid then all 0s
PuzzleState getNeighbor(Direction direction) const;

//all possible states from a single move 
std::vector<PuzzleState> getNeighbors() const;

//manahttan thing cehck sassingment i think its jus abs of x diff - abs val of athe y diff 
int manhattanDistance(const PuzzleState desiredState = PuzzleState()) const;