#include "coffee.h"
#include <iostream>
using namespace std;


int main()
{
	CaffeineBeverage* tea = new Tea();
	tea->prepareRecipe();
	delete tea;
	tea = new Coffee();
	tea->prepareRecipe();
	delete tea;
	tea = new CoffeeWithHook();
	tea->prepareRecipe();

	return 0;
}