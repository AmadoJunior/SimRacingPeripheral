#ifndef HX711_LoadCell_H
#define HX711_LoadCell_H

#include "Libs/Core.hpp"
#include "Services/Interfaces/ILoadCellInput.hpp"
#include <HX711.h>

class HX711LoadCellInput : public ILoadCellInput
{
public:
	HX711LoadCellInput(uint8_t dataPin, uint8_t clockPin);
	HX711LoadCellInput(
			uint8_t dataPin,
			uint8_t clockPin,
			uint8_t tareReps,
			int32_t cellScaling,
			int32_t cellMax,
			int8_t cellPolarity);
	void setup() override;
	float getMeasurement() override;

private:
	HX711 HX711Instance;
	uint8_t _dataPin;
	uint8_t _clockPin;
};

#endif