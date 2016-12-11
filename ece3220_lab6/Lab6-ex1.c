#include <stdio.h>
 
int main()
{
    char* fileName;
    printf("Specify file name you would like to print to: \n");
    scanf("%s",fileName);
 


 


	FILE* file1 = fopen(fileName, "a+");
	int c;
if(file1 != NULL)
{
	
    while ((c=getchar()) != EOF)
    {
        fprintf(file1, "%d", c);
    }
    fclose(file1);
 }

 
    printf("CTRL+d is a correct ending");
 
    return 0;
}
