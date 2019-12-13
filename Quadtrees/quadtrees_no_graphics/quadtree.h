#ifndef _QUADTREE_H
#define _QUADTREE_H

#include <stdio.h>
#include "stack.h"


/* Quadtrees Structure definition */
class quadtree
{
protected:
    // Boundary details
    Point top_left;
    Point bot_right;
    // Set children
    quadtree *child[4];
    quadtree *Parent;
    // Points 
    Stack *pointArray;
    // Tree Metadata
    int capacity;   //Maximum number of nodes per tree
    int size;       // Current size of tree
    // Private function members
    // create additional four children by dividing region 4 times
    void __subdivideQuadPR__();
    void __subdivideQuadMXR__();
    // Check if pt data is within boundary
    bool __inBoundary__(Point Pt);
    // Check if bounding boxes are intersected
    bool __instersectsBoundary__(Point top_left2, Point bot_right2);
    // Query points within region
    void __query__(Point topLeft, Point botRight, Stack* X);
    int __distance__(Point P1, Point P2);
    
public:
    quadtree(Point topLeft, Point botRight, int capacity);
    quadtree( Point topLeft, Point botRight, int capacity, quadtree* Father);
    ~quadtree();
    /* ------Util Functions-----*/
    // insert a node onto tree
    int insert_nodeMXR(Node *Pt); //********* Could be node pointer
    int insert_nodePR(Node *Pt); //********* Could be node pointer
    // Delete Node
    void delete_node(Node *Pt);
    // Print Quadtree
    void printCapacities(int depth = 0);
    void printTree(int depth = 0);

    /* ----- Return Functions -----*/
    // Lookup for pt node 
    Node searchPt(Point Pt);
    // Extract capacity
    int getCapacity() const;
    // Extract current Size
    int getSize() const;
    // Print Values within Region
    void inRegion(Point topLeft, Point botRight);
    // Nearest neighbour
    Node nearestNeighbour(Point Pt);
    // Look for smallest quadrant containing point Pt
    quadtree* __searchQuadrant__(Point Pt);
    //  Nearest Points
    void __searchNearestPts__(Point Pt, Stack *S);
    void NearestPt(Point Pt, Stack *S);
    
    
};

#endif /*_QUADTREE_H*/