#include<stdio.h>
#include"node.h"


class kd_tree{
public:
    // constructs empty kd tree
    kd_tree();
    
    // constructs a one node empty kd tree
    // kd_tree(int* array, int dim);

    // constructs a no node kd_tree with d = dim;
    kd_tree(int dim);

    void print_node(Node* a);

    void insert_node(int* array);

    void delete_node(int* array);

    Node* find_node(int* array);

private:


    
public:
    // dimension of the coordinates of each node
    int d;
    Node *root;

};