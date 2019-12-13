#include "quadtree.h"
#include <math.h>
#include <stdio.h>
#include "stack.h"


#define STACK_CAPACITY 1000000

int returnRegion(Point topLeft, Point botRight, Point Pt){
    if ((topLeft.x + botRight.x) / 2 >= Pt.x) 
    { 
        // Indicates topLeftTree 
        if ((topLeft.y + botRight.y) / 2 >= Pt.y) 
        { 
            return 1; 
        }        
        // Indicates botLeftTree 
        else
        {   
            return 2; 
        } 
    } 
    else
    { 
        // Indicates topRightTree 
        if ((topLeft.y + botRight.y) / 2 >= Pt.y) 
        { 
            
            return 0; 
        } 
        // Indicates botRightTree 
        else
        { 
            
            return 3; 
        } 
    } 
}
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
    // check if rectangles overlap
    return !((  this->top_left.x  >  testRight.x  )||  (this->bot_right.x  <  testLeft.x)  || (this->top_left.y > testRight.y ) ||
           (this->bot_right.y  <  testLeft.y)); 
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
    this->Parent = NULL;
    // Preallocate memory for array of nodes
    this->pointArray = createStack(capacity+2);
};
quadtree::quadtree( Point topLeft, Point botRight, int capacity, quadtree* Father){
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
    this->Parent = Father;
    // Preallocate memory for array of nodes
    this->pointArray = createStack(capacity+2);
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
int quadtree::insert_nodeMXR(Node *Pt){
        if(Pt == NULL)
        return 0;
    // Ignore objects outside of bound
    if(!this->__inBoundary__(Pt->coordinates))
        return 0;  // object cannot be added
    
    // If there is space in quadtree and if it does not contain subdivision, insert object here
    if(this->size < this->capacity){
        // Append point Pt on queue
        Push(this->pointArray, *Pt);
        // increase size of tree
        this->size++;
        //printf("Node inserted \t x=%d \t y=%d \n", Pt->coordinates.x, Pt->coordinates.y);
        return 1;
    } 
    else{ // Otherwise Check if current node is a leaf and then subdivide
        if(this->child[0] == NULL) // Node is has not been subdivided yet
            this->__subdivideQuadMXR__();
        //We have to add the points/data contained into this quad array to the new quads if we want that only 
        //the last node holds the data 
        for (int i = 0; i < 4; i++)
        {
            if(this->child[i]->insert_nodeMXR(Pt))
                return 1;
        }     
    }
   
    return 0;       
};
int quadtree::insert_nodePR(Node *Pt){
        if(Pt == NULL)
        return 0;
    // Ignore objects outside of bound
    if(!this->__inBoundary__(Pt->coordinates))
        return 0;  // object cannot be added
    //Check if Point is repeated
    for(int i=0; i < this->pointArray->size; i++){
        if(isPointEqual(Show(this->pointArray, i).coordinates,Pt->coordinates))
            return 0;
    }
    // If there is space in quadtree and if it does not contain subdivision, insert object here
    if(this->size < this->capacity){
        // Append point Pt on queue
        Push(this->pointArray, *Pt);
        // increase size of tree
        this->size++;
        //printf("Node inserted \t x=%d \t y=%d \n", Pt->coordinates.x, Pt->coordinates.y);
        return 1;
    } 
    else{ // Otherwise Check if current node is a leaf and then subdivide
        if(this->child[0] == NULL){ // Node is has not been subdivided yet
            this->__subdivideQuadPR__();
            // Pop current values stored
            Node N;
            // reinsert parent nodes
            while(this->pointArray->size!=0){
                N = Pop(this->pointArray);
                this->insert_nodePR(&N);
            } 
        }
        // Compute the Corresponding matching region
        int reg;
        reg = returnRegion(this->top_left, this->bot_right, Pt->coordinates);
        // Insert data in the corresponding node
        if(this->child[reg]->insert_nodePR(Pt))
            return 1;
        else
            return 0;
    }
   
    return 0;   
}
// Delete Node *****************************************************************
void quadtree::delete_node(Node *Pt){
    // Look for smallest quadrant containing Pt
    quadtree* Q;
    Q = __searchQuadrant__(Pt->coordinates);
    // Check if only point in quadrant
    int region;
    region = returnRegion(Q->top_left, Q->bot_right, Pt->coordinates);
    delete Q->Parent->child[region];

    
};
// create additional four children by dividing region 4 times

// Print Quadtree 
void quadtree::printCapacities(int depth){
    printf("\t depth:%d \n", depth);
    for (int i = 0; i < depth; i++)
        printf("\t ");
    for (int i = 0; i < 4; i++)
    {
        if(this->child[i]==NULL){
            printf("Points: %d\n", this->size);    
        }
        else
        {
            printf("Children:\n");
            this->child[i]->printTree(depth+1);
        }      
    }
};

void quadtree::printTree(int depth){
    printf("\t depth:%d \n", depth);
    for (int i = 0; i < depth; i++)
        printf("\t ");
    for (int i = 0; i < 4; i++)
    {
        if(this->child[i]==NULL){
            printf("Points: %d\n", this->size); 
            for (int j = 0; j < this->pointArray->size; j++)
            {
                printf("%d. x=%d \t y=%d \n", j+1,Show(this->pointArray,j).coordinates.x, Show(this->pointArray,j).coordinates.y);
            }   
        }
        else
        {
            printf("Children:\n");
            this->child[i]->printTree(depth+1);
        }      
    }
};

void quadtree::__subdivideQuadPR__(){
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

void quadtree::__subdivideQuadMXR__(){
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

void quadtree::__query__(Point topLeft, Point botRight, Stack* X){
    Node Pt;
    if(!this->__instersectsBoundary__(topLeft, botRight))
        return;
    else
    {
    // Populate array if we are at leaf
        if(this->pointArray->size==this->size){
            for (int i = 0; i < this->size; i++)
            {
                // Extract point
                Pt = Show(this->pointArray,i);
                if( (Pt.coordinates.x >= topLeft.x && Pt.coordinates.x <= botRight.x) &&
                    (Pt.coordinates.y >= topLeft.y && Pt.coordinates.y <= botRight.y))
                {
                    Push(X,Pt);
                }
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if(this->child[i]!=NULL)    
            {
                this->child[i]->__query__(topLeft, botRight, X);
            } 
        }
    }
    
};
// Print Values within Region
void quadtree::inRegion(Point topLeft, Point botRight){
    //define empty storing stacks
    Stack* X = createStack(STACK_CAPACITY);
    Node N;
    // Extract values in region
    this->__query__(topLeft, botRight, X);
    //Print values in region
    while(X->size!=0)
    {
        N = Pop(X);
        printf("x=%d \t y=%d \t val=%d \n", N.coordinates.x, N.coordinates.y, N.data);
    }
};
Node quadtree::searchPt(Point Pt){
    //define empty storing stacks
    Stack* X = createStack(STACK_CAPACITY);
    
    // Extract values in region
    this->__query__(Pt, Pt, X);
    //Node* N = (Node*)malloc(sizeof(Node)*X->size);
    //Print values in region
    //int count = 0;
    Node N = Pop(X);
    /* while(X->size!=0)
    {
        N = Pop(X);
        //count ++;
    } */
    return N;
};

quadtree* quadtree::__searchQuadrant__(Point Pt){   
    
    // Current quad cannot contain it 
	if (!__inBoundary__(Pt)) 
		return NULL; 
    // it is located at the unit lenght quadrant
    else{
        int cuadrant ;
        // if it has been subdivided
        if(this->child[0]!=NULL){
            // compute cuadrant
            cuadrant = returnRegion(this->top_left, this->bot_right, Pt);  
            if(this->child[cuadrant]->__searchQuadrant__(Pt)==NULL)
                return this->child[cuadrant];
        }
    }
    return NULL;
};

void quadtree::__searchNearestPts__(Point Pt, Stack *S){
    if (!__inBoundary__(Pt)) 
        return;
    else
    {
        // Populate array if we are at leaf
        if(this->pointArray->size==this->size){
            for (int i = 0; i < this->size; i++)
            {
                // Extract Point
                Push(S,Show(this->pointArray,i));
            }
        }
        for (int i = 0; i < 4; i++)
        {
            if(this->child[i]!=NULL)    
            {
                this->child[i]->__searchNearestPts__(Pt, S);
            } 
        }
    }
};
void quadtree::NearestPt(Point Pt, Stack *S){
    // compute nearest neighbours
    Stack *Temp = createStack(STACK_CAPACITY);
    this->__searchNearestPts__(Pt, Temp);
    int dist =0;
    Node N;
    // Compute minimum Distance
    while(Temp->size!=0){
        N = Pop(Temp);
        if(this->__distance__(Pt, N.coordinates) < dist)
            dist = this->__distance__(Pt, N.coordinates);
    }
    // Compute range rectangle
    Point *regLeft = createPoint(Pt.x - dist, Pt.y + dist);
    Point *regRight = createPoint(Pt.x + dist, Pt.y - dist);
    // Extract candidate points
    this->__query__(*regLeft, *regRight, Temp);
    dist = 0;
    
    while(Temp->size!=0){
        N = Pop(Temp);
        if(this->__distance__(Pt, N.coordinates) < dist){
            dist = this->__distance__(Pt, N.coordinates);
            Push(S,N);
        }
    }

};
Node quadtree::nearestNeighbour(Point Pt){
    // Look for smallest quadrant containing Pt
    quadtree* Q;
    Q = __searchQuadrant__(Pt);
    // Create storing stack for nearest points
    Stack* Temp =  createStack(STACK_CAPACITY); //Might need more space
    // Extract Closest point 
    Node N;
    if(Q == NULL)
        return N;
    if (Q->pointArray->size!=0){
        for (int i = 0; i < Q->pointArray->size; i++)
        {
            Push(Temp, Show(Q->pointArray, i));
        }
    }
    // Compute minimum distance
    int dist = 500000;
    int tempdist = 0;
    if(Q->capacity==1){
        return (Pop(Temp));
    }
    else{
        while(Temp->size!=0)
        {   
            tempdist = this->__distance__(Pt, Pop(Temp).coordinates);
            if(tempdist < dist)
                dist = tempdist;
        }
    }
    Point *regLeft = createPoint(Pt.x - dist, Pt.y + dist);
    Point *regRight = createPoint(Pt.x + dist, Pt.y - dist);
    // Extract candidate points
    __query__(*regLeft, *regRight, Temp);

    // Compute the closest point
    dist = 500000;
    tempdist = 0;
    Node closest;
    Node TempClosest;
    while(Temp->size!=0)
    {   
        TempClosest = Pop(Temp);
        tempdist = this->__distance__(Pt, TempClosest.coordinates);
        if(tempdist < dist){
            dist = tempdist;
            closest = TempClosest;
        }
    }

    return closest;
};
int quadtree::__distance__(Point P1, Point P2){
    return (int)ceil((sqrt(pow(P2.x-P1.x,2)+pow(P2.y-P1.y,2))));
};



