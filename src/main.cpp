#include "Config.hpp"
#include "Services/Implementations/MultiAxisJoystickPeripheral.hpp"
#include "Services/Implementations/HX711Peripheral.hpp"
#include "Services/Implementations/PotentiometerPeripheral.hpp"

// #define DEBUG

MultiAxisJoystickPeripheral joystick;
IInputPeripheral *inputs[DEVICE_CONFIG.NUM_AXES];

void setupInputs()
{
  // Initialize Inputs
  for (uint8_t i = 0; i < DEVICE_CONFIG.NUM_AXES; i++)
  {
    const auto &config = DEVICE_CONFIG.inputs[i];

    // Create Input Peripheral Based on Type
    switch (config.type)
    {
    case InputType::LOAD_CELL:
    {
      const auto &lc = config.config.loadCell;
      inputs[i] = new HX711Peripheral(
          lc.dataPin,
          lc.clockPin,
          lc.tareReps,
          lc.scaling,
          lc.maxValue,
          lc.polarity);
      break;
    }
    case InputType::POTENTIOMETER:
    {
      const auto &pot = config.config.potentiometer;
      inputs[i] = new PotentiometerPeripheral(
          pot.pin,
          pot.invertReading);
      break;
    }
    }
  }
}

void setupJoystick()
{
  // Configure Joystick Axes
  for (uint8_t i = 0; i < DEVICE_CONFIG.NUM_AXES; i++)
  {
    const auto &axisConfig = DEVICE_CONFIG.axes[i];
    joystick.configureAxis(
        i,
        axisConfig.axis,
        axisConfig.minValue,
        axisConfig.maxValue,
        axisConfig.invertOutput);
  }
}

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif

  setupInputs();

  // Initialize Inputs
  for (uint8_t i = 0; i < DEVICE_CONFIG.NUM_AXES; i++)
  {
    inputs[i]->setup();
  }

  setupJoystick();
  joystick.setup();

  // Turn Off TX & RX LEDs
  TXLED0;
  RXLED0;
}

void loop()
{
  // Update Axes
  for (uint8_t i = 0; i < DEVICE_CONFIG.NUM_AXES; i++)
  {
    float value = inputs[i]->getMeasurement();

#ifdef DEBUG
    Serial.print("Axis ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);
#endif

    joystick.setAxisValue(i, value);
  }

#ifdef DEBUG
  delay(100);
#endif
}

void cleanUp()
{
  for (uint8_t i = 0; i < DEVICE_CONFIG.NUM_AXES; i++)
  {
    if (inputs[i] != nullptr)
    {
      delete inputs[i];
      inputs[i] = nullptr;
    }
  }
}