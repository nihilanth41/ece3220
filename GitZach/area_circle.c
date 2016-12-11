#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359

int main(int argc, char **argv) {
	// compute area of circle
	//use printf/scanf
	double radius;	
	printf("Enter the radius: ");
	scanf("%lf", &radius);
	double area = (double)(PI)*pow(radius, 2);
	printf("Area of a circle with radius %lf is: %lf\n", radius, area);

	return 0;
}
	
//test comment
