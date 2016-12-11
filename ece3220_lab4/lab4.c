#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//global
int signal[2000] = { 0 };
double transform[2000] = { 0 };

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

int main(int argc, char **argv) {
	char opt, filename[32], outfilename[32];
	int len;
	double offset, scaling, factor;

	// # of file to open is cmd line arg
	if(argc < 2) 
	{
		printf("Usage is %s [file_number]\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Open file and populate global array
	sprintf(filename, "Raw_data_%02d.txt", atoi(argv[1]));
	printf("Filename is: %s\n", filename);
	len = populate_array(filename);
	if(len == -1) { return EXIT_FAILURE; }

	// Scale or offset?
	printf("Do you want to scale or offset? [s/o] ");
	fflush(stdout);
	scanf("%c", &opt);
	switch(opt) {
		case 'o':
		case 'O': {
				  //Offset
				  printf("Enter offset value: ");
				  scanf("%lf", &offset);
				  int i=0;
				  for(i=0; i<len; i++) 
				  {
					  transform[i] = (double)signal[i]+ offset;
				  }
				  sprintf(outfilename, "Offset_data_%02d.txt", atoi(argv[1]));
				  factor = offset;
				  break;
			  }
		case 's':
		case 'S': {
				  printf("Enter the scaling value: ");
				  scanf("%lf", &scaling);
				  int i=0;
				  for(i=0; i<len; i++) 
				  {
					  transform[i] = (double)signal[i]* scaling;
				  }
				  sprintf(outfilename, "Scaled_data_%02d.txt", atoi(argv[1]));
				  factor = scaling;
				  break;
			  }
		default: return EXIT_FAILURE;
	}

	// Write transform to file	
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

	// Find mean and max and write them to a file
	sprintf(outfilename, "Statistics_data_%02d.txt", atoi(argv[1]));
	int *iPtr = signal;
	double average = mean_value(iPtr, len);
	int maximum = max_value(iPtr, len);
	fp_w = fopen(outfilename, "w");
	if(fp_w != NULL)
	{
		fprintf(fp_w, "%0.4lf, %02d", average, maximum);
		fclose(fp_w);
	}

	// Center the signal
	sprintf(outfilename, "Centered_data_%02d.txt", atoi(argv[1]));
	fp_w = fopen(outfilename, "w");
	if(fp_w != NULL)
	{
		fprintf(fp_w, "%d %lf\n", len, average);
		int i;
		for(i=0; i<len; i++)
		{
			fprintf(fp_w, "%0.4lf\n", (signal[i] - average));
		}
		fclose(fp_w);
	}

	// Normalize the signal
	sprintf(outfilename, "Normalized_data_%02d.txt", atoi(argv[1]));
	fp_w = fopen(outfilename, "w");
	if(fp_w != NULL)
	{
		double scaling = (1/(double)maximum);
		fprintf(fp_w, "%d %lf\n", len, scaling);
		int i;
		for(i=0; i<len; i++)
		{
			fprintf(fp_w, "%0.4lf\n", (signal[i]*scaling));
		}
		fclose(fp_w);
	}


	return 0;
}
