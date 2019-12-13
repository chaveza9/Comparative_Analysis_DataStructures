# Quadtrees

The quadtree implementation contains tree folders. Each folder and its content is explained as follows:
1. quadtrees: 
---
⋅⋅⋅Contains a full implementation of quadtrees with visualization. In order to properly compile the code for this implementation, an installed version of opencv library is needed as the quadtree.h library contains opencv dependancies for vizualisation. In order to run the code just go inside the quadtree folder and run make. If an existing version of opencv is present on the OS, the file should run. To run the file, perform the following steps:
⋅⋅1. Run ./Quadtree
⋅⋅2. Insert the total amount of random points to be inserted in a quadtree
⋅⋅3. Define the capacity of every quadtree node. This number should be greater than 0
⋅⋅4. Define a bounding limit of the quadtree. This limit should be a number between 100 and 1200. This limit would generate a rectangle defined by the top left coordinates x = 0,y = 0 and bottom right coordinates x= limit, y = limit. The numbers for the limit are bounded between 100 and 1200 so the generated plot is big enough to be shown and also not too big that it would not fit a screen. After this step, one should see a window pop up with an image of the generated quadtree as shown below:

![alt text](https://github.com/chaveza9/Comparative_Analysis_DataStructures/Quadtrees/images/PR.png "Quadtree Build")
⋅⋅5 Press any key while Quadtree window is open
⋅⋅6 A Message will appear on the console requesting a coordinate that would represent the top left coordinate of a rectangle to generate a query. Define two numbers separated by a comma with no spaces inbetween, example 2,100
⋅⋅7 Similarly, another message will appear on the console requesting a coordinate that would represent the bottom right coordinate of a rectangle to generate a query. Define two numbers separated by a comma with no spaces inbetween, example 400,110
⋅⋅8 The Quadtree window should now show a blue rectangle as defined by the user. Also, the points inside the blue rectangle region would have a green bounding circle around them representing the extracted points
![alt text](https://github.com/chaveza9/Comparative_Analysis_DataStructures/Quadtrees/images/PR_query.png "Quadtree Build")

2. quadtrees_no_graphics: 
---
⋅⋅⋅Contains a full implementation of quadtrees with no visualization. This is just representation only prints values to the console and generates a a file called POINT.c that containes the points generated for the quadtree. To run the file, perform the following steps:
⋅⋅1. Run ./Quadtree
⋅⋅2. Insert the total amount of random points to be inserted in a quadtree
⋅⋅3. Define the capacity of every quadtree node. This number should be greater than 0
⋅⋅4. Define a bounding limit of the quadtree. This limit should be a number between 100 and 1200. This limit would generate a rectangle defined by the top left coordinates x = 0,y = 0 and bottom right coordinates x= limit, y = limit. g "Quadtree Build")
⋅⋅5 A Message will appear on the console requesting a coordinate that would represent the top left coordinate of a rectangle to generate a query. Define two numbers separated by a comma with no spaces inbetween, example 2,100
⋅⋅6 Similarly, another message will appear on the console requesting a coordinate that would represent the bottom right coordinate of a rectangle to generate a query. Define two numbers separated by a comma with no spaces inbetween, example 400,110
⋅⋅7 The console will print all the data points contained within the specified area
⋅⋅8 If the user needs a separate file for the query, just run ./Quadtree>>NAMEOFOUTPUTFILE

2. quadtrees_Benchmarking: 
---
⋅⋅⋅This folder contains the data sets used for the genration of histograms shown in the report. Here, a file with the reporting times of the insertion, find, and nearest neighbour computation time is generated. 
⋅⋅1. In order to run this version, the user needs to compile the code by running make all
⋅⋅2. After the code has been compiled, the user can run one of the following commands in order to generate a benchmarking file
⋅⋅* make run_random_data_100
⋅⋅* make run_random_perm_data_100
⋅⋅* make run_random_data_1000
⋅⋅* make run_random_perm_data_1000
⋅⋅* make run_random_data_100K
⋅⋅* make run_random_perm_data_100K
⋅⋅* make run_random_data_1M
⋅⋅* make run_random_perm_data_1M




