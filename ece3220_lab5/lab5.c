#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Modify to take args
//-n File # 
//-o: offset value (value needed) 
//-s: scale factor (value needed) 
//-S: Get statistics 
//-C: Center the signal 
//-N: Normalize signal 
//-r: Rename files (name needed) 
//-h: Help (display how the program should be called, including the different input options)

int populate_array(char *);
double mean_value(int *, int);
int max_value(int *, int);
void print_help(char *);
void write_file(char *, int, double);

//global
int signal[2000] = { 0 };
double transform[2000] = { 0 };

int main(int argc, char **argv) {
	char opt, filename[32], outfilename[32];
	int len;
	double offset, scaling;

	// Command line args
	int fileNo = 0, writeStat=0, writeNorm=0, writeCenter=0;
	char *file_rename = NULL;

	// # of file to open is cmd line arg
	if(argc < 2) 
	{
		print_help(argv[0]);
		return EXIT_FAILURE;
	}

	// Parse all options before performing anything
	int i=0;
	for(i=0; i<argc; i++)
	{
		//printf("Index: %d, Str: %s\n", i, argv[i]);
		if(argv[i][0] == '-')
		{
			// If we encounter 'help' print help and exit
			// without performing other operations
			if(argv[i][1] == 'h' || argv[i][1] == 'H')
			{
				print_help(argv[0]);
				return EXIT_SUCCESS;
			}
			switch(argv[i][1])
			{
				case 'n': { 
							  if(i+1 < argc)
							  {
								  fileNo = atoi(argv[i+1]); 
							      sprintf(filename, "Raw_data_%02d.txt", fileNo);
							  }
							  break; 
						  }

				case 'o': { 
							  if(i+1 < argc)
							  {
								  offset = strtod(argv[i+1], NULL);
							  }
							  break;
						  }
				case 's': { 
							  if(i+1 < argc)
							  {
								scaling = strtod(argv[i+1], NULL); 
							  }
							  break; 
						  }
				case 'S': { writeStat = 1; break; }
				case 'C': { writeCenter = 1; break; }
				case 'N': { writeNorm = 1; break; }
				case 'r': { 
							  if(i+1 < argc)
							  {
								file_rename = argv[i+1]; 
							  }
							  break;
						  }
			}
		}
	}
	if(fileNo == 0)
	{
			printf("Need more arguments\n");
			print_help(argv[0]);
			return EXIT_FAILURE;
	}

	if(file_rename != NULL)
	{
		sprintf(outfilename, "%s.txt", file_rename);
	}

	//// Open file and populate global array
	sprintf(filename, "Raw_data_%02d.txt", fileNo);
	printf("Input file is: %s\n", filename);
	len = populate_array(filename);
	if(len == -1) { return EXIT_FAILURE; }

	// Offset
	if((int)offset != 0)
	{
		printf("Offset value %lf\n", offset);

				  int i=0;
				  for(i=0; i<len; i++) 
				  {
					  transform[i] = (double)signal[i]+ offset;
				  }
				  if(file_rename == NULL)
				  {
					  sprintf(outfilename, "Offset_data_%02d.txt", fileNo); 
				  }
				  else
				  {
					  sprintf(outfilename, "%s_Offset.txt", file_rename); 
				  }
				  write_file(outfilename, len, offset);
	}

	// Scaling
	if((int)scaling != 0)
	{
		printf("Scaling value: %lf\n", scaling);
			int i=0;
			for(i=0; i<len; i++) 
			{
				transform[i] = (double)signal[i]*scaling;
			}
			if(file_rename == NULL)
			{
				sprintf(outfilename, "Scaled_data_%02d.txt", fileNo); 
			}
			else
			{
				sprintf(outfilename, "%s_Scaled.txt", file_rename); 
			}
			write_file(outfilename, len, scaling);
	}

	// Statistics
	//// Find mean and max 
	int *iPtr = signal;
	double average = mean_value(iPtr, len);
	int maximum = max_value(iPtr, len);

	// Center the signal
	if(writeCenter)
	{
		int i;
		for(i=0; i<len; i++)
		{
			transform[i] = ((double)signal[i] - average);
		}
		if(file_rename == NULL)
		{
			sprintf(outfilename, "Centered_data_%02d.txt", fileNo);
		}
		else
		{
			sprintf(outfilename, "%s_Centered.txt", file_rename);
		}
		write_file(outfilename, len, average);
	}

	// Normalize the signal
	if(writeNorm)
	{
		double scaling = (1/(double)maximum);
		int i;
		for(i=0; i<len; i++)
		{
			transform[i] = ((double)signal[i]*scaling);
		}
		if(file_rename == NULL)
		{
			sprintf(outfilename, "Normalized_data_%02d.txt", fileNo);
		}
		else
		{
			sprintf(outfilename, "%s_Normalized.txt", file_rename);
		}
		write_file(outfilename, len, scaling);
	}

	if(writeStat)
	{
		if(file_rename == NULL)
		{
			sprintf(outfilename, "Statistics_data_%02d.txt", fileNo);
		}
		else
		{
			sprintf(outfilename, "%s_Statistics.txt", file_rename);
		}
		printf("Writing file %s\n", outfilename);
		// Find mean and max and write them to a file
		int *iPtr = signal;
		double average = mean_value(iPtr, len);
		int maximum = max_value(iPtr, len);
		FILE *fp_w = fopen(outfilename, "w");
		if(fp_w != NULL)
		{
			fprintf(fp_w, "%1.4lf, %02d", average, maximum);
		}
		fclose(fp_w);
	}

	// Check if -r option is passed by itself. 
	// In that case copy the original file 
	if(file_rename != NULL && ( !((int)scaling) && !((int)offset) && !writeStat && !writeNorm && !writeCenter ))  
	{
		FILE *fp_r, *fp_w;
		char buf[256];
		// Didn't design this well 
		// At this point its easiest to just read the original file again
		sprintf(outfilename, "%s.txt", file_rename);
		printf("Copying file %s to %s\n", filename, outfilename);
		fp_r=fopen(filename, "r");
		fp_w=fopen(outfilename, "w");
		if(fp_w != NULL && fp_r != NULL)
		{
			while(fgets(buf, 256, fp_r))
			{
				fprintf(fp_w, "%s", buf);
			}
		}
		fclose(fp_w);
		fclose(fp_r);
	}
		
	return 0;
}

// input: filename str
// output: length of input
int populate_array(char *filename)
{
	int len, max;
	FILE *fp_r = fopen(filename, "r");
	if(fp_r == NULL)
	{
		return -1;
	}
	else
	{
		fscanf(fp_r, "%d %d", &len, &max);
		printf("Number of entries: %d\n", len);
		printf("Upper bound: %d\n", max);
		int i=0;
		for(i=0; i<max; i++)
		{
			fscanf(fp_r, "%d", signal+i);
		}
		fclose(fp_r);
	}
	return len;
}

double mean_value(int *i_array, int len)
{
	double mean = 0;

	int i=0;
	for(i=0; i<len; i++)
	{
		mean += *(i_array+i); 
	}
	mean /= (double)len;

	return mean;
}

int max_value(int *i_array, int len)
{
	int i;
	int max=INT_MIN;
	for(i=0; i<len; i++)
	{
		if( *(i_array+i) > max ) 
		{
			max = *(i_array+i);
		}
	}
	return max;
}

void print_help(char *progname) {
	printf("Usage is: %s \n", progname);
	printf("-n [file number] \n");
	printf("-o [offset value]\n");
	printf("-s [scale factor]\n");
	printf("-S Get Statistics \n");
	printf("-C Center Signal \n");
	printf("-N Normalize Signal \n");
	printf("-r [filename] Rename file\n");
	printf("-h Display Help\n\n");
	printf ("Minimum required: %s -n [file number]\n", progname);
	return;
}

void write_file(char *outfilename, int len, double factor) 
{
		FILE *fp_w = fopen(outfilename, "w");
		if(fp_w != NULL)
		{
			fprintf(fp_w, "%d %0.4lf\n", len, factor);
			int i;
			for(i=0; i<len; i++)
			{
				fprintf(fp_w, "%0.4lf\n", transform[i]);
			}
			fclose(fp_w);
			printf("Wrote transform to file: %s\n", outfilename);
		}
}


/* vim: set ts=4 sw=4: */ 
