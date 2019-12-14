#include "kd_tree.h"
#include <time.h>
#include <fstream>
#include <chrono>


// Read-In Code based off of HW5 code
int main(int argc, char *argv[]) {
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
    char *infile;
    FILE *fp1;
    FILE *of1;

    infile =  argv[1];

    cout << " infile  " << infile << endl;
    fp1 = fopen(infile,"r");
    if (fp1 == NULL) {
      printf("Did not find input file \n");
      exit(1);
    }
    fscanf(fp1,"%d %d",&n,&d);

    char filename[30];
    sprintf(filename, "%d_%d_insert_find_times.txt", n, d); 
    of1 = fopen(filename, "a");

    kd_tree tree_1 = kd_tree(d);
    cout << "initialize kd_tree" << endl;
    cout << "n: " << n << " " << "d: " << d << endl;
    int point[d];
    int points[n][d];
    // int already_deleted[n]; for some reason this array causes me to seg fault
    start = chrono::steady_clock::now();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < d; j++) {
            fscanf(fp1,"%d",&point[j]);
            cout << point[j] << endl;
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