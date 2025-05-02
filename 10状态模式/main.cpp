#include <iostream>
#include "state.h"

using namespace std;


int main()
{
	GumballMachine gumbal(5);

	cout << gumbal;

	gumbal.insertQuarter();
	gumbal.turnCrank();

	cout << gumbal;
	gumbal.insertQuarter();
	gumbal.turnCrank();
	gumbal.insertQuarter();
	gumbal.turnCrank();

	cout << gumbal;

	return 0;
}