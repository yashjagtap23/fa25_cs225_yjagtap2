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


PuzzleState::PuzzleState() {
//for loops that go through and assign based onb number so 1-15 and then 0 at the end
    int count = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (count != 16) {
                myBoard[i][j] = count;
            } else {
                myBoard[i][j] = 0;
            }
            count++;
        }
    }
}
//default constructor which creates the solution state initially


//row major order 0 indexed s
PuzzleState::PuzzleState(const std::array<char, 16> state) {
    //take the input and convert it 
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            myBoard[i][j] = state[count];
            count++;
        }
    }

}

//convert puzle satate ingto a array 
std::array<char, 16> PuzzleState::asArray() const {
    std::array<char, 16> myArray;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            myArray[count] = myBoard[i][j];
            count++;
        }
    }

    return myArray;
}

//equal when value of each tile is the same
//simple for loop and iterate through and check? 
//first make sure the size is the same
//then u can use two nested loops to check 
bool PuzzleState::operator==(const PuzzleState &rhs) const {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rhs.myBoard[i][j] != myBoard[i][j]) {
                return false;
            }
        }
    }
    return true;
}
//same as aboce 
bool PuzzleState::operator!=(const PuzzleState &rhs) const {
    return !(*this == rhs);

}

//at the first diff (index i) return if A < B or vice versa if all equal then that mean return false since operator == would ve true so maybe check with that one first 
bool PuzzleState::operator<(const PuzzleState &rhs) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rhs.myBoard[i][j] != myBoard[i][j]) {
                if (myBoard[i][j] < rhs.myBoard[i][j]) {
                    return true;
                } 
            }
        }
    }
    return false;

}

//neighbor if invalid then all 0s
const PuzzleState PuzzleState::getNeighbor(Direction direction) const {

    return PuzzleState();
}

//all possible states from a single move 
std::vector<PuzzleState> PuzzleState::getNeighbors() const {

}

//manahttan thing cehck sassingment i think its jus abs of x diff - abs val of athe y diff 
int PuzzleState::manhattanDistance(const PuzzleState desiredState = PuzzleState()) const {

}

std::pair<int, int> PuzzleState::findMyBlankTile() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (myBoard[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}