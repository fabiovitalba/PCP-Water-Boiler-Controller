# Fabio Vitalba - Arduino Water Boiler Controller ('Boil Voyage')
This is the final project for the course "Physical Computing Project 24/25" for Fabio Vitalba.

## Boil Voyage
The Project is divided into two repositories. This repository is the Arduino Controller that controls the 3D world created in Unity.
Find the other repository here: [Ship Navigation Project (Boil Voyage)](https://github.com/fabiovitalba/PCP-Ship-Project).

## 1. Description
This Arduino Project consists in the arduino script that handles the Water Boiler Controller. It reads from three different sensors/resistors:
- A **rotary potentiometer** that is hidden in the bottom part of the water boiler. It is used in order to read the rotation of the water boiler.
- A **photocell** that is placed inside the water boiler in order to read the amount of light shining into the inside of the water boiler. This is used to measure how much light is led in by the water boiler lid.
- A **switch** directly taken from the water boiler circuit. The switch consists in a broken circuit that closes whenever the button on the handle of the water boiler is closed.

These inputs are used to produce the following outputs:
- **SensorAbsoluteRotationValue**: The raw output produced by the rotary potentiometer.
- **AbsoluteRotationValue**: The absolute rotation of the water boiler. This is the processed output produced by the rotary potentiometer.
- **RelativeRotationValue**: The rotation of the water boiler, relative to its starting position. The starting position is also continuously updated, so that anytime the user reverses the rotation, that reversal is immediately effective.
- **SwitchValue**: The output produced by the switch circuit. Whenever the switch is not being pressed this will be 0. However, when the switch is being pressed, the circuit closes and the value will raise.
- **SensorLightValue**: The raw output produced by the photocell.
- **LightValue**: The output produced by the photocell. Whenever the lid is closed a base-amount of light is entering the water boiler from the sidewalls. Once the lid is opened (even when only partially open), more light enters and the output of the photocell will raise.

## 2. Visuals
![Image of the Controller package](/Images/controller-01.jpeg)
![Image of the Controller insides](/Images/controller-02.jpeg)
![Circuit design in fritzing](/Fritzing/arduino_circuit_design.png)

Find some more detailed images of the [build process](/BUILDHISTORY.md).

## 3. Installation
The Water Boiler Controller can be used as is, but should be tuned based on the environment it's being used in. The arduino script contains a few constants that should be tuned based on the baseline values you might find during usage.

### 3.1. Rotation settings
_In order to tune these settings, listen to the Arduino on the Serial Port (default is 9600). Open the Serial Plotter, then continue._
- `MIN_ROTATION_VALUE`: Rotate the water boiler completely to the left. Read the value for `SensorAbsoluteRotationValue` and set the constant `MIN_ROTATION_VALUE` to this value. (Rounding the value up a little is fine.)
- `MAX_ROTATION_VALUE`: Rotate the water boiler completely to the right. Read the value for `SensorAbsoluteRotationValue` and set the constant `MIN_ROTATION_VALUE` to this value. (Rounding the value down a little is fine.)
- `MAX_REL_ROTATION_VALUE`: This value defines the maximum rotation value before the relative starting position is moved in the rotation direction. A higher value means that rotations are harder to reverse, a smaller value means that rotations are quick to reverse. Default value is `40`.

### 3.2. Switch settings
_In order to tune these settings, listen to the Arduino on the Serial Port (default is 9600). Open the Serial Plotter, then continue._
- `SWITCH_TRIGGER_VALUE`: This is the minimum value for the Switch Circuit to count as "triggered". Usually the switch - in unpressed mode - should have a value of 0, so anything above 0 should mean that the switch is triggered. To avoid unwanted behaviour, we set a theshold in order to be sure that the switch was triggered correctly. Default value is `300`.

### 3.3. Light settings
_In order to tune these settings, listen to the Arduino on the Serial Port (default is 9600). Open the Serial Plotter, then continue._
- `MIN_LIGHT_VALUE`: Place the water boiler in the position you want to use it and close the water boiler lid. Read the value for `SensorLightValue` and set the constant `MIN_LIGHT_VALUE` to this value. It is a good idea to add 10-20 to the constant's value to account for slight lighting variations.
- `MAX_LIGHT_VALUE`: Place the water boiler in the position you want to use it and open the water boiler lid completely. Read the value for `SensorLightValue` and set the constant `MAX_LIGHT_VALUE` to this value. (Rounding the value down a little is fine.)

## 4. Usage
The Water Boiler Controller emits the following values on the Serial Port (default 9600):
- **AbsoluteRotationValue**: Provides a value between `-127` and `127` to indicate the absolute rotation position for the rotary potentiometer.
- **RelativeRotationValue**: Provides a value between `-MAX_REL_ROTATION_VALUE` and `MAX_REL_ROTATION_VALUE` relative to the starting position of the controller.
- **SwitchValue**: Provides a value between `0` and `1`. Anything that is above `SWITCH_TRIGGER_VALUE` activates the internal LED and should be counted as triggered/active.
- **LightValue**: Provides a value between `0` and `255`. The higher the value, the more light is entering the water boiler.

Sample output: `SensorAbsoluteRotationValue:473.00,AbsoluteRotationValue:-31,RelativeRotationValue:0,SwitchValue:0,SensorLightValue:519.00,LightValue:0`

## 5. Support
For issues feel free to contact me on fvitalba@unibz.it, or by opening an Issue on the Repository.

## 6. Contributing
Currently this project is not open for contributions at it is in very early stages of development.

## 7. Authors and acknowledgment
- Main author: Fabio Vitalba

## 8. License
MIT License
Copyright (c) 2025 Fabio Vitalba

## 9. Project status
This Project is currently being worked on.
