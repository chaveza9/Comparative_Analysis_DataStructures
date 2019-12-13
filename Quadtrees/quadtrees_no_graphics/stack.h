#ifndef _STACK_H
#define _STACK_H

/* Node data structure for 2D representation */
typedef struct Point
{
    int x;
    int y;
} Point;
Point * createPoint(int x, int y);
// Check if two points are the same
bool isPointEqual(Point Pt1, Point Pt2);

// Node Data
typedef struct Node
{
    Point coordinates;
    int data;
} Node;
Node * createNode(Point point, int data);


typedef struct Stack
{
        int capacity;
        int size;
        int top;
        //int rear;
        Node *elements;
}Stack;

Stack * createStack(int maxElements);
void Push(Stack *S,Node element);
Node Pop(Stack *S);
Node Show(Stack *S, int Pos);


#endif /*_STACK_H*/