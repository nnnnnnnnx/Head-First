#pragma once
#include <iostream>
#include <memory>
#include <time.h>

// 前向声明
class State;
class GumballMachine;
class SoldQutState;
class NoQuarterState;
class HasQuarterState;
class SoldState;
class WinnerState;

// 状态类的接口
class State {
public:
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
	virtual ~State() {}
};

// GumballMachine 类
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

public:
	GumballMachine(int numberGumballs);
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
	friend std::ostream& operator<<(std::ostream& os, GumballMachine& a) {
		os << "GumballMachine : " << a.getCount() << "\n";
		return os;
	}
};

// 各个具体状态类的声明
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
