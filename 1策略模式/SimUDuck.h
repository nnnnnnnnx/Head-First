#pragma once
#include<iostream>
#include <memory>
//识别应用中变化的方面，把他们和不变的方面分开
//针对接口（超类型）编程而不是针对实现编程
//优先使用组合而不是继承


/*
策略模式（Strategy Pattern） 是一种行为型设计模式，用于将算法（策略）从使用它的类中分离出来，使它们可以独立变化和互相替换。
:定义类一个算法族,分别封装起来，使得它们之间可以相互变换。策略让算法的变化独立于使用他们的客户。
核心思想是：
封装一组可互换的算法（策略类）
将这些算法的实现抽象出来
在运行时可以自由切换策略（而不修改使用它的对象）
*/
class FlyBehavior {
public:
	virtual void fly() const = 0;
};

class FlyWithWings : public FlyBehavior {
public:
	virtual void fly() const override {
		std::cout << "I am flying!!\n";
	}
};

class FlyNoWay : public FlyBehavior {
public:
	virtual void fly() const override {
		std::cout << "I can't fly\n";
	}
};

class FlyRocketPowered : public FlyBehavior {
public:
	virtual void fly() const override {
		std::cout << "I'm flying with a rocket!\n";
	}
};

class QuackBehavior {
public:
	virtual void quack() const = 0;
};

class Quack :public QuackBehavior {
	virtual void quack() const override {
		std::cout << "Quack\n";
	}
};

class MuteQuack :public QuackBehavior {
	virtual void quack() const override {
		std::cout << "Silence\n";
	}
};

class Squack :public QuackBehavior {
	virtual void quack() const override {
		std::cout << "Squeak\n";
	}
};

class Duck
{
protected:
	std::unique_ptr<FlyBehavior> flyBehavior;
	std::unique_ptr<QuackBehavior> quackBehavior;
public:
	Duck() {
	}
	virtual void display() const = 0;
	void performFly() {
		flyBehavior->fly();
	}
	void performQuack() {
		quackBehavior->quack();
	}
	void swim() {
		std::cout << "I can swimming!\n";
	}
	void setFlyBehavior(std::unique_ptr<FlyBehavior> fb) {
		flyBehavior = std::move(fb);
	}

	void setQuackBehavior(std::unique_ptr<QuackBehavior> qb) {
		quackBehavior = std::move(qb);
	}

	virtual ~Duck() = default;
};

class MallardDuck : public Duck {
public:
	MallardDuck() {
		flyBehavior = std::make_unique<FlyWithWings>();
		quackBehavior = std::make_unique<Quack>();
	}
	virtual void display() const
	{
		std::cout << "I'm a real Mallard duck\n";
	}
};

class ModelDuck :public Duck {
public:
	ModelDuck()
	{
		flyBehavior = std::make_unique<FlyNoWay>();
		quackBehavior = std::make_unique<Quack>();
	}
	virtual void display() const {
		std::cout << "I'm a model duck\n";
	}
};

