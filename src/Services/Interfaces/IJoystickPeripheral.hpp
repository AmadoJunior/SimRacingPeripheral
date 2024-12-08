#ifndef I_JOYSTICK_H
#define I_JOYSTICK_H

#include "Libs/Core.hpp"

enum class JoystickAxis
{
	X,
	Y,
	Z,
	RX,
	RY,
	RZ,
	RUDDER,
	THROTTLE,
	ACCELERATOR,
	BRAKE,
	STEERING
};

struct AxisConfig
{
	AxisConfig(JoystickAxis axis_, uint16_t minValue_ = 0, uint16_t maxValue_ = 1023,
						 bool invertOutput_ = false, bool enabled_ = false)
			: axis(axis_), minValue(minValue_), maxValue(maxValue_), invertOutput(invertOutput_), enabled(enabled_)
	{
	}
	JoystickAxis axis;
	uint16_t minValue;
	uint16_t maxValue;
	bool invertOutput;
	bool enabled;
};

class IJoystickPeripheral
{
public:
	static const uint8_t MAX_AXES = 3;

	virtual ~IJoystickPeripheral() = default;
	virtual void setup() = 0;
	virtual void updateState() = 0;
	virtual void setAxisValue(uint8_t axisIndex, float value) = 0;
	virtual void configureAxis(uint8_t axisIndex, JoystickAxis axis,
														 uint16_t minValue = 0, uint16_t maxValue = 1023,
														 bool invertOutput = false) = 0;
};
#endif