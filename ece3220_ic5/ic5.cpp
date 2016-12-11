// Group members: 
// Zachary Rump, zrrm74@mail.missouri.edu
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>

using namespace std;

// --------- BaseSig class and methods ------------------------------
class BaseSig{
	private:
		// neither derived classes nor other users
		// can access private members
	
	protected:	// accessible by derived classes, not by other users.
		int length;
		int *raw_data;
		void populate(int fileno);
		
	public:
		BaseSig();		// default constructor.
		BaseSig(int fileno);	// parametric constructor
		~BaseSig();		// destructor
		int getLength() { return length; };
		int getRawValue(int pos);
		static int numObjects;	// static, only one member for the entire hierarchy
		virtual void printInfo();
};

void BaseSig::populate(int fileno) {
	char filename[32];
	int ret;
	ret = sprintf(filename, "Raw_data_%02d.txt", fileno);
	FILE *fp_r = fopen(filename, "r");
	if(fp_r == NULL)
	{
		cout << "Error opening file" << endl;
	}
	else
	{
		// Ignore max value in the base class? 
		// Add member for it in derived class?
		int max_val;
		fscanf(fp_r, "%d %d", &length, &max_val);
		// allocate memory for signal
		raw_data = new int[length];
		if(raw_data == NULL)
			cerr << "Error in memory allocation";
		int i=0;
		for(i=0; i<length; i++)
		{
			// Load data into array 
			fscanf(fp_r, "%d", raw_data+i);
		}
		fclose(fp_r);
	}
}


int BaseSig::numObjects = 0;	// initialize static data member

// Base class constructor
BaseSig::BaseSig(){
	length = 0;
	raw_data = NULL;
	numObjects++;
	// Default constructor uses fileno 1
	populate(1);
}

// Base class parametric constructor
// Note that the data array is not being initialized (we could read from a file)
BaseSig::BaseSig(int fileno){
	numObjects++;
	populate(fileno);
}

// Base class destructor
BaseSig::~BaseSig(){
	delete[] raw_data;
	cout << "Goodbye, BaseSig." << endl;
}

int BaseSig::getRawValue(int pos) {
	if(pos < 0)			// invalid index
		return(raw_data[0]);
	else if(pos >= length)	// invalid index
		return(raw_data[length-1]);	
	else
		return(raw_data[pos]);
}

void BaseSig::printInfo() {
	cout << "\nLength: " << length << endl;
}
// ------------------------------------------------------------------
// --------- ProcessedSignal class & methods  ----------------------------

class ProcessedSignal : public BaseSig {
	//ProcessedSignal is derived from class BaseSig
	private:
		double average;
		double max_val;
		double min_val;
		double *data;
	public:
		ProcessedSignal(int fileno);
		~ProcessedSignal();

		// functions from extendSig
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage(void);
		// new member functions
		double getMax(void);
		double getMin(void);
		void Normalize(void);
		
		// redefine member function. Virtual keyword not needed
		void printInfo();	// new standard: explicit "override" keyword can be used
};

// Derived class constructor. Note how the Base constructor is called.
ProcessedSignal::ProcessedSignal(int fileno) : BaseSig(fileno) {
	data = new double[length];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 0; i < length; i++)
			data[i] = (double)raw_data[i];
		average = getAverage();
		max_val = getMax();
		min_val = getMin();
	}
}

ProcessedSignal::~ProcessedSignal() {
	//delete raw_data;
	delete data;
	cout << "Goodbye, ProcessedSignal." << endl;
}

void ProcessedSignal::Normalize(void) {
	// Dont care about wasted cycles;
	// Just in case
	max_val = getMax();

	for(int i=0; i<length; i++)
	{
		data[i] /= max_val;
	}
	average = getAverage();
	max_val = getMax();
	min_val = getMin();
}

double ProcessedSignal::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);	
	else
		return(data[pos]);
}

int ProcessedSignal::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		max_val = getMax();
		min_val = getMin();
		return(0);	// success
	}
}

double ProcessedSignal::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++)
			temp += data[i];
		return(temp/(double)length);
	}
}

double ProcessedSignal::getMax(void) {
	double tmp_max = (double)INT_MIN;
	for(int i=0; i<length; i++)
	{
		if(data[i] > tmp_max);
		tmp_max = data[i];
	}
	return tmp_max;
}

double ProcessedSignal::getMin(void) {
	double tmp_min = (double)INT_MAX;
	for(int i=0; i<length; i++)
	{
		if(data[i] < tmp_min);
		tmp_min = data[i];
	}
	return tmp_min;
}

void ProcessedSignal::printInfo() {
	cout << "\nLength: "  << length  << endl;
	cout << "Average: " << average << endl;
	cout << "Maximum: " << max_val << endl;
	cout << "Minimum: " << min_val << "\n" << endl;
}




// --------- extendSig class and methods ----------------------------
class ExtendSig : public BaseSig{ // ExtendSig is derived from class BaseSig
//BaseSig is a public base class
	private: 
		double average;		// add new data members
		double *data;
		
	public:
		ExtendSig(int L);	//derived classes need a new constructor
		~ExtendSig();
		
		// define new member functions
		double getValue(int pos);
		int setValue(int pos, double val);
		double getAverage();
		
		// redefine member function. Virtual keyword not needed
		void printInfo();	// new standard: explicit "override" keyword can be used
};

// Derived class constructor. Note how the Base constructor is called.
ExtendSig::ExtendSig(int fileno) : BaseSig(fileno) {
	data = new double[length];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 0; i < length; i++)
			data[i] = (double)raw_data[i];
		average = getAverage();
	}
}

// Derived class destructor
ExtendSig::~ExtendSig() {
	//delete raw_data;
	delete data;
	cout << "Goodbye, ExtendSig." << endl;
}

double ExtendSig::getValue(int pos) {
	if(pos < 0)			// invalid index
		return(data[0]);
	else if(pos >= length)	// invalid index
		return(data[length-1]);	
	else
		return(data[pos]);
}

int ExtendSig::setValue(int pos, double val) {
	if((pos < 0) || (pos >= length))
		return(-1);	// invalid index
	else {
		data[pos] = val;
		average = getAverage();
		return(0);	// success
	}
}

double ExtendSig::getAverage() {
	if(length == 0)
		return(0.0);
	else {
		double temp = 0.0;
		for(int i = 0; i < length; i++)
			temp += data[i];
		return(temp/(double)length);
	}
}

// Redefined printInfo function for derived class
void ExtendSig::printInfo() {
	cout << "\nLength: " << length << endl
		 << "Average: " << average << endl;
}
// ------------------------------------------------------------------

class ProcessedSignal_v2 : public ExtendSig {
	private: 
		double average;
		double max_val;
		double min_val;
		double *data;
	public:
		double getMax(void);
		double getMin(void);
		void Normalize(void);
		ProcessedSignal_v2(int fileno);
		~ProcessedSignal_v2();

		void printInfo();
};


ProcessedSignal_v2::ProcessedSignal_v2(int fileno) : ExtendSig(fileno) {
	data = new double[length];
	if(data == NULL)
		cerr << "Error in memory allocation";
	else{
		for(int i = 0; i < length; i++)
			data[i] = (double)raw_data[i];
		average = getAverage();
		max_val = getMax();
		min_val = getMin();
	}
}

ProcessedSignal_v2::~ProcessedSignal_v2() {
	//delete raw_data;
	delete data;
	cout << "Goodbye, ProcessedSignal_v2." << endl;
}

void ProcessedSignal_v2::Normalize(void) {
	// Dont care about wasted cycles;
	// Just in case
	max_val = getMax();

	for(int i=0; i<length; i++)
	{
		data[i] /= max_val;
	}
	average = getAverage();
	max_val = getMax();
	min_val = getMin();
}

void ProcessedSignal_v2::printInfo() {
	cout << "\nLength: "  << length  << endl;
	cout << "Average: " << average << endl;
	cout << "Maximum: " << max_val << endl;
	cout << "Minimum: " << min_val << "\n" << endl;
}

double ProcessedSignal_v2::getMax(void) {
	double tmp_max = (double)INT_MIN;
	for(int i=0; i<length; i++)
	{
		if(data[i] > tmp_max);
		tmp_max = data[i];
	}
	return tmp_max;
}

double ProcessedSignal_v2::getMin(void) {
	double tmp_min = (double)INT_MAX;
	for(int i=0; i<length; i++)
	{
		if(data[i] < tmp_min);
		tmp_min = data[i];
	}
	return tmp_min;
}

// ------------------------------------------------------------------
// Main function. A few examples
int main(){
	
	cout << "ProcessedSignal1 using Raw_data_01.txt:" << endl;
	ProcessedSignal psig1(1);
	// PrintInfo
	psig1.printInfo();
	// Make sure getVal(), setVal() still work
	cout << "Position 5: " << psig1.getValue(4) << endl;
	cout << "Setting data[4] to 3" << endl;
	psig1.setValue(4, 3);
	cout << "Position 5: " << psig1.getValue(4) << endl;
	// Normalize
	cout << "\nNormalize:" << endl;
	psig1.Normalize();
	// Print normalized signal
	psig1.printInfo();

	cout << "ProcessedSignal_v2 using Raw_data_01.txt:" << endl;
	ProcessedSignal_v2 psig2(1);
	// PrintInfo
	psig2.printInfo();
	// Make sure getVal(), setVal() still work
	cout << "Position 5: " << psig2.getValue(4) << endl;
	cout << "Setting data[4] to 3" << endl;
	psig2.setValue(4, 3);
	cout << "Position 5: " << psig2.getValue(4) << endl;
	// Normalize
	cout << "\nNormalize:" << endl;
	psig2.Normalize();
	// Print normalized signal
	psig2.printInfo();

	return 0;
}
