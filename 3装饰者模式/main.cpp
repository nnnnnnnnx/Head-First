#include "Starbuzz.h"
#include <iostream>
#include <memory>
using namespace std;

int main()
{
	Beverage* beverage = new Espresso();
	cout << beverage->getDescription() << " $" << beverage->cost() << "\n";

	unique_ptr<Beverage> beverage2 = make_unique<DarkRoast>();
	beverage2 = make_unique<Mocha>(move(beverage2));
	beverage2 = make_unique<Mocha>(move(beverage2));
	beverage2 = make_unique<Whip>(move(beverage2));
	cout << beverage2->getDescription() << " $" << beverage2->cost() << "\n";

	unique_ptr<Beverage> beverage3 = make_unique<HouseBlend>();
	beverage3 = make_unique<Soy>(move(beverage3));
	beverage3 = make_unique<Mocha>(move(beverage3));
	beverage3 = make_unique<Whip>(move(beverage3));
	cout << beverage3->getDescription() << " $" << beverage3->cost() << "\n";


	auto drink = std::make_unique<Whip>(
		std::make_unique<Soy>(
			std::make_unique<Mocha>(
				std::make_unique<DarkRoast>()
			)
		)
	);
	cout << drink->getDescription() << " $" << drink->cost() << "\n";

	return 0;
}
