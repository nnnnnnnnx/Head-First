#pragma once

//类应该对扩展开放 对修改关闭
//装饰者，动态地将额外责任附加到对象上。对于扩展功能，装饰者提供子类化之外的弹性代替方案。
#include <string>
#include <iostream>
#include <memory>
class Beverage {
protected:
	std::string description;
public:
	Beverage() : description("Unknown Beverage") {}
	virtual std::string getDescription()const {
		return description;
	}
	virtual double cost() const = 0;
};

class CondimentDecorator : public Beverage
{
protected:
	std::unique_ptr<Beverage> beverage;
public:
	virtual std::string getDescription() const = 0;
	virtual double cost() const = 0;
	CondimentDecorator() = default;
	virtual ~CondimentDecorator() = default;
};

class Espresso : public Beverage
{
public:
	Espresso() {
		description = "Espresso";
	}
	virtual double cost() const override {
		return 1.99;
	}
};

class HouseBlend : public Beverage {
public:
	HouseBlend() {
		description = "House Blend Coffee";
	}
	virtual double cost() const override {
		return .89;
	}
};

class DarkRoast : public Beverage {
public:
	DarkRoast() {
		description = "Dark Roast Coffee";
	}
	virtual double cost() const override {
		return .99;
	}
};

class Decaf : public Beverage {
public:
	Decaf() {
		description = "Decaf Coffee";
	}
	virtual double cost() const override {
		return 1.05;
	}
};

class  Mocha : public CondimentDecorator {
public:
	Mocha(std::unique_ptr<Beverage> beverage) {
		this->beverage = std::move(beverage);
	}
	std::string getDescription() const override {
		return beverage->getDescription() + ", Mocha";
	}
	double cost() const override {
		return beverage->cost() + .20;
	}
};

class Soy : public CondimentDecorator {
public:
	Soy(std::unique_ptr<Beverage> beverage) {
		this->beverage = std::move(beverage);
	}
	std::string getDescription() const override {
		return beverage->getDescription() + ", Soy";
	}
	double cost() const override {
		return beverage->cost() + .15;
	}
};

class Whip : public CondimentDecorator {
public:
	Whip(std::unique_ptr<Beverage> beverage) {
		this->beverage = std::move(beverage);
	}
	std::string getDescription() const override {
		return beverage->getDescription() + ", Whip";
	}
	double cost() const override {
		return beverage->cost() + .1;
	}
};
