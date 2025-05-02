#include<iostream>
#include "SimUDuck.h"
using namespace std;


int main()
{
	Duck* mallard = new	MallardDuck();
	mallard->display();
	mallard->performFly();
	mallard->performQuack();

	Duck* model = new ModelDuck();
	model->performFly();
	model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
	model->performFly();

	cin.get();
	return 0;
}