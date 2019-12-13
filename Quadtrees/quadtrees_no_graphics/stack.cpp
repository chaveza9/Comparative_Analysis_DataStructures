#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

//Stack Functions Defitinition

/* Node data structure for 2D representation */
Point* createPoint(int x, int y){
    // create empty  point array
    Point* point =  (Point*) malloc(sizeof(Point));
    // Populate entries of data struct
    point->x = x;
    point->y = y;
    return point;
};

bool isPointEqual(Point Pt1, Point Pt2){
    return (Pt1.x == Pt2.x && Pt1.y == Pt2.y);    
};
// Node Data
Node * createNode(Point point, int data){
    // create empty  point array
    Node* node =  (Node*) malloc(sizeof(Node));
    // Populate entries of node
    node->coordinates = point;
    return node;
};

/* STACK FUNCTIONS */
Stack * createStack(int maxElements)
{
    /* Create a Stack */
    Stack *S;
    S = (Stack*)malloc(sizeof(Stack));
    /* Initialise its properties */
    S->elements = (Node *)malloc(sizeof(Node)*maxElements);
    S->size = 0;
    S->capacity = maxElements;
    S->top = -1;
    /* Return pointer containing stack */
    return S;
}

void Push(Stack *S,Node element)
{
    /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
    if(S->size == S->capacity)
    {
            printf("Stack is Full\n");
    }
    else
    {
        // Increment top pointer
        S->top++;
        // increment size pointer
        S->size++;
        /* Insert the element in its rear side */ 
        S->elements[S->top] = element;
    }
    return;
}

Node  Pop(Stack *S)
{
    // Deine a return element integer
    Node  element;
    /* If Stack size is zero then it is empty. So we cannot pop */
    if(S->size==0)
    {
        printf("Stack is Empty\n");
        return element;
    }
    /* Removing an element is equivalent to decrementing index of top by one */
    else
    {   
        element = S->elements[S->top];
        S->size--;  // Decrease stack size
        S->top--; //Decrease top index
    }
    return element;
}
Node Show(Stack *S, int Pos){
    // Deine a return element integer
    Node  element;
    if(Pos < S->size)
        element = S->elements[Pos];
    else
    {
        printf("problem with pos");
    }
    
    return element;
};