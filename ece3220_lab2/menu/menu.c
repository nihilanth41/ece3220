#include <stdlib.h>
#include <stdio.h>

#define FACTORIAL_MAX_INPUT 33

int main(int argc, char **argv) {
	char opt; 

	do {
		printf("\n\n1. Factorial\n2. Leap year\n3. max(a, b)\n4. div(a, b)\n5. Exit\n");
		printf("\nEnter an option: ");
		scanf(" %c", &opt);
		switch(opt)
		{
			case '1': 
				{
					// Factorial 
					unsigned short input;
					unsigned long output = 1;
					printf("Enter a number: ");
					scanf("%hu", &input); 
					if(input > FACTORIAL_MAX_INPUT)
					{
						printf("Number too large.\n");
						return EXIT_FAILURE;
					}
					else 
					{
						int i;
						for(i=1; i<(input+1); i++)
						{
							output *= i;
						}
						printf("%hu! is %lu.\n", input, output);
					}
					break;
				}
			case '2': 
				{
					// Find leap year
					unsigned int year; 
					int isLeap = 0;
					printf("Enter a year (YYYY): ");
					scanf("%u", &year);
					if( (year % 4) == 0 )
					{
						if( (year % 100) == 0) 
						{
							
							if( (year % 400) == 0)
							{
								isLeap = 1;
							}
						}
						else
						{
							//divisible by 4 but not 100
							isLeap = 1;
						}
					}
					if(isLeap == 1) 
					{
						printf("Year %u IS a leap year.\n", year);
					}
					else
					{
						printf("Year %u IS NOT a leap year.\n", year);
					}
					break;
				}
			case '3': 
				{
					// Maximum 
					float f1, f2;
					printf("Enter a float: ");
					scanf("%f", &f1);
					printf("Enter another float: ");
					scanf("%f", &f2);
					printf("\nMax: ");
					(f1 > f2) ? printf("%0.1f", f1) : printf("%0.1f", f2);
					break;
				}
			case '4': 
				{
					// Division
					int n1, n2;
					float result;
					printf("Enter the int dividend: ");
					scanf("%d", &n1);
					printf("Enter the int divisor: ");
					scanf("%d", &n2);
					if(n2 == 0)
					{
						printf("Err: divide by 0\n");
						return EXIT_FAILURE;
					}
					result = (float)n1/n2;
					printf("%d / %d = %f\n", n1, n2, result);
					break;
				}
			case '5':
				{
					return EXIT_SUCCESS;
				}
			default: 
				{
					break;
				}
		}
	}while(1);
	
}


