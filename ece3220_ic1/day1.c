#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int get_num(void);
int get_opt(char *);	
char buf[16];

#define NUM_MULTIPLES 10
#define NUM_POWERS 6

int main(int argc, char **argv) {
	// 1 -> 10 	
	int n;
	// opt can be 'p' => powers 
	// or 'm' => multiples
	char opt;
	int ret;

	// get integer number
	n = get_num();
	if( n == -1 ) 
	{
		printf("Try again.\n");
		n = get_num();
		if( n == -1)
			return EXIT_FAILURE;
	}
	// get parameter m -> multiples
	//	or p -> powers
	ret = get_opt(&opt);
	if(ret == -1)
	{
		printf("Try again.\n");
		ret = get_opt(&opt);
		if(ret == -1)
			return EXIT_FAILURE;
	}
	switch(opt)
	{
		int i;
		case 'm': {

					  for(i=0; i<NUM_MULTIPLES; i++)
					  {
						  printf("%d ", (n*(i+1)));
					  }
					  printf("\n");
					  break;
				  }
		case 'p': { 
					  for(i=1; i<NUM_POWERS+1; i++)
					  {
						  printf("%1.0lf ", pow( (double)n, (double)i ));
					  }
					  printf("\n");
					  break;
				  }
	}



	return EXIT_SUCCESS;

}

int get_num(void) {

	printf("Enter an integer between 2 and 10 inclusive: ");
	char *str = fgets(buf, 10, stdin);
	if(str == NULL)
		return -1;

	int n = atoi(str);
	if( (n < 2) || ( n > 10) )
	{
		return -1;
	}
	else
	{
		return atoi(buf); 
	}
}

int get_opt(char *opt) {

	printf("Display multiples or powers? (m/p): ");
	char *str = fgets(buf, 10, stdin);
	if(str == NULL)
	{
		return -1;
	}
	*opt = *str;

	if(*str != 'p' && *str != 'm') 
	{
		return -1;
	}
	else
	{
		return 0;	
	}
}

/* vim: set ts=4 sw=4 : */
