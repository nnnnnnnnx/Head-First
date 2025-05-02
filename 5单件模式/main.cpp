#include "sing.h"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
	ChocolateBoiler* boil = ChocolateBoiler::getInstance();
	boil->fill();
	boil->boil();
	boil->drain();

	cin.get();

	return 0;
}