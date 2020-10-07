// Comfortable tmp boundaries
// Voltage at pin in milliVolts = (reading from ADC) * (5000/1024)
// Centigrade temperature = [(analog voltage in mV) - 500] / 10
const int LOWER_BOUND = 153; // 24.7C
const int UPPER_BOUND = 164; // 30C

// RGB pins
const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;

// TMP pin
const int A_TMP = 0;

// TMP storage
int val = 0;

void setup() {
  // Set up pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  // Set up serial port reading
  Serial.begin(9600);
}

/**
 * Print ADC tmp value and absolute celsius tmp
 */
void printTmp(int tmpVal) {
  float tmpCel;
  tmpCel = ((float)tmpVal * (5000.0 / 1024.0) - 500.0) / 10.0;
  Serial.print(tmpVal); Serial.print(" - "); Serial.print((int)tmpCel); Serial.println("C");
  delay(500);
}

void loop() {
  // Get analog value of TMP
  val = analogRead(A_TMP);

  printTmp(val);

  if (val > UPPER_BOUND) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  } else if (val < LOWER_BOUND) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
  } else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  }
}
