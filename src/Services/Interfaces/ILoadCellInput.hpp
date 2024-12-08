#ifndef I_LoadCell_INPUT_H
#define I_LoadCell_INPUT_H

#include "Libs/Core.hpp"
#include "Services/Interfaces/IGenericAnalogInput.hpp"

class ILoadCellInput : public IGenericAnalogInput
{
public:
	uint8_t tareReps = 100;
	int32_t cellScaling = 1100;
	float cellMax = 1000;
	int8_t cellPolarity = 1;

	virtual ~ILoadCellInput() = default;
	virtual void setup() = 0;
	virtual float getMeasurement() = 0;
};

#endif