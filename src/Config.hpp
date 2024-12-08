#ifndef CONFIG_H
#define CONFIG_H

#include "Libs/Core.hpp"
#include "Services/Implementations/MultiAxisJoystickPeripheral.hpp"
#include "Services/Interfaces/IJoystickPeripheral.hpp"

#define HANDBRAKE_CONFIG
// #define PEDALS_CONFIG

enum class InputType
{
	LOAD_CELL,
	POTENTIOMETER
};

struct PinConfig
{
	uint8_t dataPin;
	uint8_t clockPin;
};

struct LoadCellConfig
{
	uint8_t dataPin;
	uint8_t clockPin;
	uint8_t tareReps;
	int32_t scaling;
	int32_t maxValue;
	int8_t polarity;
};

struct PotConfig
{
	uint8_t pin;
	bool invertReading;
};

struct InputConfig
{
	InputType type;
	union
	{
		LoadCellConfig loadCell;
		PotConfig potentiometer;
	} config; // Named Union Member
};

#ifdef HANDBRAKE_CONFIG
const struct DeviceConfig
{
	static constexpr uint8_t NUM_AXES = 1;

	const InputConfig inputs[NUM_AXES] = {
			{InputType::LOAD_CELL,
			 {LoadCellConfig{
					 15,		// dataPin
					 14,		// clockPin
					 100,		// tareReps
					 -1100, // scaling
					 -1000, // maxValue
					 -1			// polarity
			 }}}};

	const AxisConfig axes[NUM_AXES] = {
			AxisConfig{
					JoystickAxis::RUDDER,
					0,		// minValue
					1023, // maxValue
					true, // invertOutput
					true	// enabled
			}};
} DEVICE_CONFIG;
#endif

#ifdef PEDALS_CONFIG
const struct DeviceConfig
{
	static constexpr uint8_t NUM_AXES = 3;

	const InputConfig inputs[NUM_AXES] = {
			// Clutch - Potentiometer
			{
					InputType::POTENTIOMETER,
					{PotConfig{
							A0,		// pin
							false // invertReading
					}}},
			// Brake - Load Cell
			{
					InputType::LOAD_CELL,
					{LoadCellConfig{
							4,		 // dataPin
							5,		 // clockPin
							100,	 // tareReps
							-1100, // scaling
							-1000, // maxValue
							-1		 // polarity
					}}},
			// Gas - Potentiometer
			{
					InputType::POTENTIOMETER,
					{PotConfig{
							A1,		// pin
							false // invertReading
					}}}};

	const AxisConfig axes[NUM_AXES] = {
			AxisConfig{JoystickAxis::CLUTCH, 0, 1023, false, true},
			AxisConfig{JoystickAxis::BRAKE, 0, 1023, true, true},
			AxisConfig{JoystickAxis::ACCELERATOR, 0, 1023, false, true}};
} DEVICE_CONFIG;
#endif

#endif // CONFIG_H