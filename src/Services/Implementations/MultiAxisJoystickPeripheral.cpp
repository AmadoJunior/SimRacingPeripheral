#include "MultiAxisJoystickPeripheral.hpp"

MultiAxisJoystickPeripheral::MultiAxisJoystickPeripheral()
		: _joystick(JOYSTICK_ID, JOYSTICK_TYPE_JOYSTICK,
								0, 0,										// Button count, Hat switch count
								true, true, true,				// X, Y, Z
								true, true, true,				// Rx, Ry, Rz
								true,										// Rudder
								true, true, true, true) // Throttle, Accelerator, Brake, Steering
{
	// Initialize Axes Disabled
	for (uint8_t i = 0; i < MAX_AXES; i++)
	{
		_axes[i].enabled = false;
	}
}

void MultiAxisJoystickPeripheral::setup()
{
	_joystick.begin();
}

void MultiAxisJoystickPeripheral::updateState()
{
}

void MultiAxisJoystickPeripheral::configureAxis(
		uint8_t axisIndex,
		JoystickAxis axis,
		uint16_t minValue,
		uint16_t maxValue,
		bool invertOutput)
{
	if (axisIndex < MAX_AXES)
	{
		_axes[axisIndex].axis = axis;
		_axes[axisIndex].minValue = minValue;
		_axes[axisIndex].maxValue = maxValue;
		_axes[axisIndex].invertOutput = invertOutput;
		_axes[axisIndex].enabled = true;
	}
}

void MultiAxisJoystickPeripheral::setAxisValue(uint8_t axisIndex, float value)
{
	if (axisIndex < MAX_AXES && _axes[axisIndex].enabled)
	{
		int mappedValue = mapValueToRange(value, _axes[axisIndex]);
		setJoystickValue(_axes[axisIndex].axis, mappedValue);
	}
}

int MultiAxisJoystickPeripheral::mapValueToRange(float value, const AxisConfig &config)
{
	value = constrain(value, 0.0f, 1.0f);

	if (config.invertOutput)
	{
		value = 1.0f - value;
	}

	return (int)(config.minValue + (value * (config.maxValue - config.minValue)));
}

void MultiAxisJoystickPeripheral::setJoystickValue(JoystickAxis axis, int value)
{
	switch (axis)
	{
	case JoystickAxis::X:
		_joystick.setXAxis(value);
		break;
	case JoystickAxis::Y:
		_joystick.setYAxis(value);
		break;
	case JoystickAxis::Z:
		_joystick.setZAxis(value);
		break;
	case JoystickAxis::RX:
		_joystick.setRxAxis(value);
		break;
	case JoystickAxis::RY:
		_joystick.setRyAxis(value);
		break;
	case JoystickAxis::RZ:
		_joystick.setRzAxis(value);
		break;
	case JoystickAxis::RUDDER:
		_joystick.setRudder(value);
		break;
	case JoystickAxis::THROTTLE:
		_joystick.setThrottle(value);
		break;
	case JoystickAxis::ACCELERATOR:
		_joystick.setAccelerator(value);
		break;
	case JoystickAxis::BRAKE:
		_joystick.setBrake(value);
		break;
	case JoystickAxis::STEERING:
		_joystick.setSteering(value);
		break;
	}
}
