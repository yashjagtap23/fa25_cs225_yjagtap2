#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  //bfs first in first out 
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    //pushback
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    //push back to front
    work_list.push_front(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //pop front
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    //same s
    work_list.pop_front();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
    //same

  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
    //return front
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) : startingPoint(start),  myTolerance(tolerance), imageToTraverse(png), myFns(fns) {  
    /** @todo [Part 1] */
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(this, startingPoint, myTolerance, myFns);
    //call construcor to create iterator at first point for start 
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
    //call construcor to create iterator at one past end point 
    //how do we get to one past end? hmm .end() + 1 idk  
    // end is always null or sentinel or whatever so i think its fine rn 
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() : currentPoint(Point(0,0)), myImage(NULL)
  {
      //int lastCountNeighbor;
    /** @todo [Part 1] */
    //create work lisr annd add starting point
    // created visited
  }

  ImageTraversal::Iterator::Iterator(const ImageTraversal* png, const Point & start, double tolerance, TraversalFunctions fns) : work_list_(), visitedAlrdy(png->imageToTraverse.width(), std::vector<bool>(png->imageToTraverse.height(), false)), currentPoint(start), myImage(png), myFns(fns)  // dont need tolerance i think but not sure
  {
    myFns.add(work_list_, start);
    visitedAlrdy[start.x][start.y] = true;
    std::cout << "start" << start.x << ", " << start.y << std::endl;
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    
    //myFns.pop(work_list_);
    double theTol = myImage->myTolerance;
    const HSLAPixel& startingPixel = myImage->imageToTraverse.getPixel(myImage->startingPoint.x, myImage->startingPoint.y);
    //call FNS add pop peek here (will do dfs or bfs)
    if (!work_list_.empty()) {
      Point point2 = myFns.peek(work_list_);
      std::cout << "point2 processing" << point2.x << ", " << point2.y << std::endl;

      
        Point rightP(point2.x + 1, point2.y);
        bool heymama = (rightP.x < myImage->imageToTraverse.width() && (rightP.x >= 0)) && (rightP.y < myImage->imageToTraverse.height() && rightP.y >= 0);
        if (heymama && calculateDelta(startingPixel, myImage->imageToTraverse.getPixel(rightP.x, rightP.y)) <= theTol && //bound cont h
        (visitedAlrdy[rightP.x][rightP.y] == false)
        ){
          //good point 
          myFns.add(work_list_, rightP);
                std::cout << "added right" << rightP.x << ", " << rightP.y << std::endl;
          //visitedAlrdy[rightP.x][rightP.y] = true;
        }
        Point downP(point2.x, point2.y + 1);
        heymama = (downP.x < myImage->imageToTraverse.width() && (downP.x >= 0)) && (downP.y < myImage->imageToTraverse.height() && downP.y >= 0);
        if (heymama && calculateDelta(startingPixel, myImage->imageToTraverse.getPixel(downP.x, downP.y)) <= theTol && //bound cont h
        (visitedAlrdy[downP.x][downP.y] == false)
        ){
          //good point 
          std::cout << "added down" << downP.x << ", " << downP.y << std::endl;
          myFns.add(work_list_, downP);
          //visitedAlrdy[downP.x][downP.y] = true;
        }
        Point leftP(point2.x - 1, point2.y);
        heymama = (leftP.x < myImage->imageToTraverse.width() && (leftP.x >= 0)) && (leftP.y < myImage->imageToTraverse.height() && leftP.y >= 0);
        if (heymama && calculateDelta(startingPixel, myImage->imageToTraverse.getPixel(leftP.x, leftP.y)) <= theTol && //bound cont h
        (visitedAlrdy[leftP.x][leftP.y] == false)
        ){
          //good point 
          myFns.add(work_list_, leftP);
          std::cout << "added left" << leftP.x << ", " << leftP.y << std::endl;
          //visitedAlrdy[leftP.x][leftP.y] = true;
        }
        Point upP(point2.x, point2.y - 1);
        heymama = (upP.x < myImage->imageToTraverse.width() && (upP.x >= 0)) && (upP.y < myImage->imageToTraverse.height() && upP.y >= 0);
        if (heymama && calculateDelta(startingPixel, myImage->imageToTraverse.getPixel(upP.x, upP.y)) <= theTol && //bound cont h
        (visitedAlrdy[upP.x][upP.y] == false)
        ){
          //good point 
          myFns.add(work_list_, upP);
          std::cout << "added up" << upP.x << ", " << upP.y << std::endl;
          //visitedAlrdy[upP.x][upP.y] = true;
        }

        
      //left
      
      //up

      //down
      
      myFns.pop(work_list_);
       std::cout << "point2 popped" << point2.x << ", " << point2.y << std::endl;

    }
    //remove current go into while loop 
    while (!work_list_.empty()) {
      //check 
      Point nextP = myFns.peek(work_list_);
      
      //const HSLAPixel& nextPixel = myImage->imageToTraverse.getPixel(nextP.x, nextP.y);

      if (visitedAlrdy[nextP.x][nextP.y] == true || calculateDelta(startingPixel, myImage->imageToTraverse.getPixel(nextP.x, nextP.y)) >= theTol) {
        //bad point
         std::cout << "point2 filtered" << nextP.x << ", " << nextP.y << std::endl;

        myFns.pop(work_list_);
      } else {
        break;//good point 
      }
    }

    if (work_list_.empty()) {
      myImage = NULL;
      std::cout << "eend" << std::endl;
    } else {
    Point nextP = myFns.peek(work_list_);
    currentPoint = nextP;
    visitedAlrdy[nextP.x][nextP.y] = true;
     std::cout << "next p" << nextP.x << ", " << nextP.y << std::endl;

    }
    // visitedAlrdy[nextP.x][nextP.y] = true;

    //now check for in bounds and tolerance here 
    //for RLUP points check if they are in tolerance bounds and visited or not 

    

  
    //go to next 

    

    //find a unvisited point
    //once u find it process it 
    //need to be in tolerance bound and in all directions like it sats 

    //currentPoint = the one i jus found/visited
    //
    return *this;
    // loikely use end as a bound to prevent things from blowing up or breaking 
    //if work list is empty, no neighbor nodes to add need to break or return error?
    // make current null 
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return currentPoint;
  }
  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return myImage != NULL;
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}