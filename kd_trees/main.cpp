#include "kd_tree.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>


int main() {
       /* Timeing and IO setup (FROM HW2) */
    chrono::time_point<chrono::steady_clock> start, stop; 
    chrono::duration<double> difference_in_time;
    double difference_in_seconds_build;
    double difference_in_seconds_finds;
    ofstream outfile;
    // number of points in input_file
    int n;
    // dimension of points in kd_tree
    int d;
    FILE *fp1;
    FILE *of1;
    char infile[200];


    // Enter the name of the .txt file to build the tree of.
    cout << "Enter the name of a file to compute kd_tree build time and 100 random find_node times: "<< endl;
    scanf("%s", &infile);
    cout << " infile  " << infile << endl;
    fp1 = fopen(infile,"r");
    if (fp1 == NULL) {
      printf("Did not find input file \n");
      exit(1);
    }

    fscanf(fp1,"%d %d",&n,&d);

    fscanf(fp1,"%d %d",&n,&d);
    char filename[30];
    sprintf(filename, "%d_%d_insert_find_times.txt", n, d); 
    of1 = fopen(filename, "a");

    kd_tree tree_1 = kd_tree(d);

    int point[d];
    int points[n][d];

    start = chrono::steady_clock::now();
    for (int i = 0; i < n; i++){
        cout << "i: " << i << endl;
        for (int j = 0; j < d; j++) {
            fscanf(fp1,"%d",&point[j]);
            points[i][j] = point[j];
            cout << point[j] << " ";
            if (j < d-1)
                fscanf(fp1, " ");
        }
        cout << endl;
        tree_1.insert_node(point);

    }
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_build = double(difference_in_time.count());


    start = chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        cout << "Exception here?" << endl;
        int rand_i = (int) ((((float) rand())/RAND_MAX)*n);
        // if (already_deleted[rand_i] == 1) {
        //     cout << "already deleted" << endl;
        // }
        // else {
        tree_1.find_node(points[rand_i]);
            // already_deleted[rand_i] = 1;
        // }

    }
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_finds = double(difference_in_time.count());
    fprintf(of1, "%f %f\n", difference_in_seconds_build, difference_in_seconds_finds);
    fclose(of1);



// Delete from root works
    // for (int i = 0; i < 100; i++) {
    //         tree_1.delete_node(tree_1.root->coordinates);
    // }

    return 0;
}