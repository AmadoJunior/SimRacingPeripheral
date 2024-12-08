#ifndef POTENTIOMETER_INPUT_H
#define POTENTIOMETER_INPUT_H

#include "Libs/Core.hpp"
#include "Services/Interfaces/IGenericAnalogInput.hpp"

class PotentiometerInput : public IGenericAnalogInput
{
public:
	PotentiometerInput(uint8_t pin, bool invertReading = false);
	void setup() override;
	float getMeasurement() override;

private:
	uint8_t _pin;
	bool _invertReading;
};

#endif