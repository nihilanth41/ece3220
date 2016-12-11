#include<stdio.h>
#include<malloc.h>
void main()
{
    char *a = "hey";
    //free(a);
    a = "hello";   
    printf("%s",a);
}
