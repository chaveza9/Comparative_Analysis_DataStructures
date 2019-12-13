#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>



/* #define CAPACITY 10
#define LIMIT 501 */

#include "quadtree.h"

using namespace std; 

int randn(int lim)
{
	int a;
	a=rand()%lim;
	return a;
}

void requestInputs(int *numRandomPoints, int *quadCapacity, int *limit){
	printf("Define Number of Random Points to be Inserted: \n");
	scanf("%d", numRandomPoints);
	printf("Define Capacity of Quadtree: \n");
	scanf("%d", quadCapacity);
	printf("Define a limit of Quadtree (number between 100 and 1200: \n");
	scanf("%d", limit);
	if(*limit>1200)
		*limit = 1200;
	else if(*limit<100)
		*limit = 100;
}

void requestAreaQuery(Point *topLeft, Point *bottomRight, int limit){
	int x, y;
	printf("Define Top Left Coordinate between 0,0 and %d,%d: \n", limit, limit);
	printf("Example %d,%d: \n", randn(limit), randn(limit));
	scanf("%d,%d", &x, &y);
	topLeft->x = x;
	topLeft->y = y;
	printf("Define bottom right coordinate between %d,%d and %d,%d: \n", x, y, limit, limit);
	printf("Example %d,%d: \n", randn(limit), randn(limit));
	scanf("%d,%d", &x, &y);
	bottomRight->x = x;
	bottomRight->y = y;
}


int main()
{
	
	// Define User input Variables
	int numRandomPoints,quadCapacity, limit; 
	// Request user input
	requestInputs(&numRandomPoints, &quadCapacity, &limit);
	
	// Uti Variables
	int i, x[numRandomPoints],y[numRandomPoints];
	FILE *fp;
	time_t t;
	srand(time(&t));

	// WRITE THE RANDOM POINT FILE  
	fp = fopen("POINT.C","w");
 	if ( fp == NULL )
	{
		puts ( "Cannot open file" );
		exit(1);
	}
	// Create random points
	for(i=0;i<numRandomPoints;i++)
	{
		x[i]=randn(limit+1);
		y[i]=randn(limit+1);
		fprintf(fp,"%d,%d\n",x[i],y[i]);
	}
	fclose(fp); 
	// ALLOCATE MEMORY FOR POINTS ARRAY
	Node* pointArray = (Node*)malloc(sizeof(Node)*numRandomPoints);
	
	// READ THE RANDOM POINT FILE AND ASSIGN TO ROOT Node
	fp=fopen("POINT.C","r");
	if (fp == NULL){
		printf("FILE NOT FOUND");
		return 0;
	}
	for(i=0;i<numRandomPoints;i++)
	{
		if(fscanf(fp,"%d,%d",&x[i],&y[i]) != EOF)
		{
			pointArray[i].coordinates = *createPoint(x[i],y[i]);
			pointArray[i].data = 0; 				// No data in specific to be tested
			//printf("%d %d \n",x[i],y[i]);
		}
	}
	fclose(fp);
	printf("done");
	// Create empty quadTree
	quadtree qt(*createPoint(0,0), *createPoint(limit,limit), quadCapacity);
 	for(i=0;i < numRandomPoints;i++)
	{
		qt.insert_nodePR(&pointArray[i]);
	}
	// Create random point for region query
	Point topLeft, botRight;
	requestAreaQuery(&topLeft, &botRight, limit);
	qt.inRegion(topLeft,botRight);
	return 0;
}

