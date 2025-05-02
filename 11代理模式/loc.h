#pragma once
#include <iostream>
#include <memory>
#include <memory>
#include<string>



class State;
class GumballMachine;
class SoldQutState;
class NoQuarterState;
class HasQuarterState;
class SoldState;
class WinnerState;

class State {
public:
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
	virtual ~State() {}
};

struct GumballStatus {
	std::string location;
	std::string state;
	int count;
};

class GumballMachine {
private:
	enum { SOLD_OUT = 0, NO_QUARTER, HAS_QUARTER, SOLD };
	int count = 0;
	std::unique_ptr<State> soldOutState;
	std::unique_ptr<State> noQuarterState;
	std::unique_ptr<State> hasQuarterState;
	std::unique_ptr<State> soldState;
	std::unique_ptr<State> winnerState;
	State* state = nullptr;
	std::string location;

public:
	GumballMachine(std::string location, int numberGumballs);
	void insertQuarter();
	void ejectQuarter();
	void turnCrank();
	void setState(State* state);
	void releaseBall();
	State* getNoQuarterState();
	State* getHasQuarterState();
	State* getSoldQutState();
	State* getSoldState();
	State* getWinnerState();
	int getCount();
	std::string getLocation() {
		return location;
	}
	std::string getState() {
		if (state == winnerState.get()) {
			return "WinnerState";
		}
		else if (state == soldState.get())
		{
			return "SoldState";
		}
		else if (state == hasQuarterState.get()) {
			return "HasQuarterState";
		}
		else if (state == noQuarterState.get()) {
			return "NoQuartState";
		}
		else if (state == soldOutState.get()) {
			return "SoldOutState";
		}
	}
	friend std::ostream& operator<<(std::ostream& os, GumballMachine& a) {
		os << "GumballMachine : " << a.getCount() << "\n";
		return os;
	}
	GumballStatus toStatus() {
		GumballStatus s;
		s.location = this->location;
		s.state = this->getState();
		s.count = this->count;
		return s;
	}
};

class GumballMonitor {
private:
	GumballStatus* machine;
public:
	GumballMonitor(GumballStatus* machine) {
		this->machine = machine;
	}
	void report() {
		std::cout << "Gumball Machine: " << machine->location << "\n";
		std::cout << "Current inverory: " << machine->state << " gumballs\n";
		std::cout << "Current state: " << machine->count << "\n";
	}
	void set(GumballStatus* machine) {
		this->machine = machine;
	}
};

class NoQuarterState : public State {
private:
	GumballMachine* gumballMachine;
public:
	NoQuarterState(GumballMachine* gumballMachine);
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class HasQuarterState : public State {
private:
	GumballMachine* gumballMachine;
public:
	HasQuarterState(GumballMachine* gumballMachine);
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class SoldState : public State {
private:
	GumballMachine* gumballMachine;
public:
	SoldState(GumballMachine* gumballMachine);
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class SoldQutState : public State {
private:
	GumballMachine* gumballMachine;
public:
	SoldQutState(GumballMachine* gumballMachine);
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};

class WinnerState : public State {
private:
	GumballMachine* gumballMachine;
public:
	WinnerState(GumballMachine* gumballMachine);
	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
};
