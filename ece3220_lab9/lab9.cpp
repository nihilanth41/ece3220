#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <vector>
#include <sstream>

using namespace std;

class Signal { 
	private:
		double max_val;
		double avg_val;
		void populate(string);
	public:
		int len;
		vector<double> data;
		void getAverage(void);
		void getMax(void);
		// Class methods
		void offset(double);
		void scale(double);
		void center(void);
		void normalize(void);
		void statistics(void);
		void menu(void);
		// Additional
		void Sig_info(void);
		void Save_file(string);
		// Constructors
		Signal();
		Signal(int fileno);
		Signal(string filename);
		// Member Operators
		// Offset
		void operator+(double);
		//Scale
		void operator*(double);
};

// These are member functions because they need to be able to access private members

// For offset
void Signal::operator+(double offset) {
	// Update data array
	for(int i=0; i<len; i++)
	{
		data[i] += offset;
	}
}

// For scale
void Signal::operator*(double scale) {
	// Update data array
	for(int i=0; i<len; i++)
	{
		data[i] *= scale;
	}
}

// Non member function operator
Signal operator+(const Signal &lhs, const Signal &rhs) {
	// Objects must be same size
	if(lhs.len != rhs.len)
	{
		cout << "Error: objects are not of same length" << endl;
		exit(-1);
	}
	else
	{
		Signal sum;
		sum.len = lhs.len;
		for(int i=0; i<sum.len; i++)
		{
			// use push_back to grow vector 
			sum.data.push_back(lhs.data[i]);
			sum.data[i] += rhs.data[i];
		}
		sum.getAverage();
		sum.getMax();
		return sum;
	}
}
	
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
					string output_file;
					cin >> output_file;
					Save_file(output_file);
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
			string filename(argv[2]);
			Signal sig1 = Signal(filename);
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
		// Demonstrate the non-member overloaded addition
		// In this case the average of sums happens to be the sum of averages.
		// Same story for the maximum, b/c the signals are identitical
		Signal sig2 = Signal(1);
		Signal sig3 = Signal(2);
		Signal sig4 = sig2 + sig3;
		sig4.Sig_info();

		Signal sig1 = Signal();
		sig1.Sig_info();
		sig1.menu();
	}
	
	
	return 0;	
}

void Signal::Save_file(string filename) {
	FILE *fp_w = fopen(filename.c_str(), "w");
	if(fp_w != NULL)
	{	
		fprintf(fp_w, "%d %0.4lf\n", len, max_val);
		for(int i=0; i<len; i++)
		{
			fprintf(fp_w, "%0.4lf\n", data[i]);
		}
		fclose(fp_w);
	}
}
	
void Signal::offset(double offset_val) {
	this->operator+(offset_val);
	// Update data members
	getAverage();
	getMax();
}

void Signal::scale(double scale_val) {
	this->operator*(scale_val);
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
		data[i] = data[i]-avg_val;
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
		data[i] = data[i]/max_val;
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

void Signal::populate(string filename) {
/* Reads data from file into data array */
	FILE *fp_r = fopen(filename.c_str(), "r");
	if(fp_r == NULL)
	{
		cout << "Error opening file" << endl;
	}
	else
	{
		fscanf(fp_r, "%d %lf", &len, &max_val);
		// allocate memory for signal
		int i=0;
		double tmp;
		for(i=0; i<len; i++)
		{
			// Load data into array 
			fscanf(fp_r, "%lf", &tmp);
			data.push_back(tmp);
		}
		fclose(fp_r);
	}
}

void Signal::getAverage(void) {
	int i=0;
	avg_val = 0;
	for(i=0; i<len; i++)
	{
		avg_val += data[i];
	}
	avg_val /= (double)len;
}

void Signal::getMax(void) {
	max_val = (double)INT_MIN;
	int i=0;
	for(i=0; i<len; i++)
	{
		if( data[i] > max_val )
		{
			max_val = data[i];
		}
	}
}	

Signal::Signal() {
	len=0;
	max_val=0.0;
	avg_val=0.0;
}

Signal::Signal(int fileno) {
	// Easiest way for some reason?
	// Maybe there's a better way to format in C++ w/ strings but I couldn't figure it out.
	char buf[32];
	sprintf(buf, "Raw_data_%02d.txt", fileno);
	string filename(buf);
	populate(filename);
	getAverage();
	getMax();
}

Signal::Signal(string filename) {
	populate(filename);
	getAverage();
	getMax();
}

