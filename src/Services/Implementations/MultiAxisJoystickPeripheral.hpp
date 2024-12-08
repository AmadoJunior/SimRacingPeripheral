#ifndef MULTI_AXIS_JOYSTICK_H
#define MULTI_AXIS_JOYSTICK_H

#include "Libs/Core.hpp"
#include "Services/Interfaces/IJoystickPeripheral.hpp"
#include "Joystick.h"

class MultiAxisJoystickPeripheral : public IJoystickPeripheral
{
public:
	MultiAxisJoystickPeripheral();

	void setup() override;
	void updateState() override;
	void setAxisValue(uint8_t axisIndex, float value) override;
	void configureAxis(uint8_t axisIndex, JoystickAxis axis,
										 uint16_t minValue = 0, uint16_t maxValue = 1023,
										 bool invertOutput = false) override;

private:
	Joystick_ _joystick;
	AxisConfig _axes[MAX_AXES] = {
			AxisConfig(JoystickAxis::X), // Initialize with Dummy Axis
			AxisConfig(JoystickAxis::Y), // Initialize with Dummy Axis
			AxisConfig(JoystickAxis::Z)	 // Initialize with Dummy Axis
	};
	static constexpr uint8_t JOYSTICK_ID = 0x06;

	int mapValueToRange(float value, const AxisConfig &config);
	void setJoystickValue(JoystickAxis axis, int value);
};
#endif