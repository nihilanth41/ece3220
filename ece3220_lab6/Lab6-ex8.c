#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
	char *s, *dyn_s;
	s = malloc(sizeof(s)*256);
	int ln;
	printf("Enter the input string\n");
	scanf("%s",s);
	ln = strlen(s);
	dyn_s = (char*)malloc(strlen(s)+1);

	free(dyn_s);

	dyn_s = s;
	dyn_s[strlen(s)]='\0';

	printf("%s", dyn_s);

	free(s);
	return 0;
}

