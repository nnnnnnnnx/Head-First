#include "loc.h"
#include <iostream>

using namespace std;


int main()
{
	GumballMachine gumbal("noname", 5);

	cout << gumbal << endl;
	gumbal.insertQuarter();
	gumbal.turnCrank();

	cout << gumbal << endl;
	gumbal.insertQuarter();
	gumbal.turnCrank();
	gumbal.insertQuarter();
	gumbal.turnCrank();


	return 0;
}


