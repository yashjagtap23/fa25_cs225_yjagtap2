/* Your code here! */
#include "maze.h"
#include <queue>



SquareMaze::SquareMaze() {

}

void SquareMaze::makeMaze(int width, int height) {
    //make some rnadom maze 
    // use rand
    mazeHeight = height;
    mazeWidth = width;
    rightWalls.clear();
    downWAlls.clear();
    Direction dir = (Direction)(0);
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
    int theIndex = myIndex(0, 0);
    while (removedWallCount < (mazeHeight * mazeWidth) - 1) {
        dir = (Direction)(std::rand() % 2);
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
        return false;
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
        return false;
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
    std::vector<int> visitedDistances(mazeHeight * mazeWidth, -1);
    //-1 might be wrong but we ball
    Direction fixedDir = (Direction)(-1);
    std::vector<Direction> backwardsPathingSol(mazeHeight * mazeWidth, fixedDir);
    std::queue<int> myql;

    int myX = myBFSThing(startX, mazeWidth, mazeHeight, visitedDistances, backwardsPathingSol);//call helper here for my bfs (starxX, w, h, visited, backwards);
    int finalIndex = myIndex(myX, mazeHeight - 1);
    std::vector<Direction> myFinalpath;
    int curIndex = finalIndex;
    

    while (curIndex != -1 && visitedDistances[curIndex] > 0) {
        //get the direction from backwardsPatjhing 
        Direction temp = backwardsPathingSol[curIndex];
        // Direction finalDir = (Direction)(-1);
       
        // if (temp == 0) {
        //     finalDir = (Direction)(2);
        // } else if (temp == 1) {
        //     finalDir = (Direction)(3);
        // } else if (temp == 2) {
        //     finalDir = (Direction)(0);
        // } else if (temp == 3) {
        //     finalDir = (Direction)(1);
        // }
        myFinalpath.insert(myFinalpath.begin(), temp);

        //right -> lef
        //up is bownd 
        //vice bersa and stuff'
        //insert at myFinalpath front 
        //push front
        curIndex = findPrevInd(curIndex, mazeWidth, mazeHeight, visitedDistances);//call my prev helper here to go backwards 
    }

    return myFinalpath;
}

cs225::PNG *SquareMaze::drawMaze(int start) const {
    //create new png 
    PNG finalOut = new PNG(mazeWidth*10 + 1, mazeHeight*10 + 1);
    HSLA w1(0, 0, 1);
    HSLA b1(0, 0, 0);
    //set dimensions of PNG (width*10+1,height*10+1)

    //borders black
    for (int i = 0; i < mazeWidth * 10 + 1; i++) {
        finalOut->getPixel(i, 0) = b1;
    }
    for (int j = 0; j < mazeHeight * 10 + 1; j++) {
        finalOut->getPixel(0, j) = b1;
    }
    //gap for start
    //((start*10)+1, 0) to ((start+1)*10-1, 0). [The gap is the pixels larger than start*10 and smaller than (start+1)*10 ]
    int startP = start * 10 + 1
    int endP = ((start + 1) * 10) - 1 
    for (int i = startP; i < endP; i++) {
        if (x < mazeWidth * 10 + 1) {
            finalOut->getPixel(i, 0) = w1;
        }
    }

    for (int i = 0; i < mazeHeight; i++) {
        for (int j = 0; j < mazeWidth; j++) {
            int daIndex = myIndex(j, i);

            if (downWAlls[daIndex]) {
                for (int l = 0; l <= 10; l++) {
                    finalOut->getPixel(j * 10 + l, (i + 1) * 10) = black;
                }
            }

            if (rightWalls[daIndex]) {
                for (int l = 0; l <= 10; l++) {
                    finalOut->getPixel((j + 1) * 10, i * 10 + l) = black;
                }
            }
        }
    }
    //drwaw walls 
    // return 
    return finalOut;
}

cs225::PNG *SquareMaze::drawMazeWithSolution(int start) {
    //png = draw maze
    HSLA w1(0, 0, 1);
    HSLA r1(0, 1.0, 0.5, 1.0);
    PNG *finalOut = drawMaze(start);
    std::vector<Direction> sol = solveMaze(startX);
    int currX = start * 10 + 5;
    int currY = 5;
    //get the solution 

    drawDaPath(finalOut, dir, currX, currY);
    

    //red white //start in middle
    //if example if start was 0 the start position of the solution is (5,5)
    //Each direction in the solution vector corresponds to a trail of 11 red pixels in the given direction. 
    // If the first step is downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA)
    //make helper forr this 

    //Make the exit by undoing the bottom wall of the destination square: call the destination maze coordinates (x,y),
    //  and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
    int eY = (currY - 5) / 10;
    int eX = (currX - 5) / 10;

    for (int i = 0; i < 10; i++) {
        finalOut->getPixel(eX * 10 + i, (eY + 1) * 10) = w1;
    }    //return the png 
    return finalOut;
}

//use disjoint sets from part 1 to detecy cycles and see which ones are connected and which walls to rmmeve
int SquareMaze::myIndex(int x, int y) const {
    return (y*mazeWidth) + x;

}

int SquareMaze::myBFSThing(int startX, int myX, int myY, std::vector<int>& visitedDistances, std::vector<Direction>& backwardsPathingSol) {
    std::queue<int> myQ;
    int startingindex = myIndex(startX, 0);
    myQ.push(startingindex);
    visitedDistances[startingindex] = 0;

    int myFinalX = startX;
    int maxD = 0;
    while (!myQ.empty()) {
        //dequeue current 
        int myCurrIndex = myQ.front();//dequeue 
        myQ.pop();
        int x = myCurrIndex % myX;
        int y =  myCurrIndex / myX;

        if (canTravel(x, y, (Direction)(0))) { 
            int nextX = x + 1;
            int nextY = y;
            int nextIndex = myIndex(nextX, nextY);

            if (visitedDistances[nextIndex] == -1) {
                visitedDistances[nextIndex] = 1 + visitedDistances[myCurrIndex];
                backwardsPathingSol[nextIndex] = (Direction)(0);
                myQ.push(nextIndex);

                if (nextY == mazeHeight - 1) {
                    //bootom row check here 
                    if (visitedDistances[nextIndex] > maxD) {
                        maxD = visitedDistances[nextIndex];
                        myFinalX = nextX;
                    } else if (visitedDistances[nextIndex] == maxD && nextX < myFinalX) {
                        myFinalX = nextX;
                    }
                    //check for max dis
                }
            }
        }
        if (canTravel(x, y, (Direction)(1))) { 
            int nextX = x;
            int nextY = y + 1;
            int nextIndex = myIndex(nextX, nextY);

            if (visitedDistances[nextIndex] == -1) {
                visitedDistances[nextIndex] = 1 + visitedDistances[myCurrIndex];
                backwardsPathingSol[nextIndex] = (Direction)(1);
                myQ.push(nextIndex);

                if (nextY == mazeHeight - 1) {
                    //bootom row check here 
                    if (visitedDistances[nextIndex] > maxD) {
                        maxD = visitedDistances[nextIndex];
                        myFinalX = nextX;
                    } else if (visitedDistances[nextIndex] == maxD && nextX < myFinalX) {
                        myFinalX = nextX;
                    }
                    //check for max dis
                }
            }
        }
        if (canTravel(x, y, (Direction)(2))) { 
            int nextX = x - 1;
            int nextY = y;
            int nextIndex = myIndex(nextX, nextY);

            if (visitedDistances[nextIndex] == -1) {
                visitedDistances[nextIndex] = 1 + visitedDistances[myCurrIndex];
                backwardsPathingSol[nextIndex] = (Direction)(2);
                myQ.push(nextIndex);

                if (nextY == mazeHeight - 1) {
                    //bootom row check here 
                    if (visitedDistances[nextIndex] > maxD) {
                        maxD = visitedDistances[nextIndex];
                        myFinalX = nextX;
                    } else if (visitedDistances[nextIndex] == maxD && nextX < myFinalX) {
                        myFinalX = nextX;
                    }
                    //check for max dis
                }
            }
        }
        if (canTravel(x, y, (Direction)(3))) { 
            int nextX = x;
            int nextY = y - 1; 
            
            int nextIndex = myIndex(nextX, nextY);

            if (visitedDistances[nextIndex] == -1) {
                visitedDistances[nextIndex] = 1 + visitedDistances[myCurrIndex];
                backwardsPathingSol[nextIndex] = (Direction)(3);
                myQ.push(nextIndex);

                if (nextY == mazeHeight - 1) {
                    //bootom row check here 
                    if (visitedDistances[nextIndex] > maxD) {
                        maxD = visitedDistances[nextIndex];
                        myFinalX = nextX;
                    } else if (visitedDistances[nextIndex] == maxD && nextX < myFinalX) {
                        myFinalX = nextX;
                    }
                    //check for max dis
                }
            }
        }
         // do other directions 
    }
    return myFinalX;
}

int SquareMaze::findPrevInd(int theIndex, int myX, int myY, std::vector<int>& visitedDistances) {
        int x = theIndex % myX;
        int y =  theIndex / myX;

        int findDist = visitedDistances[theIndex] - 1;
        if (x + 1 < mazeWidth) {
            int nexIn = myIndex(x + 1, y);
            if (visitedDistances[nexIn] == findDist && canTravel(x + 1, y, (Direction)(2))) {
                return nexIn;
            }
        } 
        if (y + 1 < mazeHeight) {
            int nexIn = myIndex(x, y + 1);
            if (visitedDistances[nexIn] == findDist && canTravel(x, y + 1, (Direction)(3))) {
                return nexIn;
            }
        }
        if (x - 1 >= 0) {
            int nexIn = myIndex(x - 1, y);
            if (visitedDistances[nexIn] == findDist && canTravel(x - 1, y, (Direction)(0))) {
                return nexIn;
            }
        }
        if (y - 1 >= 0) {
            int nexIn = myIndex(x, y - 1);
            if (visitedDistances[nexIn] == findDist && canTravel(x, y - 1, (Direction)(1))) {
                return nexIn;
            }
        }

        //this is for righbr 
        //check next x (x + 1)
        //check in bounds 
        //if next index is the findDist return the index of next 

        //repeat for other directions 

    return -1;
}

void SquareMaze::drawDaPath(PNG finalOut, Direction dir, int& currX, int& currY) {
    HSLA r1(0, 1.0, 0.5, 1.0);
    int myMapY = {0, 1, 0, -1};
    int myMapX = {1, 0, -1, 0};

    int dirY = myMapY[dir];
    int dirX = myMapX[dir];

    for (int i = 0; i <= 10; i++) {
        int amountX = currX * i * dirX;
        int amountY = currY * i * dirY;

        finalOut.getPixel(amountX, amountY) = r1;
    }

    currX = currX * 10;
    currY = currY * 10;
}