#include  <iostream>
#include "drive.h"
#include "movie.h"

using namespace std;

void testDuck(Duck* duck) {
	duck->quack();
	duck->fly();
}

int  main() {

	unique_ptr<Duck> duck = make_unique<MallardDuck>();

	unique_ptr<Turkey> turkey = make_unique<WildTurkey>();

	unique_ptr<Duck> turkeyAdapter = make_unique<TurkeyAdapter>(make_unique<WildTurkey>());

	std::cout << "The Turkey says...\n";

	turkey->gobble();
	turkey->fly();

	std::cout << "The Duck says...\n";
	testDuck(duck.get());

	std::cout << "The TurkeyAdapter says...\n";
	testDuck(turkeyAdapter.get());


	unique_ptr<Amplifier> amp = make_unique<Amplifier>("amplifier");
	unique_ptr<Tunner> tunner = make_unique<Tunner>("AM/FM Tuner", make_unique<Amplifier>("amplifier").get());
	unique_ptr<StreamingPlayer> player = make_unique<StreamingPlayer>("Streaming Player", make_unique<Amplifier>("amplifier").get());
	unique_ptr<Projector> projector = make_unique<Projector>("Projector", make_unique<StreamingPlayer>("Streaming Player", make_unique<Amplifier>("amplifier").get()).get());
	unique_ptr<TheaterLights> lights = make_unique<TheaterLights>("Theater Ceiling Lights");
	unique_ptr<Screen> screen = make_unique<Screen>("Theater Screen");
	unique_ptr<PopcornPopper> popper = make_unique<PopcornPopper>("Popcorn Popper");

	HomeTheaterFacade* homeTheater =
		new HomeTheaterFacade(std::move(amp), std::move(tunner), std::move(player), std::move(projector), std::move(lights), std::move(screen), std::move(popper));

	homeTheater->watchMovie("Raiders of the lost Ark");
	homeTheater->endMovie();

	return 0;
}