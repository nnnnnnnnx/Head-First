#include "Command.h"
#include <iostream>

using namespace std;


int main()
{
	SimpleRemoteControl* remote = new SimpleRemoteControl();
	unique_ptr<Light> light = make_unique<Light>();
	unique_ptr<LightOnCommand>lightOn = make_unique<LightOnCommand>(std::move(light));

	remote->setCommand(std::move(lightOn));
	remote->buttonWasPressed();
	remote->setCommand(make_unique< GarageDoorOpenCommand>(make_unique<GarageDoor>()));
	remote->buttonWasPressed();

	unique_ptr<Light> livingRoomLight = make_unique<Light>("Living Room");
	unique_ptr<Light> kitchenLight = make_unique<Light>("Kitchen");
	unique_ptr<CeilingFan> ceilingFan = make_unique<CeilingFan>("Living Room");
	unique_ptr<GarageDoor> garageDoor = make_unique<GarageDoor>("Garage");
	unique_ptr<Stereo> stereo = make_unique<Stereo>("Living Room");

	unique_ptr<LightOnCommand> livingRoomLightOn = make_unique<LightOnCommand>(std::move(livingRoomLight));
	unique_ptr<LightOffCommand> livingRoomLightOff = make_unique<LightOffCommand>(make_unique<Light>("Living Room"));
	unique_ptr<LightOnCommand> kitchenLightOn = make_unique<LightOnCommand>(std::move(kitchenLight));
	unique_ptr<LightOffCommand> kitchenLightOff = make_unique<LightOffCommand>(make_unique<Light>("Kitchen"));

	unique_ptr<CeilingFanOnCommand> ceilingFanOn = make_unique<CeilingFanOnCommand>(std::move(ceilingFan));
	unique_ptr<CeilingFanOffCommand> ceilingFanOff = make_unique<CeilingFanOffCommand>(make_unique<CeilingFan>("Living Room"));

	unique_ptr<GarageDoorUpCommand> garageDoorUp = make_unique<GarageDoorUpCommand>(std::move(garageDoor));//ceilingFan garageDoor 
	unique_ptr< GarageDoorDownCommand> garageDoorDown = make_unique<GarageDoorDownCommand>(make_unique<GarageDoor>("Garage"));

	unique_ptr<StereoOnWithCDCommand> stereoOnWithCD = make_unique<StereoOnWithCDCommand>(std::move(stereo));
	stereo = make_unique<Stereo>("Living Room");
	unique_ptr<StereoOffCommand> stereoOff = make_unique<StereoOffCommand>(std::move(stereo));

	unique_ptr<RemoteControl> remoteControl = make_unique<RemoteControl>();

	remoteControl->setCommand(0, move(livingRoomLightOn), move(livingRoomLightOff));
	remoteControl->setCommand(1, move(kitchenLightOn), move(kitchenLightOff));
	remoteControl->setCommand(2, move(ceilingFanOn), move(ceilingFanOff));
	remoteControl->setCommand(3, move(stereoOnWithCD), move(stereoOff));

	cout << remoteControl->toString();

	remoteControl->onButtonWasPressed(0);
	remoteControl->offButtonWasPressed(0);
	remoteControl->onButtonWasPressed(1);
	remoteControl->offButtonWasPressed(1);
	remoteControl->onButtonWasPressed(2);
	remoteControl->offButtonWasPressed(2);
	remoteControl->onButtonWasPressed(3);
	remoteControl->offButtonWasPressed(3);


	cout << "*************" << endl;
	remoteControl->onButtonWasPressed(0);
	remoteControl->offButtonWasPressed(0);
	cout << remoteControl->toString();
	remoteControl->undoButtonWasPushed();
	remoteControl->offButtonWasPressed(0);
	remoteControl->onButtonWasPressed(1);
	cout << remoteControl->toString();
	remoteControl->undoButtonWasPushed();

	cout << "*************" << endl;
	remoteControl->setCommand(4, make_unique<CeilingFanMediumCommand>(make_unique<CeilingFan>("Living Room")), make_unique<CeilingFanOffCommand>(make_unique<CeilingFan>("Living Room")));
	remoteControl->setCommand(5, make_unique<CeilingFanHighCommand>(make_unique<CeilingFan>("Living Room")), make_unique<CeilingFanOffCommand>(make_unique<CeilingFan>("Living Room")));
	remoteControl->onButtonWasPressed(4);
	remoteControl->offButtonWasPressed(4);
	cout << remoteControl->toString();
	remoteControl->undoButtonWasPushed();

	remoteControl->offButtonWasPressed(5);
	remoteControl->onButtonWasPressed(5);
	cout << remoteControl->toString();
	remoteControl->undoButtonWasPushed();

	return 0;
}