#include "PotentiometerInput.hpp"

PotentiometerInput::PotentiometerInput(uint8_t pin, bool invertReading)
		: _pin(pin), _invertReading(invertReading)
{
}

void PotentiometerInput::setup()
{
	pinMode(_pin, INPUT);
}

float PotentiometerInput::getMeasurement()
{
	float value = analogRead(_pin) / 1023.0f;
	return _invertReading ? 1.0f - value : value;
}