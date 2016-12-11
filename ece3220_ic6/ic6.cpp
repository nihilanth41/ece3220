// L20_Ex2_ExceptionObjects.cpp

#include <iostream>
#include <cmath>
#include <cstring>
//#include "L20_Ex2.h"

class demo{
private:
    char word[40];
public:
    demo(const char * str){
        strcpy(word, str);
        cout << "demo " << word << " created\n";
    }
    ~demo(){
        cout << "demo " << word << " destroyed\n";
    }
    void show()
    {
        cout << "demo " << word << " lives!\n";
    }
};

double hmean(double a, double b) throw(bad_hmean);
double gmean(double a, double b) throw(bad_gmean);
double means(double a, double b) throw(bad_hmean, bad_gmean);

int main(){
	
	double x, y, z;

    demo d1("Found in main()");
	cout << "Enter two numbers: ";
    
	while(cin >> x >> y)
	{
		try{
			z = means(x,y);
			cout << "The mean of means of " << x << " and " << y << " is " << z << endl;
			cout << "Enter next set of numbers <q to quit>: ";
		}
        catch(bad_hmean & bh)
		{
			bh.mesg();
			cout << "Try again.\n";
			continue;
		}
		catch(bad_gmean & bg)
		{
			cout << bg.mesg();
			cout << "Values used: " << bg.v1 << ", "<< bg.v2 << endl;
			cout << "Sorry, you cannot run this any more. \n";
			break;
		}
        catch(...){
            cout << "general exception";
        }
	}
    d1.show();
	cout << "Bye!\n";
	return 0;
}

double hmean(double a, double b) throw(bad_hmean)
{
	if (a == -b){
		throw bad_hmean(a,b);
	}
	return 2.0*a*b / (a+b);
}

double gmean(double a, double b) throw(bad_gmean)
{
	if(a < 0 || b < 0)
		throw bad_gmean(a,b);

	return sqrt(a*b);
}

double means(double a, double b) throw(bad_hmean, bad_gmean){
    double am, hm, gm;
    demo d2("found in means()");
    am = (a + b)/ 2.0; // arithmetic mean
    try{
        hm = hmean(a,b);
        gm = gmean(a,b);
    }
    catch(bad_hmean & bh)
    {
        bh.mesg();
        cout << "Caught in means()\n";
        throw;	// rethrow. Try commenting this out.
    }
    d2.show();
    return (am + hm + gm)/3.0;
}
