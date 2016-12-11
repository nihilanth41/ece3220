#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	if(argc < 3) { 
		printf("Usage is %s [item cost] [sale price]\n", argv[0]);
		return EXIT_FAILURE;
	}
	double paid = atof(argv[1]);
	double made = atof(argv[2]);
	int isProfit = 0;
	double magnitude = 0;
	//determine profit/loss
	if(paid < made) 
	{
		magnitude = made - paid;
		printf("Sale was profitable. Made $%0.2lf\n", magnitude);
	}
	else
	{
		magnitude = paid - made;
		printf("Sale was at a loss. Lost $%0.2lf\n", magnitude);
	}
	
	return EXIT_SUCCESS; 
}
