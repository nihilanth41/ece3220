#include <stdio.h>

int factorial ( int num )
{
	if(num == 0)
	{
		return 1;
	}
	else
		return num * factorial( num - 1 );
}

int main(void)
{
    int no,ans;
    printf("Enter the number \n");
    scanf( "%d", &no );
    ans = factorial( no );
    printf("The factorial is %d ", ans );
    return 0;
}
