#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help(char **arg);
void read_file(char *file);
void write_file(char *, char **, int);
int main(int argc, char **argv) {
	
// ./ic3 -f filename -w line1 line2
// write line1 and line2 to line1 and line2 of filename

// ./ic3 -f filename -r 
//read filename and print to stdout. 

	if(argc < 2)
		print_help(argv);

	if( (argv[1][0] == '-' && argv[1][1] == 'f') )
	{
		// Check for the possibility of a -w or -r
		if(argc < 4)
		{
			print_help(argv);
		}
		char *input_file = argv[2];
	
		// Check if -w or -r 
		if(!(strcmp(argv[3], "-w")))
		{
			// -w
			if(argc < 5)
				print_help(argv);
			//else
			write_file(input_file, argv, argc);


		}
		else if(!(strcmp(argv[3], "-r")))
		{
			// print contents to stdout
			read_file(input_file);
		}
		else
			print_help(argv);

	}

	return EXIT_SUCCESS;
}

void write_file(char *file, char **lines, int len) {
	FILE *fp_w = fopen(file, "w");
	if(fp_w != NULL)
	{	
		for(int i=4; i<len; i++)
		{
			//write to file
			fprintf(fp_w, "%s\n", lines[i]);
		}
		fclose(fp_w);
		return;
	}
	exit(EXIT_FAILURE);
}

void print_help(char **argv) {
	printf("Usage is:\n\t%s -f [filename] -w <line1> <line2>\nor\n\t %s -f [filename] -r \n", argv[0], argv[0]);
	exit(EXIT_FAILURE);
}

void read_file(char *file) {
	FILE *fp_r = fopen(file, "r");
	char buf[256];
	if(fp_r != NULL)
	{
		while(fgets(buf, 256, fp_r))
		{
			printf("%s", buf);
		}
		
		// todo: check fclose()
		fclose(fp_r);
		return;

	}
	// Failed to open file
	exit(EXIT_FAILURE);
}


	
