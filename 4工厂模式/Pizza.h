#pragma once

#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
//工厂方法模式定义了一个创建对象的接口，但子类决定要示例化哪个类。工厂方法让类把实例化推迟到子类。
//抽象工厂模式 提供一个接口来创建相关或依赖对象的家族，而不需要指定具体类。
//依赖抽象不依赖具体类   依赖倒置原则
class Pizza {
protected:
	std::string name;
	std::string dough;
	std::string sauce;
	std::vector<std::string> toppings;
public:
	virtual void prepare() {
		std::cout << "Preparing " << name << "\n";
		std::cout << "Tossing dough ..." << '\n';
		std::cout << "Adding sauce ..." << '\n';
		std::cout << "Adding toppings: " << '\n';
		for (auto topping : toppings)
			std::cout << "   " << topping << '\n';
	}
	virtual void bake()
	{
		std::cout << "Bake for 25 minutes at 350" << '\n';
	}
	virtual void cut() {
		std::cout << "Cutting the pizza into diagonal slices" << '\n';
	}
	virtual void box() {
		std::cout << "Place pizza in official PizzaStore box" << "\n";
	}
public:
	std::string getName() {
		return name;
	}
};

class NYStyleCheesePizza : public Pizza {
public:
	NYStyleCheesePizza() {
		name = "NY Style Sauce and Cheese Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";

		toppings.push_back("Grated Reggiano Cheese");
	}
};

class NYStylePepperoniPizza : public Pizza {
public:
	NYStylePepperoniPizza() {
		name = "NY Style Pepperoni Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";

		toppings.push_back("Grated Reggiano Cheese");
		toppings.push_back("Sliced Pepperoni");
		toppings.push_back("Garlic");
		toppings.push_back("Onion");
		toppings.push_back("Mushrooms");
		toppings.push_back("Red Pepper");
	}
};

class NYStyleClamPizza : public Pizza {
public:
	NYStyleClamPizza() {
		name = "NY Style Clam Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";

		toppings.push_back("Grated Reggiano Cheese");
		toppings.push_back("Fresh Clams from Long Island Sound");
	}
};

class NYStyleVeggiePizza : public Pizza {
public:
	NYStyleVeggiePizza() {
		name = "NY Style Veggie Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";

		toppings.push_back("Grated Reggiano Cheese");
		toppings.push_back("Garlic");
		toppings.push_back("Onion");
		toppings.push_back("Mushrooms");
		toppings.push_back("Red Pepper");
	}
};

class ChicagoStyleCheesePizza : public Pizza {
public:
	ChicagoStyleCheesePizza() {
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";

		toppings.push_back("Shredded Mozzarella Cheese");
	}
	virtual void cut() override {
		std::cout << "Cutting the pizza into square slices" << '\n';
	}
};

class ChicagoStylePepperoniPizza : public Pizza {
public:
	ChicagoStylePepperoniPizza() {
		name = "Chicago Style Pepperoni Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";

		toppings.push_back("Shredded Mozzarella Cheese");
		toppings.push_back("Black Olives");
		toppings.push_back("Spinach");
		toppings.push_back("Eggplant");
		toppings.push_back("Sliced Pepperoni");
	}

	virtual void cut() override {
		std::cout << "Cutting the pizza into square slices" << "\n";
	}
};

class ChicagoStyleClamPizza : public Pizza {
public:
	ChicagoStyleClamPizza() {
		name = "Chicago Style Clam Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";

		toppings.push_back("Shredded Mozzarella Cheese");
		toppings.push_back("Frozen Clams from Chesapeake Bay");
	}

	virtual void cut() override {
		std::cout << "Cutting the pizza into square slices" << "\n";
	}
};

class ChicagoStyleVeggiePizza : public Pizza {
public:
	ChicagoStyleVeggiePizza() {
		name = "Chicago Deep Dish Veggie Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";

		toppings.push_back("Shredded Mozzarella Cheese");
		toppings.push_back("Black Olives");
		toppings.push_back("Spinach");
		toppings.push_back("Eggplant");
	}

	virtual void cut() override {
		std::cout << "Cutting the pizza into square slices" << "\n";
	}
};

class PizzaStore {
public:
	virtual std::unique_ptr<Pizza> createPizza(const std::string&) = 0;
	std::unique_ptr<Pizza> orderPizza(const std::string& type) {
		std::unique_ptr<Pizza> pizza;
		pizza = createPizza(type);
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();
		return pizza;
	}
};

class NYStylePizzaStore : public PizzaStore
{
public:
	virtual std::unique_ptr<Pizza> createPizza(const std::string& type) override {
		std::unique_ptr<Pizza> pizza;
		if (type == "cheese")
		{
			pizza = std::make_unique<NYStyleCheesePizza>();
		}
		else if (type == "pepperoni") {
			pizza = std::make_unique<NYStylePepperoniPizza>();
		}
		else if (type == "clam") {
			pizza = std::make_unique<NYStyleClamPizza>();
		}
		else if (type == "veggie") {
			pizza = std::make_unique<NYStyleVeggiePizza>();
		}
		else return nullptr;
		return pizza;
	}
};

class ChicagoStylePizzaStore : public PizzaStore
{
public:
	virtual std::unique_ptr<Pizza> createPizza(const std::string& type) override {
		std::unique_ptr<Pizza> pizza;
		if (type == "cheese")
		{
			pizza = std::make_unique<ChicagoStyleCheesePizza>();
		}
		else if (type == "pepperoni") {
			pizza = std::make_unique<ChicagoStylePepperoniPizza>();
		}
		else if (type == "clam") {
			pizza = std::make_unique<ChicagoStyleClamPizza>();
		}
		else if (type == "veggie") {
			pizza = std::make_unique<ChicagoStyleVeggiePizza>();
		}
		else return nullptr;
		return pizza;
	}
};
