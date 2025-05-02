#include "Pizza.h"
#include <iostream>

using namespace std;

int main()
{
	unique_ptr<PizzaStore> nyStore = make_unique<NYStylePizzaStore>();
	unique_ptr<Pizza> pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " + pizza->getName() << "\n";

	unique_ptr<PizzaStore>  chicagoStore = make_unique<ChicagoStylePizzaStore>();
	pizza = chicagoStore->orderPizza("cheese");
	cout << "Joel ordered a " + pizza->getName() << "\n";

	return 0;
}