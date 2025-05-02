#pragma once
#include <iostream>
#include <string>
#include <vector>

/*
迭代器提供一种方式，可以访问一个聚合对象中的元素而又不暴露其潜在的表示
*/
/*
单一责任原则，一个类应该只有一个变化的原因
*/

//组合模式 允许你讲对象组合成树形结构来表现部分-整体层次结构。组合可以让客户可以统一处理个别对象进和对象的组合。

class MenuItem {
private:
	std::string name;
	std::string description;
	bool vegatrain;
	double price;

public:
	MenuItem(std::string name, std::string description, bool vegatrain, double price)
	{
		this->name = name;
		this->description = description;
		this->vegatrain = vegatrain;
		this->price = price;
	}
	std::string getName()
	{
		return name;
	}
	std::string getDescription()
	{
		return description;
	}
	double getPrice()
	{
		return price;
	}
	bool isVegetarian()
	{
		return vegatrain;
	}
};

class PancakeHouseMenu {
private:
	std::vector<MenuItem*> menuItems;
public:
	PancakeHouseMenu() {
		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes With friend eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes with fresh blueberries", true, 3.49);
		addItem("Waffles", "Wasffles with your choice of blueberries or strawberries", true, 3.59);
	}
	void addItem(std::string name, std::string description, bool vegetarian, double price)
	{
		MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
		menuItems.push_back(menuItem);
	}
	std::vector<MenuItem*>& getMenuItems()
	{
		return menuItems;
	}
};

class DinerMenu {
private:
	static const int MAX_ITEMS = 6;
	int numberOfItems = 0;
	MenuItem* menuItems[MAX_ITEMS];
public:
	DinerMenu()
	{
		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with sauerkraut, relish, onions, topped with cheese", false, 3.0);
	}
	void addItem(std::string name, std::string description, bool vegetarian, double price) {
		if (numberOfItems >= MAX_ITEMS) {
			std::cout << "Sorry, menu is full! Cann't add item to menu" << "\n";
		}
		else {
			menuItems[numberOfItems] = new MenuItem(name, description, vegetarian, price);
			numberOfItems++;
		}
	}
	int len() {
		return numberOfItems;
	}
	MenuItem** getMenuItems() {
		return menuItems;
	}
};


class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual MenuItem* next() = 0;
	virtual ~Iterator() {}
};

class DinerMenuIterator : public Iterator {
private:
	int position;
	MenuItem** items;
	int size;
public:
	DinerMenuIterator(MenuItem** items, int size) {
		this->items = items;
		this->size = size;
		this->position = 0;
	}

	bool hasNext() override {
		return (position < size && items[position] != nullptr);
	}

	MenuItem* next() override {
		if (!hasNext()) return nullptr;
		return items[position++];
	}
};

class DinerMenu1 {
private:
	static const int MAX_ITEMS = 6;
	int numberOfItems = 0;
	MenuItem* menuItems[MAX_ITEMS];
public:
	DinerMenu1()
	{
		addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
		addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
		addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
		addItem("Hotdog", "A hot dog, with sauerkraut, relish, onions, topped with cheese", false, 3.0);
	}
	Iterator* createIterator() {
		return new DinerMenuIterator(menuItems, numberOfItems);
	}
	void addItem(std::string name, std::string description, bool vegetarian, double price) {
		if (numberOfItems >= MAX_ITEMS) {
			std::cout << "Sorry, menu is full! Cann't add item to menu" << "\n";
		}
		else {
			menuItems[numberOfItems] = new MenuItem(name, description, vegetarian, price);
			numberOfItems++;
		}
	}
	int len() {
		return numberOfItems;
	}
};

class PancakeHouseMenuIterator : public Iterator {
private:
	std::vector<MenuItem*> items;
	int position = 0;
public:
	PancakeHouseMenuIterator(std::vector<MenuItem*> items) {
		this->items = items;
	}
	bool hasNext() override {
		return (position < items.size() && items[position] != nullptr);
	}

	MenuItem* next() override {
		if (!hasNext()) return nullptr;
		return items[position++];
	}
};

class PancakeHouseMenu1 {
private:
	std::vector<MenuItem*> items;
public:
	PancakeHouseMenu1() {
		addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs and toast", true, 2.99);
		addItem("Regular Pancake Breakfast", "Pancakes With friend eggs, sausage", false, 2.99);
		addItem("Blueberry Pancakes", "Pancakes with fresh blueberries", true, 3.49);
		addItem("Waffles", "Wasffles with your choice of blueberries or strawberries", true, 3.59);
	}
	void addItem(std::string name, std::string description, bool vegetarian, double price)
	{
		MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
		items.push_back(menuItem);
	}
	Iterator* createIterator() {
		return new PancakeHouseMenuIterator(items);
	}
};

class Waitress {
private:
	PancakeHouseMenu1* p;
	DinerMenu1* d;

public:
	Waitress(DinerMenu1* d, PancakeHouseMenu1* p)
	{
		this->p = p;
		this->d = d;
	}
	void printMenu() {
		Iterator* pi = p->createIterator();
		Iterator* di = p->createIterator();
		std::cout << "MENU\n----\nBREAKFAST\n";
		printMenu(pi);
		std::cout << "lunch\n";
		printMenu(di);
	}
	void printMenu(Iterator* i)
	{
		while (i->hasNext())
		{
			MenuItem* me = i->next();
			std::cout << me->getName() << " " << me->getPrice() << " " << me->getDescription() << "\n";
		}
	}
};