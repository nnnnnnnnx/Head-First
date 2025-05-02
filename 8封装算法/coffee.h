#pragma once
#include <iostream>
#include <memory>

//模版方法定义一个算法的步骤，允许子类提供一个或多个步骤的实现
/*
模版方法模式在一个方法中定义一个算法的骨架，而把一些步骤延迟到子类，模版方法使得子类可以在不改变算法结构的情况下，重新定义算法中的某些步骤。
*/

//好莱坞原则：不要打电话给（调用）我们，我们会打电话给（调用）你。

class CaffeineBeverage {
public:
	virtual void prepareRecipe() final {
		boilWater();
		brew();
		pourInCup();
		if (customerWantsCondiments()) {
			addCondiments();
		}
	}
	void boilWater() {
		std::cout << "Boiling water" << "\n";
	}
	virtual void brew() = 0;
	void pourInCup() {
		std::cout << "Pouring into cup" << "\n";
	}
	virtual bool customerWantsCondiments() {
		return true;
	}
	virtual void addCondiments() = 0;
};


class Tea : public CaffeineBeverage {
public:
	void brew() override {
		std::cout << "Sleeping the tea" << "\n";
	}
	void addCondiments() override {
		std::cout << "Adding Lemon" << "\n";
	}
};

class Coffee : public CaffeineBeverage {
public:
	void brew() override {
		std::cout << "Dripping Coffee through filter" << "\n";
	}
	void addCondiments() override {
		std::cout << "Adding Sugar and Milk" << "\n";
	}
};


class CoffeeWithHook : public CaffeineBeverage {
public:
	void brew() override {
		std::cout << "Dripping Coffee through filter" << "\n";
	}
	void addCondiments() override {
		std::cout << "Adding Sugar and Milk" << "\n";
	}
	virtual bool customerWantsCondiments() {
		return false;
	}
};