#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
	char operator;
	double arg1, arg2, result;
	
	printf("Enter a number: ");
	scanf("%lf", &arg1);	
	printf("Enter an operator {+-*/}: ");
	scanf(" %c", &operator);	
	printf("Enter a number: ");
	scanf("%lf", &arg2);	

	switch(operator) 
	{
		case '+': 
			{
				result = arg1 + arg2;
				break;
			}
		case '-':
			{
				result = arg1 - arg2;
				break; 
			}
		case '*': 
			{
				result = arg1 * arg2;
				break;
			}
		case '/':
			{ 
				if(arg2 == 0)
				{
					printf("Error: divide by 0\n");
					return EXIT_FAILURE;
				}
				else
				{
					result = arg1 / arg2;
					break;
				}
			}
		default: 
			{
				printf("Error: Invalid operator\n");
				return EXIT_FAILURE;
			}
	}
	printf("%0.2lf %c %0.2lf = %0.2lf\n", arg1, operator, arg2, result);
	
	return EXIT_SUCCESS; 
}


