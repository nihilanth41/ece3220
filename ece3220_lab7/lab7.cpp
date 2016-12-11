#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <limits.h>

using namespace std;

class Signal { 
	private:
		int len;
		double max_val;
		double avg_val;
		double *data;
		void populate(const char *);
		void getAverage(void);
		void getMax(void);
	public:
		// Class methods
		void offset(double);
		void scale(double);
		void center(void);
		void normalize(void);
		void statistics(void);
		void menu(void);
		// Additional
		void Sig_info(void);
		void Save_file(const char *filename);
		// Constructors
		Signal();
		Signal(int fileno);
		Signal(const char *filename);
		// Destructor
		~Signal();
};

void print_help(char **argv) {
	cout << "Usage is: " << argv[0] << "[ -f <filename> ] or [ -n <file_number> ]" << endl;
	cout << "With no arguments uses filename Raw_data_01.txt" << endl;
	exit(EXIT_FAILURE);
}

void Signal::menu(void) {
	while(1)
	{
		cout << "\n1) Offset " << endl;
		cout << "2) Scale" << endl;
		cout << "3) Center" << endl;
		cout << "4) Normalize" << endl;
		cout << "5) Statistics" << endl;
		cout << "6) Print Signal" << endl;
		cout << "7) Save Signal" << endl;
		cout << "8) Exit" << endl;
		cout << "Select an option: ";
		int opt;
		cin >> opt;
		switch(opt)
		{
			case 1: { 	cout << "\nEnter the offset value: ";
					double val;
					cin >> val;
					offset(val);
					break;
				}
			case 2: { 	cout << "\nEnter the scale value: ";
				        double val;
					cin >> val;
					scale(val);
					break; 
				}
			case 3: { 	center(); 
					break;	
				}
			case 4: { 	normalize();
					break;
				}
			case 5: {	statistics();
					break;
				}
			case 6: {	Sig_info();
					break;
				}
			case 7:	{	cout << "Enter a filename: ";
					char *output_file = new char[32];
					cin >> output_file;
					Save_file(output_file);
					delete[] output_file;
					break;
				}
			case 8: {
					exit(EXIT_SUCCESS);
				}
			default: { 	 cout << "Invalid option" << endl; 
					 break;
				 }
		}
	}
}

				 

int main(int argc, char **argv) {
	
	/* Handle command line args */
	if(argc == 2)
		print_help(argv);

	if(argc > 2)
	{
		if(!(strcmp(argv[1], "-f")))
		{
			// Call constructor with filename
			Signal sig1 = Signal(argv[2]);
			sig1.Sig_info();
			sig1.menu();
		}
		else if(!(strcmp(argv[1], "-n")))
		{
			// Call constructor with number arg
			// E.g. 2 => Raw_data_02.txt
			Signal sig1 = Signal(atoi(argv[2]));
			sig1.Sig_info();
			sig1.menu();
		}
	}
	else {
		// No cmd line arguments, call default constructor
		Signal sig1 = Signal();
		sig1.Sig_info();
		sig1.menu();
	}
	
	
	return 0;	
}




void Signal::Save_file(const char *filename) {
	FILE *fp_w = fopen(filename, "w");
	if(fp_w != NULL)
	{	
		fprintf(fp_w, "%d %0.4lf\n", len, max_val);
		for(int i=0; i<len; i++)
		{
			fprintf(fp_w, "%0.4lf\n", *(data+i));
		}
		fclose(fp_w);
	}
}
	
void Signal::offset(double offset_val) {
	int i=0;
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) += offset_val;
	}
	// Update data members
	getAverage();
	getMax();

}

void Signal::scale(double scale_val) {
	int i=0;
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) *= scale_val;
	}
	// Update data members
	getAverage();
	getMax();
}

void Signal::center(void) {
	int i=0;
	// Ensure average is accurate
	getAverage();
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) -= avg_val;
	}
	// Update data members
	getAverage();
	getMax();
}

void Signal::normalize(void) {
	int i=0;
	// Ensure max_val is accurate
	getMax();
	// Update data array
	for(i=0; i<len; i++)
	{
		*(data+i) /= max_val;
	}
	// Update data members
	getAverage();
	getMax();
}

void Signal::statistics(void) {
	cout << "\nAverage: " << avg_val << endl;
	cout << "Max value: " << max_val << endl;
}

void Signal::Sig_info(void) {
/* Display length, current maximum, current average */
	cout << "\nSignal length: " << len << endl;
	cout << "Maximum val:" << max_val << endl;
	cout << "Average val:" << avg_val << endl;
}

/* Private */

void Signal::populate(const char *filename) {
/* Reads data from file into data array */
	FILE *fp_r = fopen(filename, "r");
	if(fp_r == NULL)
	{
		cout << "Error opening file" << endl;
	}
	else
	{
		fscanf(fp_r, "%d %lf", &len, &max_val);
		// allocate memory for signal
		data = new double[len];
		int i=0;
		for(i=0; i<len; i++)
		{
			// Load data into array 
			fscanf(fp_r, "%lf", data+i);
		}
		fclose(fp_r);
	}
}

void Signal::getAverage(void) {
	int i=0;
	avg_val = 0;
	for(i=0; i<len; i++)
	{
		avg_val += *(data+i);
	}
	avg_val /= (double)len;
}

void Signal::getMax(void) {
	max_val = (double)INT_MIN;
	int i=0;
	for(i=0; i<len; i++)
	{
		if( *(data+i) > max_val )
		{
			max_val = *(data+i);
		}
	}
}	

Signal::Signal() {
/* Takes default file and allocates memory accordingly */
	const char *filename = "Raw_data_01.txt";
	populate(filename);
	getAverage();
	getMax();
}

Signal::Signal(int fileno) {
	char filename[32];
	sprintf(filename, "Raw_data_%02d.txt", fileno);
	populate(filename);
	getAverage();
	getMax();
}

Signal::Signal(const char *filename) {
	populate(filename);
	getAverage();
	getMax();
}

Signal::~Signal() {
	// Free memory allocated at runtime
	delete[] data;
}
