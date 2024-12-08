#include "HX711Peripheral.hpp"

HX711Peripheral::HX711Peripheral(uint8_t dataPin, uint8_t clockPin)
		: _dataPin(dataPin), _clockPin(clockPin)
{
}

HX711Peripheral::HX711Peripheral(
		uint8_t dataPin,
		uint8_t clockPin,
		uint8_t tareReps,
		int32_t cellScaling,
		int32_t cellMax,
		int8_t cellPolarity) : _dataPin(dataPin),
													 _clockPin(clockPin)
{

	this->tareReps = tareReps;
	this->cellScaling = cellScaling;
	this->cellMax = cellMax;
	this->cellPolarity = cellPolarity;
}
void HX711Peripheral::setup()
{
	this->HX711Instance.begin(this->_dataPin, this->_clockPin);
	this->HX711Instance.tare(this->tareReps);
}

float HX711Peripheral::getMeasurement()
{
	int32_t readingScaled = this->HX711Instance.get_value() / this->cellScaling;

	switch (this->cellPolarity)
	{
	case 1:
		readingScaled = max(0, readingScaled);
		break;
	case -1:
		readingScaled = min(0, readingScaled);
		break;
	}

	return readingScaled / this->cellMax;
}