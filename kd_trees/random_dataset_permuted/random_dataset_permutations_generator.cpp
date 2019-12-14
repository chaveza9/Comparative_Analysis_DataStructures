#include<iostream>
#include<fstream>
#include <cstdlib> 
#include <time.h>

using namespace std;

// From HW1 (this file is based heavily off randomSort.cpp)
void swap(int* a, int* b, int d);
int  uniform(int  m);
// void initialize_and_permute(int** permutation[], int n, int d);



int main(int argc, char *argv[]) {
    // number of data points in infile
    int n;
    // dimension of each point in data file
    int d;
    // Number of permutations
    int Ncases;

    // For swapping
    int temp;

    ifstream infile1;
    infile1.open(argv[1]);

    if(!infile1) {
        cout << "Error opening file " <<endl;
        return -1;
    } 


    infile1 >> n;
    infile1 >> d;

    if (n < 100000)
        Ncases = 100;
    else
        Ncases = 10;

    int data_points[n][d];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            infile1 >> data_points[i][j];
        }

    }
    cout << "here" << endl;
    // For swapping
    int random_n_index;

    for (int k = 0; k < Ncases; k++) {
        // Each iteration is a permutation
        for (int n_index = 0; n_index <= n-2; n_index++) {
            random_n_index = n_index+uniform(n-n_index);
            for (int d_index = 0; d_index < d; d_index++) {
                temp = data_points[n_index][d_index]; 
                data_points[n_index][d_index] = data_points[random_n_index][d_index]; 
                data_points[random_n_index][d_index] = temp;
            }
        }

        cout << "n: " << n << " " << "dataset num: " << k << endl;
        char filename[20];
        sprintf(filename, "%d_%d_perm_%d.txt", n, d, k); 
        ofstream outfile(filename);
        outfile << n << " " << d << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < d; j++) {
                outfile << data_points[i][j];
                if (j != d-1)
                    outfile << " ";
            }
            outfile << endl;
        }
    }


    return 0;
}

// void initialize_and_permute(int** permutation, int n, int d)
// {
//   // Clearly this is borrowed from the Wikipedia article
//   // https://en.wikipedia.org/wiki/Random_permutation 
//   int random_index;
//   for (int index = 0; index <= n-2; index++) {
//         random_index = index+uniform(n-index);
//         swap(&permutation[index], &permutation[random_index], d);
//     }   
// }

int  uniform(int  m)
{
  return rand()%m;
}  