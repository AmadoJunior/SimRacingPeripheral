#ifndef I_INPUT_PERIPHERAL_H
#define I_INPUT_PERIPHERAL_H

class IInputPeripheral
{
public:
	virtual ~IInputPeripheral() = default;
	virtual void setup() = 0;
	virtual float getMeasurement() = 0;
};
#endif
