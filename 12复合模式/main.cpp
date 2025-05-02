#include <iostream>
#include "old_mvc.h"

using namespace std;

int main()
{

	AbstractDuckFactory* duckfactory = new CountingFactory();
	simulate(duckfactory);

	return 0;
}