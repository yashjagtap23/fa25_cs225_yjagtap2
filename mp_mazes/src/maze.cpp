/* Your code here! */
#include "maze.h"




SquareMaze::SquareMaze() {

}

void SquareMaze::makeMaze(int width, int height) {
    //make some rnadom maze 
    // use rand
    mazeHeight = height;
    mazeWidth = width;
    rightWalls.clear();
    downWAlls.clear();
    Direction dir = 0;
    // Direction dir2 = 1;
    for (int i = 0; i < height * width; i++) {
        rightWalls.push_back(true);
        downWAlls.push_back(true);
    }
    dset.addElements(mazeHeight * mazeWidth);

    // all the walls at first 
    //set em true in my vecs

    //direction = random will either be 0 or 1
   
    //lets say 1 is down and 0 is right
    //all cels are their own set
    //count the wall that are remove d
    int removedWallCount = 0;
    theIndex = myIndex(0, 0);
    while (removedWallCount < (mazeHeight * mazeWidth) - 1) {
        dir = std::rand() % 2;
        int x = std::rand() % mazeWidth;
        int y = std::rand() % mazeHeight;
        
        theIndex = myIndex(x, y);
        int nextIndex = 0;

        if (dir == 1) {
            if (y != mazeHeight - 1) {
                nextIndex = myIndex(x, y + 1);
            } else {
                continue;
            }
        } else if (dir == 0) {
            if (x != mazeWidth - 1) {
                nextIndex = myIndex(x + 1, y);
            } else {
                continue;
            }
        }
        if (dset.find(theIndex) != dset.find(nextIndex)) {
            setWall(x, y, dir, false);
            dset.setUnion(dset.find(theIndex), dset.find(nextIndex));
            removedWallCount++;
        }
    }
    //while until wallRemoved < total cells - 1
    //star randmwall and direction 
    //get neighbor right or down 

    //use finds to get roots and if they are diff then remove wall 
    // set wall false 
    // merge if we remove the walls w the setUnion 
    //wall removed count goes up one 
}

bool SquareMaze::canTravel(int x, int y, Direction dir) const {
    //check in bounds
    int theIndex = myIndex(x, y);
    if (x >= mazeWidth || y >= mazeHeight || x < 0 || y < 0) {
        return false;
    }

    if (dir == 2) {
        if (x - 1 >= 0) {
            int newIndex = myIndex(x - 1, y);
            return !rightWalls[newIndex];
        }
    }
    if (dir == 0) {
        if (x != mazeWidth - 1) {
            return !rightWalls[theIndex];
        }
        return false;
        
    }
    if (dir == 1) {
        if (y != mazeHeight - 1) {
            return !downWAlls[theIndex];
        }
        return false;
    }
    if (dir == 3) {
        if (y - 1 >= 0) {
            int newIndex = myIndex(x, y - 1);
            return !downWAlls[newIndex];
        }
    } 
    return false;
    //check in each direction if its in bounds and if their is a wall in the current cell
    // if right check if right wall
    // if there is a wall then no can go 

    //we only have right and down wall so go back one index to check for left and go up one to check for up ykwm
    //gotta check in bounds somehow tho niot sre yet 

    //return false or true dependednt on walls or not 

}

void SquareMaze::setWall(int x, int y, Direction dir, bool exists) {
 
    //if right and set the right wall approparieltuy 
    // if down and set the down wall approparieltuy 
    //if we are out bounds dont set

    if (x < mazeWidth && y < mazeHeight && x >= 0 && y >= 0) {
        int theIndex = myIndex(x, y);
        if (dir == 1) {
            if (y != mazeHeight - 1) {
                downWAlls[theIndex] = exists;
            }
        } else if (dir == 0) {
            if (x != mazeWidth - 1) {
                rightWalls[theIndex] = exists;
            }
        }
    }
}

std::vector<Direction> SquareMaze::solveMaze(int startX) {
    return std::vector<Direction>();
}

cs225::PNG *SquareMaze::drawMaze(int start) const {
    return nullptr;
}

cs225::PNG *SquareMaze::drawMazeWithSolution(int start) {
    return nullptr;
}

//use disjoint sets from part 1 to detecy cycles and see which ones are connected and which walls to rmmeve
int SquareMaze::myIndex(int x, int y) const {
    return (y*mazeWidth) + x;

}