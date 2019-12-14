#include<stdio.h>
#include<iostream>

using namespace std;

struct Node {

    // "Feature Vector"
    int *coordinates;

    // Left Child
    Node *lo_child;

    // Right Child
    Node *hi_child;

    // DISC
    int DISC;
};

int next_disc(int disc, int d);

Node* insert_or_find_node(Node* Q, int* point, int d, bool insert, int disc);

void find_min_key_in_subtree(Node* Q, Node* Parent_Q, Node* best_min_node, Node* best_min_node_parent, bool* is_hi, int j_disc);

Node* find_max_key_in_subtree(Node* Q, Node* Parent_Q, Node* best_max_node, Node* best_max_node_parent, bool* is_hi, int j_disc);

Node* remove_node(Node* P);