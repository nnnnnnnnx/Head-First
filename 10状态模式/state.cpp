#include "state.h"



// GumballMachine 类的实现
GumballMachine::GumballMachine(int numberGumballs) {
	soldOutState.reset(new SoldQutState(this));
	noQuarterState.reset(new NoQuarterState(this));
	hasQuarterState.reset(new HasQuarterState(this));
	soldState.reset(new SoldState(this));
	winnerState.reset(new WinnerState(this));
	this->count = numberGumballs;
	if (numberGumballs) {
		state = noQuarterState.get();
	}
	else {
		state = soldOutState.get();
	}
}

void GumballMachine::insertQuarter() {
	state->insertQuarter();
}

void GumballMachine::ejectQuarter() {
	state->ejectQuarter();
}

void GumballMachine::turnCrank() {
	state->turnCrank();
	state->dispense();
}

void GumballMachine::setState(State* state) {
	this->state = state;
}

void GumballMachine::releaseBall() {
	std::cout << "A gumball comes rolling out the slot...\n";
	if (count > 0) {
		count = count - 1;
	}
}

State* GumballMachine::getNoQuarterState() {
	return noQuarterState.get();
}

State* GumballMachine::getHasQuarterState() {
	return hasQuarterState.get();
}

State* GumballMachine::getSoldQutState() {
	return soldOutState.get();
}

State* GumballMachine::getSoldState() {
	return soldState.get();
}

State* GumballMachine::getWinnerState() {
	return winnerState.get();
}

int GumballMachine::getCount() {
	return count;
}

// NoQuarterState 类的实现
NoQuarterState::NoQuarterState(GumballMachine* gumballMachine) {
	this->gumballMachine = gumballMachine;
}

void NoQuarterState::insertQuarter() {
	std::cout << "You inserted a quarter\n";
	gumballMachine->setState(gumballMachine->getHasQuarterState());
}

void NoQuarterState::ejectQuarter() {
	std::cout << "You turned, but there's no quarter\n";
}

void NoQuarterState::turnCrank() {
	std::cout << "You turned, but there's no quarter\n";
}

void NoQuarterState::dispense() {
	std::cout << "You need to pay first\n";
}

// HasQuarterState 类的实现
HasQuarterState::HasQuarterState(GumballMachine* gumballMachine) {
	this->gumballMachine = gumballMachine;
}

void HasQuarterState::insertQuarter() {
	std::cout << "You can't insert a quarter\n";
}

void HasQuarterState::ejectQuarter() {
	std::cout << "Quarter returned\n";
	gumballMachine->setState(gumballMachine->getNoQuarterState());
}

void HasQuarterState::turnCrank() {
	//1/10的机会赢
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	int winner = std::rand() % 10;
	std::cout << winner << " ggggg" << "\n";
	if (winner == 0 && gumballMachine->getCount() > 1) {
		gumballMachine->setState(gumballMachine->getWinnerState());
	}
	else {
		std::cout << "You turned...\n";
		gumballMachine->setState(gumballMachine->getSoldState());
	}
}

void HasQuarterState::dispense() {
	std::cout << "No gumball dispensed\n";
}

// SoldState 类的实现
SoldState::SoldState(GumballMachine* gumballMachine) {
	this->gumballMachine = gumballMachine;
}

void SoldState::insertQuarter() {
	std::cout << "Please wait, we're already giving you a gumball\n";
}

void SoldState::ejectQuarter() {
	std::cout << "Sorry, you already turned the crank\n";
}

void SoldState::turnCrank() {
	std::cout << "Turning twice doesn't get you another gumball.\n";
}

void SoldState::dispense() {
	gumballMachine->releaseBall();
	if (gumballMachine->getCount() > 0) {
		gumballMachine->setState(gumballMachine->getNoQuarterState());
	}
	else {
		std::cout << "Oops, out of gumballs\n";
		gumballMachine->setState(gumballMachine->getSoldQutState());
	}
}

// SoldQutState 类的实现
SoldQutState::SoldQutState(GumballMachine* gumballMachine) {
	this->gumballMachine = gumballMachine;
}

void SoldQutState::insertQuarter() {
	std::cout << "You can't insert a quarter, the machine is sold out\n";
}

void SoldQutState::ejectQuarter() {
	std::cout << "You can't eject, the machine is sold out\n";
}

void SoldQutState::turnCrank() {
	std::cout << "You turned but there are no gumballs\n";
}

void SoldQutState::dispense() {
	std::cout << "No gumballs dispensed\n";
}

// WinnerState 类的实现
WinnerState::WinnerState(GumballMachine* gumballMachine) {
	this->gumballMachine = gumballMachine;
}

void WinnerState::insertQuarter() {
	std::cout << "Please wait, we're already giving you a gumball\n";
}

void WinnerState::ejectQuarter() {
	std::cout << "Sorry, you already turned the crank\n";
}

void WinnerState::turnCrank() {
	std::cout << "Turning twice doesn't get you another gumball.\n";
}

void WinnerState::dispense() {
	gumballMachine->releaseBall();
	if (gumballMachine->getCount() == 0) {
		gumballMachine->setState(gumballMachine->getSoldQutState());
	}
	else {
		gumballMachine->releaseBall();
		std::cout << "YOU'RE A WINNER! You got two gumballs for a quarter\n";
		if (gumballMachine->getCount() > 0) {
			gumballMachine->setState(gumballMachine->getNoQuarterState());
		}
		else {
			std::cout << "Oops, out of gumballs\n";
			gumballMachine->setState(gumballMachine->getSoldQutState());
		}
	}
}
