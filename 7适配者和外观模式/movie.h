#pragma once
#include <iostream>
#include <string>
#include <memory>
/*
外观模式:为子系统中的一组接口提供了一个统一的接口。外观定义了一个更高级别的接口使得子系统更容易使用。
*/
/*
最少知识原则：只和你的密友谈话。
*/
class Tunner;
class StreamingPlayer;

class Amplifier {
private:
	std::string description;
	Tunner* tuner = nullptr;
	StreamingPlayer* player = nullptr;
public:
	Amplifier(std::string description) {
		this->description = description;
	}
	void on() {
		std::cout << description << " on" << std::endl;
	}
	void off() {
		std::cout << description << " off" << std::endl;
	}
	void setStreamSound() {
		std::cout << description << " stereo mode on" << std::endl;
	}
	void setSurroundSound() {
		std::cout << description << " surround sound on (5 speakers, 1 subwoofer)" << std::endl;
	}
	void setVolume(int level) {
		std::cout << description << " setting volume to " << level << std::endl;
	}
	void setTuner(Tunner* tuner) {
		std::cout << description << " setting tuner to " << tuner << std::endl;
		this->tuner = tuner;
	}
	void setStreamingPlayer(StreamingPlayer* playe) {
		std::cout << description << " setting Streaming player to " << player << std::endl;
		this->player = player;
	}
	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const Amplifier* amplifier)
	{
		os << amplifier->description;
		return os;
	}
};

class Tunner {
private:
	std::string description;
	Amplifier* amplifier;
	double frequency;
public:
	Tunner(std::string description, Amplifier* amplifier) {
		this->description = description;
		this->amplifier = amplifier;
	}
	void on() {
		std::cout << description << " on" << std::endl;
	}
	void off() {
		std::cout << description << " off" << std::endl;
	}
	void setFrequency(double frequency) {
		std::cout << description << " setting frequency to " << frequency << std::endl;
		this->frequency = frequency;
	}
	void setAm() {
		std::cout << description << " setting AM mode" << std::endl;
	}
	void setFm() {
		std::cout << description << " setting FM mode" << std::endl;
	}
	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const Tunner* tuner)
	{
		os << tuner->description;
		return os;
	}
};


class StreamingPlayer {
private:
	std::string description;
	int currentChapter;
	Amplifier* amplifier;
	std::string movie;
public:
	StreamingPlayer(std::string description, Amplifier* amplifier) {
		this->description = description;
		this->amplifier = amplifier;
	}
	void on() {
		std::cout << description << " on" << std::endl;
	}
	void off() {
		std::cout << description << " off" << std::endl;
	}
	void play(std::string movie) {
		this->movie = movie;
		currentChapter = 0;
		std::cout << description << " playing \"" << movie << "\"" << std::endl;
	}
	void play(int chapter) {
		if (movie == "") {
			std::cout << " can't play chapter " << chapter << " no movie selected" << std::endl;
		}
		else {
			currentChapter = chapter;
			std::cout << description << " playing chapter " << currentChapter << " of\"" << movie << "\"" << std::endl;
		}
	}
	void stop() {
		currentChapter = 0;
		std::cout << description << " stopped \"" << movie << "\"" << std::endl;
	}
	void pause() {
		std::cout << description << " paused \"" << movie << "\"" << std::endl;
	}
	void setTwoChannelAudio() {
		std::cout << description << " set two channel audio" << std::endl;
	}
	void setSurroundAudio() {
		std::cout << description << " set surround audio" << std::endl;
	}
	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const StreamingPlayer* streamingPlayer)
	{
		os << streamingPlayer->description;
		return os;
	}
};

class Projector {
private:
	std::string description;
	StreamingPlayer* player;
public:
	Projector(std::string description, StreamingPlayer* player) {
		this->description = description;
		this->player = player;
	}

	void on() {
		std::cout << description << " on" << std::endl;
	}

	void off() {
		std::cout << description << " off" << std::endl;
	}

	void wideScreenMode() {
		std::cout << description << " in widescreen mode (16x9 aspect ratio)" << std::endl;
	}

	void tvMode() {
		std::cout << description + " in tv mode (4x3 aspect ratio)" << std::endl;
	}

	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const Projector* projector)
	{
		os << projector->description;
		return os;
	}
};


class TheaterLights {
private:
	std::string description;
public:
	TheaterLights(std::string description) {
		this->description = description;
	}
	void on() {
		std::cout << description << " on" << "\n";
	}
	void off() {
		std::cout << description << " off" << '\n';
	}
	void dim(int level) {
		std::cout << " dimming to " << level << "%" << "\n";
	}
	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const TheaterLights* theaterlights)
	{
		os << theaterlights->description;
		return os;
	}
};

class PopcornPopper {
private:
	std::string description;
public:
	PopcornPopper(std::string description) {
		this->description = description;
	}
	void on() {
		std::cout << description << " on\n";
	}
	void off() {
		std::cout << description << " off\n";
	}
	void pop() {
		std::cout << description << " popping popcorn!" << "\n";
	}
	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const PopcornPopper* popcornpopper)
	{
		os << popcornpopper->description;
		return os;
	}
};

class Screen {
private:
	std::string description;
public:
	Screen(std::string description) {
		this->description = description;
	}
	void up() {
		std::cout << description << " going up\n";
	}
	void down() {
		std::cout << description << " going down\n";
	}
	std::string toString() {
		return description;
	}
	friend std::ostream& operator<<(std::ostream& os, const Screen* screen)
	{
		os << screen->description;
		return os;
	}
};




class HomeTheaterFacade {
private:
	std::unique_ptr<Amplifier> amp;
	std::unique_ptr<Tunner> tunner;
	std::unique_ptr<StreamingPlayer> player;
	std::unique_ptr<Projector> projector;
	std::unique_ptr<TheaterLights> lights;
	std::unique_ptr<Screen> screen;
	std::unique_ptr<PopcornPopper> popper;
public:
	HomeTheaterFacade(std::unique_ptr<Amplifier> amp, std::unique_ptr<Tunner> tunner, std::unique_ptr<StreamingPlayer> player, std::unique_ptr<Projector> projector, std::unique_ptr<TheaterLights> lights, std::unique_ptr<Screen> screen,
		std::unique_ptr<PopcornPopper> popper) {
		this->amp = std::move(amp);
		this->tunner = std::move(tunner);
		this->player = std::move(player);
		this->projector = std::move(projector);
		this->lights = std::move(lights);
		this->screen = std::move(screen);
		this->popper = std::move(popper);
	}
	void watchMovie(std::string movie) {
		std::cout << "Get ready to watch a movie..." << '\n';
		popper->on();
		popper->pop();
		lights->dim(10);
		screen->down();
		projector->on();
		projector->wideScreenMode();
		amp->on();
		amp->setStreamingPlayer(player.get());
		amp->setSurroundSound();
		amp->setVolume(5);
		player->on();
		player->play(movie);
	}
	void endMovie() {
		std::cout << "Shutting movie theater down..." << "\n";
		popper->off();
		lights->on();
		screen->up();
		projector->off();
		amp->off();
		player->stop();
		player->off();
	}
};