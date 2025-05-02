#pragma once
#include <iostream>
#include <memory>

/*
适配器模式将一个类的接口转换成客户期望的另一个接口。适配器让原本不兼容的类可以合作。
*/

class Duck {
public:
	virtual void quack() = 0;
	virtual void fly() = 0;
};

class MallardDuck : public Duck {
public:
	void quack() override {
		std::cout << "Quack" << "\n";
	}
	void fly() override {
		std::cout << "I'm flying" << "\n";
	}
};


class Turkey {
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

class WildTurkey : public Turkey {
	void gobble() override {
		std::cout << "Gobble gobble" << '\n';
	}
	void fly() override {
		std::cout << "I'm flying a short distance" << '\n';
	}
};

class TurkeyAdapter : public Duck {
private:
	std::unique_ptr<Turkey> turkey;
public:
	TurkeyAdapter(std::unique_ptr<Turkey> turkey) {
		this->turkey = std::move(turkey);
	}
	void quack() override {
		turkey->gobble();
	}
	void fly() override {
		for (int i = 0; i < 5; i++) {
			turkey->fly();
		}
	}
};