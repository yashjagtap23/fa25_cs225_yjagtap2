/* Your code here! */
#include "maze.h"




SquareMaze::SquareMaze() {

}

void SquareMaze::makeMaze(int width, int height) {
    //make some rnadom maze 
    // use rand
    // all the walls at first 
    //set em true in my vecs


    //direction = random will either be 0 or 1
    int dir = std::rand() % 2;
    //lets say 1 is down and 0 is right
    //all cels are their own set
    //count the wall that are remove d
    //while until wallRemoved < total cells - 1
    //star randmwall and direction 
    //get neighbor right or down 

    //use finds to get roots and if they are diff then remove wall 
    // set wall false 
    // merge if we remove the walls w the setUnion 
    //wall removed count goes up one 
}

bool SquareMaze::canTravel(int x, int y, Direction dir) const {
    return true;
    //check in bounds

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