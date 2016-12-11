// Lab9_vectors.cpp
// This program shows some simple vector examples, and asks for simple tasks.
// Reference: Lippman, section 3.3

// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
// Example: g++ Lab9_vectors.cpp -o Lab9_vectors -std=c++11
// Some initialization methods and other things are not supported by the old standard.

#include <iostream>
#include <vector>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	vector<int> ivec1(5), ivec2;
	vector<double> dvec1{5.1}, dvec2(5,1.5);
	vector<string> svec1 = {"hello", "world"};
	// vector<myClass> myCvec;	// you can have vectors of objects
	// in general: vector<Type> vec;	// vector is a template

	for(int i = 0; i < ivec1.size(); i++)
		cout << ivec1[i] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:ivec1)	// This is equivalent to the above for loop
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:dvec2)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
	
	for(auto i:svec1)
		cout << i << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
	cout << "Original size: " << ivec2.size() << endl;
	ivec2.push_back(50);
	cout << "New size: " << ivec2.size() << "\nAdded element: " << ivec2[0] << endl;
	cout << "\n------------------------------------------------------------------" << endl;
		
// ***********************************************************************
// Try all the wasy to initializa a vector shown in Table 3.4. Use the
// vectors above and/or declare new vectors.
// Some of those operations have already been used, but write your
// own examples.
	
	// Empty Vector
	vector<int> tivec1;
	// Initialize w/ elements
	vector<int> tivec2{1, 2, 3};
	vector<int> tivec6 = {0, 1, 2};
	// Initialize w/ elements of tivec2:
	vector<int> tivec3(tivec2);
	// Same as above
	vector<int> tivec4 = tivec2;
	// 10 elements w/ val '0'
	vector<int> tivec5;
// Do exercises 3.14 and 3.15 from Lippman (page 102)
	// 3.14 Read sequence of ints from cin into vector

	cout << "Enter a sequence of 5 integers: ";
	for(int i=0; i<5; i++)
	{
		static int tmp;
		cin >> tmp;
		tivec5.push_back(tmp);
	}
	cout << "Integers entered: " << endl;
	for(auto i: tivec5) 
	{ cout << i << endl; }

	// 3.15 - 3.14 but w/ strings instead
	vector<string> tsvec1;
	cout << "Enter a sequence of 5 strings: ";
	for(int i=0; i<5; i++)
	{
		static string tmp;
		cin >> tmp;
		tsvec1.push_back(tmp);
	}
	cout << "Strings entered: " << endl;
	for(auto s: tsvec1) 
	{ cout << s << endl; }

// Try all the vector operations shown in table 3.5. Use the vectors above
// or define new ones. Try different types.

	   if(tivec1.empty())
	   {
		   cout << "Empty vector" << endl;
	   }
	   cout << "Size of empty vector: " << tivec1.size() << endl;
	   tivec1.push_back(9); // i.e. append
	   cout << "New value in index 0: " << tivec1[0] << endl;
	   tivec2 = {2, 3, 1};
	   tivec1 = tivec2;
	   if(tivec1 == tivec2) 
	   {
		   cout << "Equal" << endl;
	   }
	   tivec2 = {2, 2, 1};
	   if(tivec1 != tivec2) 
	   {
		   cout << "Not Equal" << endl;
	   }
	   if(tivec1 > tivec2) 
	   {
		   cout << "vec1 > vec2" << endl;
	   }
	   tivec2 = {2, 3, 1, 0};
	   if(tivec1 < tivec2) 
	   {
		   cout << "vec1 < vec2" << endl;
	   }
// ***********************************************************************

	return 0;
}
