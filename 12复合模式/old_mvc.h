#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Observer;

class QuackObserveable {
public:
	virtual void registerObserve(Observer*) = 0;
	virtual void notifyObservers() = 0;
	virtual std::string str() = 0;
};

class Quackable : public QuackObserveable {
public:
	virtual void quack() = 0;
};

class Observer {
public:
	virtual void update(QuackObserveable* duck) = 0;
};

class Quacklogist : public Observer {
public:
	void update(QuackObserveable* duck) {
		std::cout << "Quackologist: " << duck->str() << " just quacked!\n";
	}
};

class Observable : public QuackObserveable {
private:
	std::vector<Observer*> observers;
	QuackObserveable* duck;
public:
	Observable(QuackObserveable* duck) {
		this->duck = duck;
	}
	void registerObserve(Observer* observer) {
		observers.push_back(observer);
	}
	void notifyObservers() {
		for (auto t : observers) {
			t->update(this->duck);
		}
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "Observable";
		return os;
	}
	std::string str() {
		return "Observable";
	}
};


class MallarDuck : public Quackable {
private:
	Observable* observable;
public:
	MallarDuck() {
		observable = new Observable(this);
	}
	void quack() override {
		std::cout << "Quack" << "\n";
		notifyObservers();
	}
	void registerObserve(Observer* observer) {
		observable->registerObserve(observer);
	}
	void notifyObservers() {
		observable->notifyObservers();
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "MallarDuck";
		return os;
	}
	std::string str() {
		return "MallarDuck";
	}
};

class RedheadDuck : public Quackable {
private:
	Observable* observable;
public:
	RedheadDuck() {
		observable = new Observable(this);
	}
	void quack() override {
		std::cout << "Quack" << "\n";
		notifyObservers();
	}
	void registerObserve(Observer* observer) {
		observable->registerObserve(observer);
	}
	void notifyObservers() {
		observable->notifyObservers();
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "RedheadDuck";
		return os;
	}
	std::string str() {
		return "RedheadDuck";
	}
};

class DuckCall : public Quackable {
private:
	Observable* observable;
public:
	DuckCall() {
		observable = new Observable(this);
	}
	void quack() override {
		std::cout << "Kwak" << "\n";
		notifyObservers();
	}
	void registerObserve(Observer* observer) {
		observable->registerObserve(observer);
	}
	void notifyObservers() {
		observable->notifyObservers();
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "DuckCall";
		return os;
	}
	std::string str() {
		return "DuckCall";
	}
};

class RubberDuck : public Quackable {
private:
	Observable* observable;
public:
	RubberDuck() {
		observable = new Observable(this);
	}
	void quack() override {
		std::cout << "Squeak\n";
		notifyObservers();
	}
	void registerObserve(Observer* observer) {
		observable->registerObserve(observer);
	}
	void notifyObservers() {
		observable->notifyObservers();
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "RubberDuck";
		return os;
	}
	std::string str() {
		return "RubberDuck";
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
	Observable* observable;
public:
	GooseAdapter(Goose* goose) {
		this->goose = goose;
		observable = new Observable(this);
	}
	void quack() override {
		goose->honk();
		notifyObservers();
	}
	void registerObserve(Observer* observer) {
		observable->registerObserve(observer);
	}
	void notifyObservers() {
		observable->notifyObservers();
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "GooseAdapter";
		return os;
	}
	std::string str() {
		return "GooseAdapter";
	}
};

class QuackCounter : public Quackable {
private:
	Quackable* duck;
	static int numberOfQuacks;
	Observable* observable;
public:
	QuackCounter(Quackable* duck) {
		this->duck = duck;
		observable = new Observable(this);
	}
	void quack() {
		duck->quack();
		numberOfQuacks++;
		notifyObservers();
	}
	static int getQuacks() {
		return numberOfQuacks;
	}
	void registerObserve(Observer* observer) {
		observable->registerObserve(observer);
	}
	void notifyObservers() {
		observable->notifyObservers();
	}
	std::ostream& operator<<(std::ostream& os) {
		os << "QuackCounter";
		return os;
	}
	std::string str() {
		return duck->str();
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
	void registerObserve(Observer* observer) {
		for (auto t : quackers) {
			t->registerObserve(observer);
		}
	}
	void notifyObservers() {

	}
	std::string str() {
		return "Flock";
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

	Flock* flockofDucks = new Flock();
	flockofDucks->add(mallardDuck);
	flockofDucks->add(redheadDuck);
	flockofDucks->add(duckCall);
	flockofDucks->add(rubberDuck);
	flockofDucks->add(gooseDuck);

	std::cout << "\nDuck Simulator: With Observe\n";

	Quacklogist* quackologist = new Quacklogist();
	flockofDucks->registerObserve(quackologist);

	simulate(flockofDucks);
	std::cout << "\nDuck simulator: While Floack simulator\n";


	std::cout << "The ducks quacked : " << QuackCounter::getQuacks() << "\n";

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

