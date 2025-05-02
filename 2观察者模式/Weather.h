#pragma once
//观察者模式定义对象之间一对多的依赖，这样一来，当一个对象改变状态时，它的所有对象都会收到通知并自动更新
//尽量做到交互的对象之间松耦合设计。
#include <iostream>
#include <vector>
#include <algorithm>
class Observe;
class Subject
{
public:
	virtual void registerObserver(Observe* o) = 0;
	virtual void removeObsercer(Observe* o) = 0;
	virtual void notifyObservers() = 0;
	virtual ~Subject() = default;
};

class Observe {
public:
	virtual void update(float temp, float humidity, float pressure) = 0;
};

class DisplayElement {
public:
	virtual void display() = 0;
};

class CurrentConditionsDisplay : public Observe, public DisplayElement
{
private:
	float temperature;
	float humidity;
	float pressure;
	std::shared_ptr<Subject> weatherData;
public:
	CurrentConditionsDisplay(std::shared_ptr<Subject> wd) : weatherData(std::move(wd))
	{
		weatherData->registerObserver(this);
	}
	~CurrentConditionsDisplay() {
		if (weatherData)
			weatherData->removeObsercer(this);
	}
	void update(float temp, float humi, float pres) {
		temperature = temp;
		humidity = humi;
		pressure = pres;
		display();
	}
	void display() {
		std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "\% humidity\n";
	}
};

class HeatIndexDisplay : public Observe, public DisplayElement {
private:
	float temperature;
	float humidity;
	float pressure;
	float heat;
	std::shared_ptr<Subject> weatherData;
	float cacl_heat(int T, int R) {
		return (-42.379 + (2.04901523 * T) + (10.14333127 * R) - (0.22475541 * T * R) - (6.83783e-3 * T * T) - (5.481717e-2 * R * R)
			+ (1.22874e-3 * T * T * R) + (8.5282e-4 * T * R * R) - (1.99e-6 * T * T * R * R));
	}
public:
	HeatIndexDisplay(std::shared_ptr<Subject> wd) : weatherData(std::move(wd))
	{
		weatherData->registerObserver(this);
	}
	~HeatIndexDisplay() {
		if (weatherData)
			weatherData->removeObsercer(this);
	}
	void update(float temp, float humi, float pres) {
		temperature = temp;
		humidity = humi;
		pressure = pres;
		display();
	}
	void display() {
		std::cout << "Current conditions: " << temperature << "F degrees and " << humidity << "\% humidity\n";
		std::cout << "Heat index is " << cacl_heat(temperature, humidity) << "\n";
	}
};

class WeatherData : public Subject
{
private:
	std::vector<Observe*> observes;
	float temperature;
	float humidity;
	float pressure;
public:
	WeatherData(float temp = 0, float humi = 0, float pres = 0) {
		temperature = temp;
		humidity = humi;
		pressure = pres;
	}
	virtual void registerObserver(Observe* o) override {
		if (std::find(observes.begin(), observes.end(), o) == observes.end()) {
			observes.push_back(o);
		}
	}
	virtual void removeObsercer(Observe* o) override {
		observes.erase(
			std::remove(observes.begin(), observes.end(), o),
			observes.end()
		);
		/*
		auto it = std::find(observes.begin(), observes.end(), o);
		if (it != observes.end()) {
			observes.erase(it);
		}*/
	}
	virtual void notifyObservers() override {
		for (auto& observer : observes) {
			observer->update(temperature, humidity, pressure);
		}
	}
	float getTemperature() {
		return temperature;
	}
	float getHumidity() {
		return humidity;
	}
	float getPressure() {
		return pressure;
	}
	void measurementsChanged() {
		notifyObservers();
	}
	void setMeasurements(float temp, float humi, float pres)
	{
		temperature = temp;
		humidity = humi;
		pressure = pres;
		measurementsChanged();
	}
};