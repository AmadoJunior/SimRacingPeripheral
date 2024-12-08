#ifndef I_LoadCell_H
#define I_LoadCell_H

#include "Libs/Core.hpp"
#include "Services/Interfaces/IInputPeripheral.hpp"

class ILoadCellPeripheral : public IInputPeripheral
{
public:
	uint8_t tareReps = 100;
	int32_t cellScaling = 1100;
	float cellMax = 1000;
	int8_t cellPolarity = 1;

	virtual ~ILoadCellPeripheral() = default;
	virtual void setup() = 0;
	virtual float getMeasurement() = 0;
};

#endif