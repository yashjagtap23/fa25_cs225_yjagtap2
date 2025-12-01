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
                return false;
            }
        }
    }
    return false;

}

//neighbor if invalid then all 0s
const PuzzleState PuzzleState::getNeighbor(Direction direction) const {
    //get the blank tile place 
    std::pair<int, int> myPair = findMyBlankTile();
    std::pair<int, int> theSwappingOne;
    std::array<char, 16> blanks = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    if (direction == Direction::UP) {
        if (myPair.first == 3) {
            return PuzzleState(blanks);
        }
        theSwappingOne = {myPair.first + 1, myPair.second};
    } else if (direction == Direction::DOWN) {
        if (myPair.first == 0) {
            return PuzzleState(blanks);
        }
        theSwappingOne = {myPair.first - 1, myPair.second};
    } else if (direction == Direction::LEFT) {
        if (myPair.second == 3) {
            return PuzzleState(blanks);
        }
        theSwappingOne = {myPair.first, myPair.second + 1};
    } else {
        if (myPair.second == 0) {
            return PuzzleState(blanks);
        }
        theSwappingOne = {myPair.first, myPair.second - 1};
    }
    //get the tile the blank will swap with by looking at the direction and pisutin of the blank tile 
    //if we going down the tile to swap is the one above blank so blank would swap wit it 

    //check if its invalid or not (out of bounds ands tuff )
    //make a copy of the current puzzle state (i thin i will usea aa se helper for this)
    //make the change 
    const PuzzleState myPuzzleState = createMyCopyState(myPair.first, myPair.second, theSwappingOne.first, theSwappingOne.second);
    //return it 

    return myPuzzleState;
}

//all possible states from a single move 
std::vector<PuzzleState> PuzzleState::getNeighbors() const {
    std::vector<PuzzleState> myStates; 
    std::array<char, 16> blanks = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    PuzzleState blankOne = PuzzleState(blanks);

    PuzzleState temp; 

    temp = getNeighbor(Direction::UP);
    if (temp != blankOne) {
        myStates.push_back(temp);
    }
    temp = getNeighbor(Direction::DOWN);
    if (temp != blankOne) {
        myStates.push_back(temp);
    }
    temp = getNeighbor(Direction::LEFT);
    if (temp != blankOne) {
        myStates.push_back(temp);
    }
    temp = getNeighbor(Direction::RIGHT);
    if (temp != blankOne) {
        myStates.push_back(temp);
    }
   
    return myStates;
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

PuzzleState PuzzleState::createMyCopyState(int bR, int bC, int sR, int sC) const {
    //make the copied state here but with replacing the blank row and tr tc. 
    //call as array to get the current board
    std::array<char, 16> myArrayCopy = asArray();
    int bIndex = 4 * bR + bC;
    int sIndex = 4 * sR + sC;

    char temp = myArrayCopy[sIndex];

    myArrayCopy[sIndex] = myArrayCopy[bIndex];
    myArrayCopy[bIndex] = temp;

    return PuzzleState(myArrayCopy);
    //go through after calculating new index since we can jus stick w the 1d
    //polus we know its got to b 4x4
}