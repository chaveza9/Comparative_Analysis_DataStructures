#include "quadtree.h"
#include <math.h>
#include <stdio.h>
#include "stack.h"
//#include <stack>

/* Node data structure for 2D representation */
Point* createPoint(int x, int y){
    // create empty  point array
    Point* point =  (Point*) malloc(sizeof(Point));
    // Populate entries of data struct
    point->x = x;
    point->y = y;
    return point;
};
// Node Data
Node * createNode(Point point, int data){
    // create empty  point array
    Node* node =  (Node*) malloc(sizeof(Node));
    // Populate entries of node
    node->coordinates = point;
    return node;
};

/* Quadtrees Methods */
// Check if point is within limits
bool quadtree::__inBoundary__(Point Pt){
    // check if point is whithin boundaries
    bool check_x, check_y;
    check_x =(Pt.x >= this->top_left.x && Pt.x <= this->bot_right.x); 
    check_y =  (Pt.y >= this->top_left.y && Pt.y <= this->bot_right.y); 
    return (check_x && check_y);
};
bool quadtree::__instersectsBoundary__(Point testLeft, Point testRight){
    return  (this->bot_right.x > testLeft.x ||
             this->top_left.x < testRight.x ||
             this->top_left.y > testRight.y||
             this->bot_right.y < testLeft.y) ;           
};

// Create Quad tree 
quadtree::quadtree( Point topLeft, Point botRight, int capacity){
    // populate quadtree metadata
    this->capacity = capacity;
    this->size = 0;
    // Define point region boundaries
    this->top_left = topLeft;
    this->bot_right = botRight;
    // Initialize Children Nodes
    for (int i = 0; i < 4; i++)
    {
        this->child[i] = NULL;
    }
    // Preallocate memory for array of nodes
    this->pointArray = (Node*)malloc(sizeof(Node)*capacity);
};
// Class destructor
quadtree::~quadtree(){
    
     // Free all child nodes.
    for (int i = 0; i < 4; i++)
    {
        if(this->child[i] != NULL) delete this->child[i];
    }
    // Free this node.
    delete this->pointArray;

}  

// Insert Point (flag ={0,1} {false,true})
int quadtree::insert_node(Node *Pt){
    if(Pt == NULL)
        return 0;
    // Ignore objects outside of bound
    if(!this->__inBoundary__(Pt->coordinates))
        return 0;  // object cannot be added
    
    // If there is space in quadtree and if it does not contain subdivision, insert object here
    if(this->size < this->capacity){
        // Append point Pt on queue
        this->pointArray[this->size] = *Pt;
        // increase size of tree
        this->size++;
        printf("Node inserted \t x=%d \t y=%d \n", Pt->coordinates.x, Pt->coordinates.y);
        return 1;
    }
    else{ // Otherwise Check if current node is a leaf and then subdivide
        // Extract current values and push them  to a leave node
        // Create empty stack 
        Stack *X = createStack(500);
        Stack *Y = createStack(500);
        Stack *Vals = createStack(500); 
        // Empty Point
        Point extP;
        for (int i = 0; i < this->size; i++)
        {
            // Extract point
            extP = this->pointArray[i].coordinates;
            Push(X,this->pointArray[i].coordinates.x);
            Push(Y,this->pointArray[i].coordinates.y);
            Push(Vals,this->pointArray[i].data);
        }
        if(this->child[0] == NULL) // Node is has not been subdivided yet
            this->__subdivideQuad__();
        //We have to add the points/data contained into this quad array to the new quads if we want that only 
        //the last node holds the data 
        while(X->size!=0)
        {
            for (int i = 0; i < 4; i++)
            {
                if(this->child[i]->insert_node(createNode(*createPoint(Pop(X),Pop(Y)),Pop(Vals))));
                    
            }
        }
        /* extP = createNode(*createPoint(Pop(X),Pop(Y)),Pop(Vals));
            for (int i = 0; i < 4; i++)
            {
                if(this->child[i]->insert_node(extP)){
                    flag = 1;
                    break;
                }
            }
            if(flag)
                break; */

        for (int i = 0; i < 4; i++)
        {
            if(this->child[i]->insert_node(Pt))
                return 1;
        }     
    }
    // Otherwise, point could not be inserted 
    //printf("Node could not be inserted \t x=%d \t y=%d \n", Pt->coordinates.x, Pt->coordinates.y);
    return 0;      
};
// Delete Node *****************************************************************
void quadtree::delete_node(Node *Pt){};
// create additional four children by dividing region 4 times

// Print Quadtree 
void quadtree::printCapacities(int depth){
    for (int i = 0; i < depth; i++)
        printf("\t");
    if(this->child[0]==NULL)
    {
        printf("Points: %d\n", this->size);
        return;
    }
    else if (this->child[0]!=NULL)
    {
        printf("Children:\n");
        for (int i=0; i<4; i++)
            this->child[i]->printCapacities(depth+1);
        return;
    }   
    
};

void quadtree::printTree(int depth){
    for (int i = 0; i < depth; i++)
        printf("\t");
    if(this->child[0]==NULL)
    {
        printf("Points: %d\n", this->size);
            for (int i = 0; i < this->size; i++)
            {
                printf("  %d. x=%d \t y=%d \n",i+1, this->pointArray[i].coordinates.x, this->pointArray[i].coordinates.y);
            }
            
        return;
    }
    else if (this->child[0]!=NULL)
    {
        printf("Children:\n");
        for (int i = 0; i < this->size; i++)
            {
                printf("\t child %d. x=%d \t y=%d \n",i+1, this->pointArray[i].coordinates.x, this->pointArray[i].coordinates.y);
            }
        for (int i=0; i<4; i++)
            this->child[i]->printTree(depth+1);
        return;
    }   
    
};

void quadtree::__subdivideQuad__(){
    // Divide quadrant into 4 equal subquadrants
    int half_dim_x = (int)(this->bot_right.x+this->top_left.x)/2;
    int half_dim_y = (int)(this->bot_right.y+this->top_left.y)/2;
    
    // Create a midpoint
    Point* halfPt = createPoint(half_dim_x,half_dim_y);  
    /*
	 Position of the child node, based on index (0-3), is determined in this order:
	 | 1 NW | 0 NE |
	 | 2 SW | 3 SE |
	 */
    
    // Create new subquadrants based on the new boundaries
    this->child[0] = new quadtree(*createPoint(halfPt->x,this->top_left.y),  //NE
                *createPoint(this->bot_right.x, halfPt->y), this->capacity);  
    this->child[1] = new quadtree(this->top_left, *halfPt, this->capacity);  //NW
    this->child[2] = new quadtree(*createPoint(this->top_left.x, halfPt->y), //SW   
                *createPoint(halfPt->x, this->bot_right.y), this->capacity);
    this->child[3] = new quadtree(*halfPt, this->bot_right , this->capacity);  //SE
};

// Extract capacity
int quadtree::getCapacity() const{
    return this->capacity;
};
// Extract current Size
int quadtree::getSize() const{
    return this->size;
};

void quadtree::__query__(Point topLeft, Point botRight, Stack* X, Stack* Y, Stack* Vals){
    Point Pt;
    if(!this->__instersectsBoundary__(topLeft, botRight))
        return;
    
    for (int i = 0; i < this->size; i++)
    {
        // Extract point
        Pt = this->pointArray[i].coordinates;
        // Check if extracted point is within specified boundary for query
        if( (Pt.x >= topLeft.x && Pt.x <= botRight.x) &&
            (Pt.y >= topLeft.y && Pt.y <= botRight.y))
        {
            Push(X,this->pointArray[i].coordinates.x);
            Push(Y,this->pointArray[i].coordinates.y);
            Push(Vals,this->pointArray[i].data);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if(this->child[i]!=NULL)    
        {
            this->child[i]->__query__(topLeft, botRight, X, Y, Vals);
        } 
    }
    
};
// Print Values within Region
void quadtree::inRegion(Point topLeft, Point botRight){
    //define empty storing stacks
    Stack* X = createStack(5000);
    Stack* Y = createStack(5000);
    Stack* Vals = createStack(5000);
    // Extract values in region
    this->__query__(topLeft, botRight, X, Y, Vals);
    //Print values in region
    for (int i = 0; i < X->size; i++)
    {
        printf("x=%d \t y=%d \t val=%d \n", Pop(X), Pop(Y), Pop(Vals));
    }
};
