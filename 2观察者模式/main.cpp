#include "Weather.h"
#include <iostream>
#include <memory>

using namespace std;

int main()
{
	std::shared_ptr<WeatherData> weatherData = std::make_shared<WeatherData>();

	CurrentConditionsDisplay currentDisplay(weatherData);
	HeatIndexDisplay heatDisplay(weatherData);

	weatherData->setMeasurements(80.0f, 65.0f, 30.4f);
	weatherData->setMeasurements(82.0f, 70.0f, 29.2f);
	weatherData->setMeasurements(78.0f, 90.0f, 29.2f);

	return 0;
}