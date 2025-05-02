#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include<sstream>
#include<algorithm>
/*
命令模式把请求封装为对象，以便于不同的请求，队列或者日志请求来参数化其他对象
并支持可撤销的操作
*/

class Light {
private:
	std::string location;
public:
	Light(std::string location = "No") {
		this->location = location;
	}
	void on() {
		std::cout << location << " Light is on" << std::endl;
	}
	void off() {
		std::cout << location << " Light is off" << std::endl;
	}
};

class GarageDoor {
private:
	std::string location;
public:
	GarageDoor(std::string location = "No") {
		this->location = location;
	}
	void up() {
		std::cout << location << " Garage Door is Open" << std::endl;
	}
	void down() {
		std::cout << location << " Garage Door is Closed" << std::endl;
	}
	void stop() {
		std::cout << location << " Garage Door is Stopped" << std::endl;
	}
	void lightOn() {
		std::cout << location << " Garage light is on" << std::endl;
	}
	void lightOff() {
		std::cout << location << " Garage light is off" << std::endl;
	}
};

class Stereo {
private:
	std::string location;
public:
	Stereo(std::string location = "No") {
		this->location = location;
	}
	void on() {
		std::cout << location << " stereo is on" << "\n";
	}
	void off() {
		std::cout << location << " stereo is off" << '\n';
	}
	void setCD() {
		std::cout << location << " stereo is set for CD input" << '\n';
	}
	void setRadio() {
		std::cout << location << " stereo is set for Radio" << "\n";
	}
	void setVolume(int volume) {
		std::cout << location << " stereo volume set to " << volume << "\n";
	}
};

class CeilingFan {
private:
	std::string location;
	int level;
public:
	enum { OFF = 0, LOW, MEDIUM, HIGH };
public:
	CeilingFan(std::string location) {
		this->location = location;
		level = OFF;
	}
	void high() {
		level = HIGH;
		std::cout << location << " ceiling fan is on high" << "\n";
	}
	void medium() {
		level = MEDIUM;
		std::cout << location << " ceiling fan is on medium" << "\n";
	}
	void low() {
		level = LOW;
		std::cout << location << " ceiling fan is on low" << "\n";
	}
	void off() {
		level = OFF;
		std::cout << location << " ceiling fan is off" << "\n";
	}
	int getSpeed() {
		return level;
	}
};


class Command
{
public:
	virtual void excute() {

	}
	virtual void undo() {

	}
	virtual std::string name() {
		return "NoCommand";
	}
};

class LightOnCommand : public Command {
private:
	std::unique_ptr<Light> light;
public:
	LightOnCommand(std::unique_ptr<Light> light) {
		this->light = std::move(light);
	}
	void excute()  override {
		light->on();
	}
	void undo() override {
		light->off();
	}
	std::string name() override {
		return "LightOnCommand";
	}
};

class LightOffCommand : public Command {
private:
	std::unique_ptr<Light> light;
public:
	LightOffCommand(std::unique_ptr<Light> light) {
		this->light = std::move(light);
	}
	void excute()  override {
		light->off();
	}
	void undo() override {
		light->on();
	}
	std::string name() override {
		return "LightOffCommand";
	}
};

class CeilingFanOnCommand : public Command {
private:
	std::unique_ptr<CeilingFan> ceilingFan;
public:
	CeilingFanOnCommand(std::unique_ptr<CeilingFan> ceilingFan) {
		this->ceilingFan = std::move(ceilingFan);
	}
	void excute() override {
		ceilingFan->high();
	}
	std::string name() override {
		return "CeilingFanOnCommand";
	}
};

class CeilingFanOffCommand : public Command {
private:
	std::unique_ptr<CeilingFan> ceilingFan;
	int prevSpeed;
public:
	CeilingFanOffCommand(std::unique_ptr<CeilingFan> ceilingFan) {
		this->ceilingFan = std::move(ceilingFan);
		prevSpeed = 0;
	}
	void excute() override {
		ceilingFan->off();
	}
	void undo() override {
		if (prevSpeed == CeilingFan::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::OFF) {
			ceilingFan->off();
		}
	}
	std::string name() override {
		return "CeilingFanOffCommand";
	}
};

class CeilingFanHighCommand : public Command {
private:
	std::unique_ptr<CeilingFan> ceilingFan;
	int prevSpeed;
public:
	CeilingFanHighCommand(std::unique_ptr<CeilingFan> ceilingFan) {
		this->ceilingFan = std::move(ceilingFan);
		prevSpeed = 0;
	}
	void excute() override {
		prevSpeed = ceilingFan->getSpeed();
		ceilingFan->high();
	}
	void undo() override {
		if (prevSpeed == CeilingFan::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::OFF) {
			ceilingFan->off();
		}
	}
	std::string name() override {
		return "CeilingFanHighCommand";
	}
};

class CeilingFanMediumCommand : public Command {
private:
	std::unique_ptr<CeilingFan> ceilingFan;
	int prevSpeed;
public:
	CeilingFanMediumCommand(std::unique_ptr<CeilingFan> ceilingFan) {
		this->ceilingFan = std::move(ceilingFan);
		prevSpeed = 0;
	}
	void excute() override {
		prevSpeed = ceilingFan->getSpeed();
		ceilingFan->medium();
	}
	void undo() override {
		if (prevSpeed == CeilingFan::HIGH) {
			ceilingFan->high();
		}
		else if (prevSpeed == CeilingFan::MEDIUM) {
			ceilingFan->medium();
		}
		else if (prevSpeed == CeilingFan::LOW) {
			ceilingFan->low();
		}
		else if (prevSpeed == CeilingFan::OFF) {
			ceilingFan->off();
		}
	}
	std::string name() override {
		return "CeilingFanMediumCommand";
	}
};

class GarageDoorOpenCommand : public Command {
private:
	std::unique_ptr<GarageDoor> garagedoor;
public:
	GarageDoorOpenCommand(std::unique_ptr<GarageDoor> garagedoor) {
		this->garagedoor = std::move(garagedoor);
	}
	void excute() override {
		garagedoor->up();
	}
	std::string name() override {
		return "GarageDoorOenCommand";
	}
};

class GarageDoorUpCommand : public Command {
private:
	std::unique_ptr<GarageDoor> garagedoor;
public:
	GarageDoorUpCommand(std::unique_ptr<GarageDoor> garagedoor) {
		this->garagedoor = std::move(garagedoor);
	}
	void excute() override {
		garagedoor->up();
	}
	std::string name() override {
		return "GarageDoorUpCommand";
	}
};

class GarageDoorDownCommand : public Command {
private:
	std::unique_ptr<GarageDoor> garagedoor;
public:
	GarageDoorDownCommand(std::unique_ptr<GarageDoor> garagedoor) {
		this->garagedoor = std::move(garagedoor);
	}
	void excute() override {
		garagedoor->down();
	}
	std::string name() override {
		return "GarageDoorDownCommand";
	}
};


class StereoOnWithCDCommand : public Command {
private:
	std::unique_ptr<Stereo> stereo;
public:
	StereoOnWithCDCommand(std::unique_ptr<Stereo> stereo) {
		this->stereo = std::move(stereo);
	}
	void excute() override {
		stereo->on();
		stereo->setCD();
		stereo->setVolume(11);
	}
	std::string name() override {
		return "StereoOnWithCDCommand";
	}
};

class StereoOffCommand : public Command {
private:
	std::unique_ptr<Stereo> stereo;
public:
	StereoOffCommand(std::unique_ptr<Stereo> stereo) {
		this->stereo = std::move(stereo);
	}
	void excute() override {
		stereo->off();
	}
	std::string name() override {
		return "StereoOffCommand";
	}
};


class SimpleRemoteControl {
private:
	std::unique_ptr<Command> slot;
public:
	SimpleRemoteControl() {

	}
	void  setCommand(std::unique_ptr<Command> command)
	{
		slot = std::move(command);
	}
	void buttonWasPressed()
	{
		slot->excute();
	}
};

class RemoteControl {
private:
	std::vector<std::unique_ptr<Command>> onCommands;
	std::vector<std::unique_ptr<Command>> offCommands;
	Command* undoCommand;
public:
	RemoteControl(int num = 7) {
		onCommands.resize(num);
		offCommands.resize(num);
		for (int i = 0; i < 7; i++)
			onCommands[i] = nullptr, offCommands[i] = nullptr;
		undoCommand = nullptr;
	}
	void setCommand(int slot, std::unique_ptr<Command> onCommand, std::unique_ptr<Command> offCommand) {
		onCommands[slot] = std::move(onCommand);
		offCommands[slot] = std::move(offCommand);
	}

	void onButtonWasPressed(int slot) {
		onCommands[slot]->excute();
		undoCommand = onCommands[slot].get();
	}
	void offButtonWasPressed(int slot) {
		offCommands[slot]->excute();
		undoCommand = offCommands[slot].get();
	}
	void undoButtonWasPushed() {
		if (undoCommand) {
			undoCommand->undo();
		}
	}
	std::string toString() {
		std::string buffer;
		buffer += "\n------Remote Control ------\n";
		for (int i = 0; i < onCommands.size(); i++) {
			buffer += "[slot ";
			buffer += std::to_string(i);
			buffer += "] ";
			if (onCommands[i] != nullptr)
				buffer += onCommands[i]->name();
			else
				buffer += "NoComments";
			buffer += "    ";
			if (offCommands[i] != nullptr)
				buffer += offCommands[i]->name();
			else
				buffer += "NoComments";
			buffer += "\n";
		}
		buffer += "[undo] ";
		if (undoCommand)
			buffer += undoCommand->name();
		else
			buffer += "NoComments";
		buffer += "\n";
		return buffer;
	}
};