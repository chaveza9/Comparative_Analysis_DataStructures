#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    // ifstream infile;
    // infile.open(argv[1]);
    int vals = 2;
    int line_counter = 0;
    double min_insert, max_insert, min_find, max_find;
    FILE *fp1;
    char *infile;
    float a, b;

    infile = argv[1];
    cout << " infile  " << infile << endl;
    fp1 = fopen(infile,"r");
    // cout << "vals: " << vals << endl;
    while (vals == 2) {
        line_counter++;
        vals = fscanf(fp1,"%f %f", &a, &b);
        // cout << "vals: " << vals << endl;
    }
    fclose(fp1);
    // cout << "seg fault here" << endl;

    double insert_times[line_counter];
    double find_times[line_counter];
    double avg_insert;
    double avg_find;
    fp1 = fopen(infile,"r");
    for (int i = 0; i < line_counter; i++) {
        fscanf(fp1, "%f %f", &insert_times[i], &find_times[i]);;
        if (i == 0) {
            min_insert = insert_times[i];
            max_insert = insert_times[i];
            min_find = find_times[i];
            max_find = find_times[i];
            avg_find = find_times[i];
            avg_insert = insert_times[i];
        } else {
            if (insert_times[i] < min_insert)
                min_insert = insert_times[i];
            if (insert_times[i] > max_insert)
                max_insert = insert_times[i];
            if (find_times[i] < min_find)
                min_find = find_times[i];
            if (find_times[i] > max_insert)
                max_find = find_times[i];
            avg_find = avg_find + find_times[i];
            avg_insert = avg_insert + insert_times[i];
        }
    }
    fclose(fp1);

    double bin_width = ((avg_insert-min_insert)/7);
    int histogram_bins[] = {0, 0, 0, 0, 0, 0, 0, 0};
    double histogram_ticks[] = {bin_width+min_insert, 
                                2*bin_width+min_insert, 
                                3*bin_width+min_insert, 
                                4*bin_width+min_insert, 
                                5*bin_width+min_insert, 
                                6*bin_width+min_insert, 
                                7*bin_width+min_insert};

    for (int i = 0; i < line_counter; i++) {
      if (insert_times[i] < histogram_ticks[0])
        histogram_bins[0]++;
      else 
      {
        if (insert_times[i] >= histogram_ticks[6])
          histogram_bins[7]++;
        else 
        {
          for (int g = 1; g < 5; g++) {
            if ((insert_times[i] >= histogram_ticks[g]) && (insert_times[i] < histogram_ticks[g+1]))
              histogram_bins[g]++;
          }
        } 
      }
    }

    ofstream hist_file;
    hist_file.open(strcat(infile,"_insert_hist"));
    for(int g = 0; g < 8; g++)
        hist_file << histogram_ticks[g-1] << " " << histogram_bins[g] << endl;
          // if (g == 0)
          //   hist_file << min_height << " " << histogram_bins[g] << endl;
          // else

    bin_width = ((avg_find-min_find)/7);
    int histogram_bins_f[] = {0, 0, 0, 0, 0, 0, 0, 0};
    double histogram_ticks_f[] = {bin_width+min_find, 
                                2*bin_width+min_find, 
                                3*bin_width+min_find, 
                                4*bin_width+min_find, 
                                5*bin_width+min_find, 
                                6*bin_width+min_find, 
                                7*bin_width+min_find};

    for (int i = 0; i < line_counter; i++) {
      if (find_times[i] < histogram_ticks_f[0])
        histogram_bins_f[0]++;
      else 
      {
        if (find_times[i] >= histogram_ticks_f[6])
          histogram_bins_f[7]++;
        else 
        {
          for (int g = 1; g < 5; g++) {
            if ((find_times[i] >= histogram_ticks_f[g]) && (find_times[i] < histogram_ticks_f[g+1]))
              histogram_bins_f[g]++;
          }
        } 
      }
    }

    // ofstream hist_file;
    hist_file.open(strcat(infile,"_find_hist"));
    for(int g = 0; g < 8; g++)
        hist_file << histogram_ticks_f[g-1] << " " << histogram_bins_f[g] << endl;

    FILE *of1;
    char filename[20];
    sprintf(filename, "avg_finds.txt"); 
    of1 = fopen(filename, "a");
    fprintf(of1, "%f\n", avg_find);
    fclose(of1);

    sprintf(filename, "avg_inserts.txt"); 
    of1 = fopen(filename, "a");
    fprintf(of1, "%f\n", avg_insert);


    return 0;
}