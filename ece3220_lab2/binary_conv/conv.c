#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	unsigned short dec_num;
	char opt; 
	int buf[16] = { 0 };

	printf("Enter a number: ");
	scanf("%hu", &dec_num);
	printf("Enter 'a' for arithmetic or 'b' for bitwise: ");
	scanf(" %c", &opt);
	switch(opt) 
	{
		case 'a':
		case 'A': {
				  // Arithmetic approach
				  int i=0;
				  int rem;
				  printf("Binary representation of %hu: ", dec_num);
				  while(dec_num > 0) 
				  {
					  buf[i] = dec_num % 2; 
					  dec_num /= 2; 
					  if(dec_num == 0)
						  break;
					  i++;
				  }
				  for(i=15; i>=0; i--)
				  {
					  printf("%d", buf[i]);
				  }
				  printf("\n");
				  break;
			  }
		case 'b':
		case 'B':
			  {
				  // Bitwise approach
				  unsigned int buf[16];
				  unsigned short bit;
				  int i=0;
			 	  unsigned short temp = 0x01;
				  do { 
					  bit = dec_num;
					  if(i > 0)
					  {
						  temp = temp << 1;
					  }

					  bit &= temp;
					  if(bit != 0)
					  {
						  buf[15-i] = 1;
					  }
					  else
					  {
						  buf[15-i] = 0;
					  }
					  i++;
				  }while(i<16);

				  for(i=0; i<16; i++)
				  {
					  printf("%d", buf[i]);
				  }
				  printf("\n");
				  break;
			}
	}
	return EXIT_SUCCESS;
}
