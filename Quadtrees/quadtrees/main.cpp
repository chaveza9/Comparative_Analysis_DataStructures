#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <stdlib.h>
#include <opencv2/highgui.hpp>

//#define CAPACITY 1000
//#define LIMIT 501

#include "quadtree.h"

using namespace std; 

int randn(int lim)
{
	int a;
	a=rand()%lim;
	return a;
}
// Draw Points onto Quadtree
void drawPt(cv::Mat *Img, cv::Point Cntr, cv::Scalar color){
	cv::circle(*Img,  Cntr, 3,  color, CV_FILLED, cv::LINE_8);
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
	Point *Pt = createPoint(randn(limit),randn(limit));
    
	// Define Drawing parameters
	char rook_window[] = "Quadtree";
	cv::Mat rook_image((limit),(limit), CV_8UC3, cv::Scalar(255,255,255));
	// Draw points on Quadtree
	for(i=0;i<numRandomPoints;i++)
	{
		drawPt(&rook_image,cv::Point(pointArray[i].coordinates.x,pointArray[i].coordinates.y),cv::Scalar( 0, 0, 255 ));
	}

	// Show Quad regions
	qt.show(&rook_image);

	// Show images
	cv::imshow( rook_window, rook_image );
	cv::moveWindow( rook_window, limit, 200 );
	cv::waitKey(0); 
	// Select ROI
	Point topLeft, botRight;
	requestAreaQuery(&topLeft, &botRight, limit);
	qt.inRegion(topLeft,botRight);

	printf("%d,%d",topLeft.x,topLeft.y);
	qt.drawInRegion(&rook_image, topLeft, botRight);
	qt.show(&rook_image);
    // Display Cropped Image
    cv::imshow( rook_window, rook_image );

	cv::waitKey(0);
	return 0;
}

