#include "quadtree.h"
#include <time.h>
#include <fstream>
#include <chrono>
#include <stdio.h>
#include <iostream>

using namespace std;
// Read-In Code based off of HW5 code
int main(int argc, char *argv[]) {
       /* Timeing and IO setup (FROM HW2) */
    chrono::time_point<chrono::steady_clock> start, stop; 
    chrono::duration<double> difference_in_time;
    double difference_in_seconds_build;
    double difference_in_seconds_finds;
    double difference_in_seconds_closest;
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
    int x, y;
    char filename[30];
    sprintf(filename, "%d_%d_permuted_insert_find_times.txt", n, d); 
    of1 = fopen(filename, "a");
    
    // ALLOCATE MEMORY FOR POINTS ARRAY
	Node* pointArray = (Node*)malloc(sizeof(Node)*n);
    // cout << "initialize kd_tree" << endl;
    // cout << "n: " << n << " " << "d: " << d << endl;
    int point[d];
    int points[n][d];
    //int already_deleted[n];
    
    for (int i = 0; i < n; i++){
        if(fscanf(fp1,"%d %d",&x,&y) != EOF){
            pointArray[i].coordinates = *createPoint(x,y);
            pointArray[i].data = 0;  
        }
    }
    fclose(fp1);
    // Create empty quadTree
	quadtree qt(*createPoint(0,0), *createPoint(n*10,n*10), 1);
    
    // INSERT TIME
    start = chrono::steady_clock::now();
    for(int i=0;i<n;i++)
	{
		qt.insert_nodeMXR(&pointArray[i]);
	}
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_build = double(difference_in_time.count())/n;      
    
    difference_in_time = stop - start;
    difference_in_seconds_build = double(difference_in_time.count());
    time_t t;

    srand(time(&t));
    start = chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        int rand_i = (int) ((((float) rand())/RAND_MAX)*n);
        qt.searchPt(pointArray[rand_i].coordinates);
    }
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_finds = double(difference_in_time.count())/n;
    
    start = chrono::steady_clock::now();
    for (int i = 0; i < n; i++) {
        int rand_i = (int) ((((float) rand())/RAND_MAX)*n);
        qt.searchPt(pointArray[rand_i].coordinates);
    }
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_closest = double(difference_in_time.count())/n;
    
    fprintf(of1, "%f %f %f\n", difference_in_seconds_build, difference_in_seconds_finds, difference_in_seconds_closest);
    fclose(of1);

    return 0;
}