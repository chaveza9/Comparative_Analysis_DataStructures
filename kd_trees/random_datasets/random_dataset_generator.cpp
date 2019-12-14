#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#define DIMMENSION 2
#define NUM_OF_SIZES 4
#define NUM_OF_DATASETS 100

using namespace std;

/* 
    File output code based off of HW4: makeGraph.cpp
*/

int main() {
    // Sizes of datasets
    int dataset_sizes[NUM_OF_SIZES] = {100, 1000, 100000, 1000000};
    // Number of points in dataset
    int n;
    // Output if rand() == 1
    int max;
    // number of datasets per size
    int d;

    time_t t;

    srand(time(&t));


    for (int i = 0; i < NUM_OF_SIZES; i++) {
        n = dataset_sizes[i];
        max = n*10;
        if (n >= 100000)
            d = 10;
        else
            d = NUM_OF_DATASETS;
        for (int h = 0; h < d; h++) {
            cout << "n: " << n << " " << "dataset num: " << h << endl;
            char filename[20];
            sprintf(filename, "%d_%d_%d.txt", n, DIMMENSION, h); 
            ofstream outfile(filename);
            outfile << n << " " << DIMMENSION << endl;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < DIMMENSION; k++) {
                    outfile << (int) ((((float) rand())/RAND_MAX)*max);
                    if (k != DIMMENSION-1)
                        outfile << " ";
                }
                outfile << endl;
            }
        }
    }

    return 0;
}

