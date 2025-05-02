#include "iter.h"
#include "comb.h"
#include <iostream>

using namespace std;

int main()
{
	PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
	vector<MenuItem*> breakfastItems = pancakeHouseMenu->getMenuItems();

	DinerMenu* dinerMenu = new DinerMenu();
	MenuItem** lunchItems = dinerMenu->getMenuItems();

	for (int i = 0; i < breakfastItems.size(); i++) {
		cout << breakfastItems[i]->getName() << " " << breakfastItems[i]->getPrice() << " " << breakfastItems[i]->getDescription() << endl;
	}

	for (int i = 0; i < dinerMenu->len(); i++) {
		cout << lunchItems[i]->getName() << " " << lunchItems[i]->getPrice() << " " << lunchItems[i]->getDescription() << endl;
	}
	cout << "******************" << endl;
	DinerMenu1* d1 = new DinerMenu1();
	PancakeHouseMenu1* p1 = new PancakeHouseMenu1();
	Waitress waitress(d1, p1);
	waitress.printMenu();

	return 0;
}