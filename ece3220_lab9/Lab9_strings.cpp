// Lab9_strings.cpp
// This program shows some simple string examples, and asks for simple tasks.
// Reference: Lippman, section 3.2

// Author: Luis Rivera

#include <iostream>
#include <string>

using namespace std;

// Main function. Shows a few examples. Complete the assignments stated in the comments.
int main()
{
	string s1, s2("Hello"), s3 = "World";
	cout << "\nEnter a word: ";
	cin >> s1;
	
	string s4(s1);
	
	cout << s1 << endl
		 << s2 << endl
		 << s3 << endl
		 << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;

// ***********************************************************************
// Try all the operations in Table 3.2 using the strings above and
// using new strings that you may declare.
// Some of those operations have already been used, but write your
// own examples.
// ***********************************************************************

// -----------------------------------------------------------------------
	string line1;
	cout << "\nEnter some text, finish it with an & ";
	getline(cin, line1, '&');
	cout << "String is: " << line1 << endl;
	
	string line2;
	cout << "Enter a string: ";
	cin >> line2;
	cout << "String is: " << line2 << endl;

	if(line2.empty()) 
	{
		cout << "Empty string";
	}
	cout << "String len: " << line2.size() << endl;
	cout << "string[0] == " << line2[0] << endl;

	string str3 = line1 + line2;

	cout << "str1 + str2 => " << str3 << endl;

	str3 = line1;

	if(str3 == line1)
		cout << "Strings equal" << endl;

	if(str3 != line2) 
		cout << "String not equal" << endl;

	line1 = 'A'; 
	line2 = 'a';

	if(line1 < line2) 
	{
		cout << line1 << " < " << line2 << endl;
	}


// ***********************************************************************
// Use a "Range for" (Lippman, page 93) and operations in table 3.3 to:
// 1) change the case of the letters in your input line above (upper to
//    lowercase and vice-versa).
// 2) Replace any whitespace with a dot ('.').
// Print the converted text.
// ***********************************************************************
	// foreach char in str
	// use a reference
	for(auto &c : str3)
	{
		if(islower(c))
		{
			c = toupper(c);
		}
		else if(isupper(c))
		{
			c = tolower(c);
		}
		else if(isspace(c))
		{
			c = '.';
		}
	}
	cout << str3;


	return 0;
}
