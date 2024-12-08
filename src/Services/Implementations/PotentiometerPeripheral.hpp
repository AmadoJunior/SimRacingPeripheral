#ifndef POTENTIOMETER_PERIPHERAL_H
#define POTENTIOMETER_PERIPHERAL_H

#include "Libs/Core.hpp"
#include "Services/Interfaces/IGenericAnalogInput.hpp"

class PotentiometerPeripheral : public IGenericAnalogInput
{
public:
	PotentiometerPeripheral(uint8_t pin, bool invertReading = false)
			: _pin(pin), _invertReading(invertReading) {}

	void setup() override
	{
		pinMode(_pin, INPUT);
	}

	float getMeasurement() override
	{
		float value = analogRead(_pin) / 1023.0f;
		return _invertReading ? 1.0f - value : value;
	}

private:
	uint8_t _pin;
	bool _invertReading;
};
#endif