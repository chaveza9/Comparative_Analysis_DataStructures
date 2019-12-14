#include"node.h"


int next_disc(int disc, int d) {
    return (disc+1) % d;
}

Node* insert_or_find_node(Node* Q, int* point, int d, bool insert, int disc) {
    bool equal_coordinates = true;
    int child_disc = next_disc(disc, d);
    Node* child;
    if (Q == nullptr) {
        // insert_node acts as find_node, but node not found
        if (insert == false) {
            // printf("Find\n");
            return nullptr;
        }
        // insert_node acts as insert_node,
        // node not found in tree
        else {
            // printf("Insert\n");
            Q = new Node;
            Q->hi_child = nullptr;
            Q->lo_child = nullptr;
            Q->DISC = child_disc;
            Q->coordinates = new int[d];
            for (int i = 0; i < d; i++) {
                Q->coordinates[i] = point[i];
            }
            return Q;
        }
    }
    // cout << "Current Node: " <<  Q->coordinates[0] << ", " << Q->coordinates[1] << endl;

    for (int i = 0; i < d; i++) {
        if (point[i] != Q->coordinates[i]) {
            equal_coordinates = false;
        }
    }

    if (equal_coordinates == true) {
        // printf("equal_coordinates\n");
        return Q;
    }

    // cout << "----------" << endl;
    // for (int j = 0; j < d; j++)
    //     cout << Q->coordinates[j] << " ";
    // cout << endl;
    // for (int k = 0; k < d; k++)
    //     cout << point[k] << " ";
    // cout << endl;
    // cout << "DISC: " << Q->DISC << endl;

    if (point[Q->DISC] > Q->coordinates[Q->DISC]) {
        // cout << "hi_child" << endl;
        child = insert_or_find_node(Q->hi_child, point, d, insert, child_disc);
        if (insert) {
            Q->hi_child = child;
        }
        else {
            if (child == nullptr)
                return nullptr;
            equal_coordinates = true;
            for (int i = 0; i < d; i++) {
                if (point[i] != Q->hi_child->coordinates[i])
                    equal_coordinates = false;
            }
            if (equal_coordinates)
                return Q;
            else
            return child;
        }
        
    }
    else {
        // cout << "lo_child" << endl;
        child = insert_or_find_node(Q->lo_child, point, d, insert, child_disc);
        if (insert) {
            Q->lo_child = child;
        }
        else {
            if (child == nullptr)
                return nullptr;
            equal_coordinates = true;
            for (int i = 0; i < d; i++) {
                if (point[i] != Q->lo_child->coordinates[i])
                    equal_coordinates = false;
            }
            if (equal_coordinates)
                return Q;
            else
            return child;
        }
        
    }
    // cout << "----------" << endl;
    // for (int i = 0; i < d; i++)
    //     printf("%d ", Q->coordinates[i]);
    // if (Q->lo_child == nullptr)
    //     printf("lo_child null ");
    // if (Q->hi_child == nullptr)
    //     printf("hi_child null ");
    // printf("\n");

    return Q;
}

void find_min_key_in_subtree(Node* Q, Node* Parent_Q, Node* best_min_node, Node* best_min_node_parent, bool* is_hi, int j_disc) {

    // Node* best_min_node;
    // cout << "in find_min_key" << endl;
    // cout << "is_hi " << *is_hi << endl;

    if (*is_hi) {
        best_min_node = best_min_node_parent->hi_child;
    }
    else {
        best_min_node = best_min_node_parent->lo_child;
    }

    // cout << "found ya 4" << " best_min_node " << best_min_node << " best_min_node_parent->hi_child " << best_min_node_parent->hi_child << ", " << "best_min_node_parent->lo_child " << best_min_node_parent->lo_child << endl;
    // cout << Q->coordinates[0] << endl;
    // Q being a j_disc node guarantees the best min node cannot be found in subtree(Q->hi_child)
    if (Q->DISC == j_disc) {
        // cout << "Q is j_disc" << endl;
        // cout << best_min_node->coordinates[j_disc] << endl;
        // New best_min_node is Q
        if (Q->coordinates[j_disc] < best_min_node->coordinates[j_disc]) {
            best_min_node = Q;
            best_min_node_parent = Parent_Q;
            if (best_min_node_parent->hi_child == best_min_node)
                *is_hi = true;
            else
                *is_hi = false;
        }

        // subtree(Q->lo_child) exists -> best_min_node could be found in subtree(Q->lo_child)
        if (Q->lo_child != nullptr) {
            find_min_key_in_subtree(Q->lo_child, Q, best_min_node, best_min_node_parent, is_hi, j_disc);
            // cout << "found ya 4" << " best_min_node " << best_min_node << " best_min_node_parent->hi_child " << best_min_node_parent->hi_child << ", " << "best_min_node_parent->lo_child " << best_min_node_parent->lo_child << endl;
        }

        if (best_min_node_parent->hi_child == best_min_node)
            *is_hi = true;
        else
            *is_hi = false;

    }
    // Q not being a j_disc node means the best_min_node could be found either subtree
    else {
        // cout << "Q is not j_disc" << endl;
        // New best_min_node is Q
        if (Q->coordinates[j_disc] < best_min_node->coordinates[j_disc]) {
            // cout << "Q:" << Q << endl;
            best_min_node = Q;
            best_min_node_parent = Parent_Q;

            // // determining whether best_min_node is the hi or lo child of best_min_node_parent
            if (best_min_node_parent->hi_child == best_min_node)
                *is_hi = true;
            else
                *is_hi = false;
            // cout << best_min_node_parent->coordinates[0] << ", " << best_min_node_parent->coordinates[1] << endl;
            // cout << "best_min_node " << best_min_node << " best_min_node_parent->hi_child " << best_min_node_parent->hi_child << ", " << "best_min_node_parent->lo_child " << best_min_node_parent->lo_child << endl;
            // cout << "Q->lo_child " << Q->lo_child << " Q->hi_child " << Q->hi_child << endl;

        }

        // subtree(Q->lo_child) exists -> best_min_node could be found in subtree(Q->lo_child)
        if (Q->lo_child != nullptr) {
            // cout << "Q->lo_child != nullptr" << endl;

            // determining whether best_min_node is the hi or lo child of best_min_node_parent
            if (best_min_node_parent->hi_child == best_min_node)
                *is_hi = true;
            else
                *is_hi = false;

            find_min_key_in_subtree(Q->lo_child, Q, best_min_node, best_min_node_parent, is_hi, j_disc);
            // cout << "found ya 1" << " best_min_node " << best_min_node << " best_min_node_parent->hi_child " << best_min_node_parent->hi_child << ", " << "best_min_node_parent->lo_child " << best_min_node_parent->lo_child << endl;
            if (best_min_node_parent->hi_child == best_min_node)
                *is_hi = true;
            else
                *is_hi = false;
        }

        // subtree(Q->hi_child) exists -> best_min_node could be found in subtree(Q->hi_child)
        if (Q->hi_child != nullptr) {
            // cout << "Q->hi_child != nullptr" << endl;
            // cout << best_min_node << " " << best_min_node_parent->hi_child << " " << best_min_node_parent->lo_child << endl;
            // cout << "found ya 2" << endl;
            // determining whether best_min_node is the hi or lo child of best_min_node_parent
            if (best_min_node_parent->hi_child == best_min_node)
                *is_hi = true;
            else
                *is_hi = false;

            find_min_key_in_subtree(Q->hi_child, Q, best_min_node, best_min_node_parent, is_hi, j_disc);
            // cout << "found ya 3" << " best_min_node " << best_min_node << " best_min_node_parent->hi_child " << best_min_node_parent->hi_child << ", " << "best_min_node_parent->lo_child " << best_min_node_parent->lo_child << endl;
            if (best_min_node_parent->hi_child == best_min_node)
                *is_hi = true;
            else
                *is_hi = false;
        }


    }
    // cout << "Before Return" << endl;
    // cout << "best_min_node " << best_min_node << " best_min_node_parent->hi_child " << best_min_node_parent->hi_child << ", " << "best_min_node_parent->lo_child " << best_min_node_parent->lo_child << endl;
    // cout << "is_hi " << *is_hi << endl;
    return;
}

Node* find_max_key_in_subtree(Node* Q, Node* Parent_Q, Node* best_max_node, Node* best_max_node_parent, bool* is_hi, int j_disc) {
  
    // Node* best_max_node;
    // cout << "in find_max_key" << endl;
    if (*is_hi)
        best_max_node = best_max_node_parent->hi_child;
    else
        best_max_node = best_max_node_parent->lo_child;

    // Q being a j_disc node guarantees the best max node cannot be found in subtree(Q->hi_child)
    if (Q->DISC == j_disc) {
        // New best_min_node is Q
        if (Q->coordinates[j_disc] > best_max_node->coordinates[j_disc]) {
            best_max_node = Q;
            best_max_node_parent = Parent_Q;

            if (best_max_node_parent->hi_child == best_max_node)
                *is_hi = true;
            else
                *is_hi = false;
        }

        // subtree(Q->lo_child) exists -> best_max_node could be found in subtree(Q->lo_child)
        if (Q->lo_child != nullptr) {
            best_max_node = find_max_key_in_subtree(Q->lo_child, Q, best_max_node, best_max_node_parent, is_hi, j_disc);

        }

        if (best_max_node_parent->hi_child == best_max_node)
            *is_hi = true;
        else
            *is_hi = false;
      
    }
    // Q not being a j_disc node means the best_max_node could be found either subtree
    else {

        // New best_min_node is Q
        if (Q->coordinates[j_disc] > best_max_node->coordinates[j_disc]) {
            best_max_node = Q;
            best_max_node_parent = Parent_Q;

            if (best_max_node_parent->hi_child == best_max_node)
                *is_hi = true;
            else
                *is_hi = false;

        }

        // subtree(Q->lo_child) exists -> best_max_node could be found in subtree(Q->lo_child)
        if (Q->lo_child != nullptr) {

            if (best_max_node_parent->hi_child == best_max_node)
                *is_hi = true;
            else
                *is_hi = false;

            best_max_node = find_max_key_in_subtree(Q->lo_child, Q, best_max_node, best_max_node_parent, is_hi, j_disc);
            
            if (best_max_node_parent->hi_child == best_max_node)
                *is_hi = true;
            else
                *is_hi = false;
        }

        // subtree(Q->hi_child) exists -> best_max_node could be found in subtree(Q->hi_child)
        if (Q->hi_child != nullptr) {
             if (best_max_node_parent->hi_child == best_max_node)
                *is_hi = true;
            else
                *is_hi = false;

            best_max_node = find_max_key_in_subtree(Q->hi_child, Q, best_max_node, best_max_node_parent, is_hi, j_disc);
            if (best_max_node_parent->hi_child == best_max_node)
                *is_hi = true;
            else
                *is_hi = false;
        }
    }

    return best_max_node;
}

Node* remove_node(Node* P) {
    // Assumes that pointer to node is given

    Node* Parent_Q = new Node;
    Node* Q = new Node;
    bool is_hi_child;
    // cout << "remove_node" << endl;
    // cout << "P: " << P->coordinates[0] << ", " << P->coordinates[1] << endl;
    // Edge Case: P is NULL
    if (P == nullptr) {
        return nullptr;
    }

     int j_disc = P->DISC;
     // cout << "j_disc " << j_disc << endl;

    // D.1: P is a leaf
    if ((P->hi_child == nullptr) &&  (P->lo_child == nullptr)) {
        // cout << "no children deletion" << endl;
        // cout << P->coordinates[0] << ", " << P->coordinates[1] << endl;
        P = nullptr;
        return P;
    }
    // cout << P->coordinates[0] << ", " << P->coordinates[1] << endl;
    Parent_Q = P;
    // D.2: Finding root of P's successors
    if (P->lo_child == nullptr) {
        is_hi_child = true;
        Q = P->hi_child;
        // cout << "Q = P->hi_child" << endl;
        // D.3: Get root of P's successors from P->hi_child subtree
        find_min_key_in_subtree(P->hi_child, Parent_Q, Q, Parent_Q, &is_hi_child, j_disc);

        // cout << Q->coordinates[0] << ", " << Q->coordinates[1] << endl;
    } else {
        is_hi_child = false;
        Q = P->lo_child;
        // D.4: Get root of P's successors from P->lo_child subtree
        find_max_key_in_subtree(P->lo_child, Parent_Q, Q, Parent_Q, &is_hi_child, j_disc);
    } 
    // cout << "Parent_Q: " << Parent_Q->coordinates[0] << ", " << Parent_Q->coordinates[1] << endl;
    // cout << "Q: " << Q->coordinates[0] << ", " << Q->coordinates[1] << endl;
    // cout << "is_hi_child: " << is_hi_child << endl;
    // D.5: Delete Q (recursive)
    // cout << "done with find_key" << endl;
    // cout << *(&is_hi_child) << endl;
    // cout << is_hi_child << endl;
    if (is_hi_child) {
        // cout << "Q "  << Q << endl;
        // cout << "Parent_Q->hi_child "  << Parent_Q->hi_child << endl;
        Parent_Q->hi_child = remove_node(Q);
    }
    else {
        Parent_Q->lo_child = remove_node(Q);
    }
    // cout << "done with removal" << endl;


    // cout << "P: " << P->coordinates[0] << ", " << P->coordinates[1] << endl;
    // cout << "Q: " << Q->coordinates[0] << ", " << Q->coordinates[1] << endl;

    // D.6: Make Q new root
    Q->DISC = j_disc;
    Q->hi_child = P->hi_child;
    Q->lo_child = P->lo_child;

    return Q;
}