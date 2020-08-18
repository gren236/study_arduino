const int EN = 9; // Motor enable pin (EN)
const int MC1 = 3; // Motor control input 1
const int MC2 = 2; // Motor control input 2
const int POT = 0; // Analog input for potentiometer

int val = 0; // Var holding the potentiometer value
int velocity = 0; // Var holding the motor speed value (0-255)

void setup() {
  pinMode(EN, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  brake(); // Stop motor during init
}

// Spin the motor forward with given speed (0-255)
void forward(int rate) {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);
}

// Spin the motor in the reverse direction with given speed (0-255)
void reverse(int rate) {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN, rate);
}

// Stop the motor
void brake() {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  analogWrite(EN, HIGH);
}

void loop() {
  val = analogRead(POT);
  // Go forward
  if (val > 562) {
    velocity = map(val, 263, 1023, 0, 255);
    forward(velocity);
  }
  // Go back
  else if (val < 462) {
    velocity = map(val, 461, 0, 0, 255);
    reverse(velocity);
  }
  // Break
  else {
    brake();
  }
}
