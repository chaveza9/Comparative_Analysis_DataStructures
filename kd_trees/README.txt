Important to note:

- Format for Input files (.txt):
    n d
    x1 y1
    x2 y2
    . . .
    xn yn
    So "n" is the number of data points in the file. "d" is the dimension. While the kd-tree has been built for k dimensions, it has only been tested for true. Try k dimensions at your own risk!

To run:

- make the Makefile
- run ./main
- enter then name of the .txt file to input into the program
- name of the output file will have the time to build and time to do 100 random finds on the built tree.
- name of the output file will be n_d_insert_find_times.txt

Key to note:

- delete_node was run on simple test cases but failed on benchmark datasets. For this reason the main file never calls for delete_node.



