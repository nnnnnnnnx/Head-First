#pragma once
#include <iostream>
#include <cstring>
#include <memory>
#include <vector>

class Quackable {
public:
	virtual void quack() = 0;
};

class MallarDuck : public Quackable {
public:
	void quack() override {
		std::cout << "Quack" << "\n";
	}
};

class RedheadDuck : public Quackable {
public:
	void quack() override {
		std::cout << "Quack" << "\n";
	}
};

class DuckCall : public Quackable {
public:
	void quack() override {
		std::cout << "Kwak" << "\n";
	}
};

class RubberDuck : public Quackable {
public:
	void quack() override {
		std::cout << "Squeak\n";
	}
};

class Goose {
public:
	void honk() {
		std::cout << "Hook\n";
	}
};

class GooseAdapter : public Quackable {
private:
	Goose* goose;
public:
	GooseAdapter(Goose* goose) {
		this->goose = goose;
	}
	void quack() override {
		goose->honk();
	}
};

class QuackCounter : public Quackable {
private:
	Quackable* duck;
	static int numberOfQuacks;
public:
	QuackCounter(Quackable* duck) {
		this->duck = duck;
	}
	void quack() {
		duck->quack();
		numberOfQuacks++;
	}
	static int getQuacks() {
		return numberOfQuacks;
	}
};
int QuackCounter::numberOfQuacks = 0;


class AbstractDuckFactory {
public:
	virtual Quackable* createMallarDuck() = 0;
	virtual Quackable* createRedheadDuck() = 0;
	virtual Quackable* createDuckCall() = 0;
	virtual Quackable* createRubberDuck() = 0;
};

class DuckFactory : public AbstractDuckFactory {
public:
	Quackable* createMallarDuck() override {
		return new MallarDuck();
	}
	Quackable* createRedheadDuck() override {
		return new RedheadDuck();
	}
	Quackable* createDuckCall() override {
		return new DuckCall();
	}
	Quackable* createRubberDuck() override {
		return new RubberDuck();
	}
};

class CountingFactory : public AbstractDuckFactory {
public:
	Quackable* createMallarDuck() override {
		return new QuackCounter(new MallarDuck());
	}
	Quackable* createRedheadDuck() override {
		return new QuackCounter(new RedheadDuck());
	}
	Quackable* createDuckCall() override {
		return new QuackCounter(new DuckCall());
	}
	Quackable* createRubberDuck() override {
		return new QuackCounter(new RubberDuck());
	}
};


class Flock : public Quackable {
private:
	std::vector<Quackable*> quackers;
public:
	Flock() {

	}
	void add(Quackable* quack) {
		quackers.push_back(quack);
	}
	void quack() {
		for (auto t : quackers) {
			t->quack();
		}
	}
};


void simulate(Quackable* duck) {
	duck->quack();
}

void simulate(AbstractDuckFactory* duckFactory)
{
	Quackable* mallardDuck = duckFactory->createMallarDuck();
	Quackable* redheadDuck = duckFactory->createRedheadDuck();
	Quackable* duckCall = duckFactory->createDuckCall();
	Quackable* rubberDuck = duckFactory->createRubberDuck();
	Quackable* gooseDuck = new QuackCounter(new GooseAdapter(new Goose()));

	std::cout << "\nDuck Simulator: With Composite - Flocks\n";
	Flock* flockofDucks = new Flock();

	flockofDucks->add(redheadDuck);
	flockofDucks->add(duckCall);
	flockofDucks->add(rubberDuck);
	flockofDucks->add(gooseDuck);

	Flock* flockofMallards = new Flock();

	flockofMallards->add(mallardDuck);
	Quackable* mallardDuck2 = duckFactory->createMallarDuck();
	Quackable* mallardDuck3 = duckFactory->createMallarDuck();
	Quackable* mallardDuck4 = duckFactory->createMallarDuck();
	Quackable* mallardDuck5 = duckFactory->createMallarDuck();
	flockofMallards->add(mallardDuck2);
	flockofMallards->add(mallardDuck3);
	flockofMallards->add(mallardDuck4);
	flockofMallards->add(mallardDuck5);

	std::cout << "\nDuck simulator: While Floack simulator\n";
	simulate(flockofDucks);
	simulate(flockofMallards);

	std::cout << "The ducks quacked : " << QuackCounter::getQuacks() << "\n";
	/*
	std::cout << "Duck Simulator\n";
	simulate(mallardDuck);
	simulate(redheadDuck);
	simulate(duckCall);
	simulate(rubberDuck);
	simulate(gooseDuck);
	std::cout << "The ducks quacked : " << QuackCounter::getQuacks() << "\n";
	*/
}

void simulate() {
	Quackable* mallardDuck = new QuackCounter(new MallarDuck());
	Quackable* redheadDuck = new QuackCounter(new RedheadDuck());
	Quackable* duckCall = new QuackCounter(new DuckCall());
	Quackable* rubberDuck = new QuackCounter(new RubberDuck());
	Quackable* gooseDuck = new QuackCounter(new GooseAdapter(new Goose()));
	std::cout << "Duck Simulator\n";
	simulate(mallardDuck);
	simulate(redheadDuck);
	simulate(duckCall);
	simulate(rubberDuck);
	simulate(gooseDuck);
	std::cout << "The ducks quacked : " << QuackCounter::getQuacks() << "\n";

	return;
}

