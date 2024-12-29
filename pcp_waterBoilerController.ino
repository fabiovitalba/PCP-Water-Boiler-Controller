/// LAYOUT BASED PARAMETERS ///
const int SWITCH_PIN = A1;
const int ROTATION_PIN = A0;
const int LIGHT_PIN = A2;
const int LED_PIN = 10;


/// ENVIRONMENT RELATIVE PARAMETERS ///
const int MIN_ROTATION_VALUE = 350;
const int MAX_ROTATION_VALUE = 675;

// The switch can assume values between 0 and ~600-700.
// We assume that a minimum value (like 300) has to be met in order to count as active.
const int SWITCH_TRIGGER_VALUE = 300;

// In absolute darkness the light sensor still return about ~500 (~580 with the lid closed) as a value.
// At maximum brightness the light sensor reaches about ~660  (with the lid open and beneath a lamp).
const int MIN_LIGHT_VALUE = 580;
const int MAX_LIGHT_VALUE = 660;


/// RELATIVE PARAMETERS ///
int startingRotationValue = 0.0f;

void setup() {
  pinMode(SWITCH_PIN, INPUT);
  pinMode(ROTATION_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  // Reset switch indicator LED to off
  digitalWrite(LED_PIN, LOW);

  // Store the Starting Position for the variable resistor in order to be able to use the controller without
  // any particular starting position.
  startingRotationValue = getRotationValueFromSensorValue(analogRead(ROTATION_PIN));
}

void loop() {
  // We read the variable resistors value in order to understand the water boilers position.
  int absoluteRotationValue = getRotationValueFromSensorValue(analogRead(ROTATION_PIN));

  // We use the Relative Rotation Value in order to ignore the starting position of the variable resistor.
  // A rotation to the left is translated into a positive value and a rotation to the right becomes a negative value.
  int relativeRotationValue = startingRotationValue - absoluteRotationValue;

  // We read the value from the Water Boiler built-in switch and light the led as an indicator.
  int switchValue = analogRead(SWITCH_PIN);
  if (switchValue >= SWITCH_TRIGGER_VALUE) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // We read the light reactive resistor's value in order to understand how far the water boilers lid
  // is opened.
  int lightValue = getLightValueFromSensorValue(analogRead(LIGHT_PIN));


  Serial.print("AbsoluteRotationValue:"); Serial.print(absoluteRotationValue);
  Serial.print(",");
  Serial.print("RelativeRotationValue:"); Serial.print(relativeRotationValue);
  Serial.print(",");
  Serial.print("SwitchValue:"); Serial.print(switchValue);
  Serial.print(",");
  Serial.print("LightValue:"); Serial.print(lightValue);
  Serial.println();
  delay(10);
}

int clampFloatToIntRange(float inputValue, int minIn, int maxIn, int minOut, int maxOut) {
  int clampedValue = map(inputValue, minIn, maxIn, minOut, maxOut);
  clampedValue = constrain(clampedValue, minOut, maxOut);
  return clampedValue;
}

int getRotationValueFromSensorValue(float sensorValue) {
  return clampFloatToIntRange(sensorValue, MIN_ROTATION_VALUE, MAX_ROTATION_VALUE, -127, 127);
}

int getLightValueFromSensorValue(float sensorValue) {
  return clampFloatToIntRange(sensorValue, MIN_LIGHT_VALUE, MAX_LIGHT_VALUE, 0, 255);
}
