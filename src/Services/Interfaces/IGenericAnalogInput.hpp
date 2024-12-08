#ifndef I_GENERIC_ANALOG_INPUT_H
#define I_GENERIC_ANALOG_INPUT_H

class IGenericAnalogInput
{
public:
	virtual ~IGenericAnalogInput() = default;
	virtual void setup() = 0;
	virtual float getMeasurement() = 0;
};
#endif
