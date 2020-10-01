// H-bridge control pins
const int RIGHT_EN = 9;     // Enabler for right engine
const int RIGHT_MC1 = 2;    // First right switch
const int RIGHT_MC2 = 3;    // Second right switch
const int LEFT_EN = 10;     // Enabler for left engine
const int LEFT_MC1 = 4;     // First left switch
const int LEFT_MC2 = 5;     // Second left switch

const int LEFT_LIGHT_SENSOR = 0;    // Photoresistor pin (A0)
const int RIGHT_LIGHT_SENSOR = 1;   // Photoresistor pin (A1)

const int LIGHT_THRESHOLD_MIN = 810;    // Min light to start moving
const int LIGHT_THRESHOLD_MAX = 1100;   // Min light to start moving
const int SPEED_MIN = 150;              // Min rotating speed
const int SPEED_MAX = 255;              // Max rotating speed

void setup()
{
    pinMode(RIGHT_EN, OUTPUT);
    pinMode(RIGHT_MC1, OUTPUT);
    pinMode(RIGHT_MC2, OUTPUT);
    pinMode(LEFT_EN, OUTPUT);
    pinMode(LEFT_MC1, OUTPUT);
    pinMode(LEFT_MC2, OUTPUT);

    // Init with stopped engines
    brake("left");
    brake("right");

    Serial.begin(9600);
}

void loop()
{
    // Read photoresistors
    int left_light = analogRead(LEFT_LIGHT_SENSOR);
    int right_light = analogRead(RIGHT_LIGHT_SENSOR);

    // Little pause to let serial port output
    delay(50);
    // To turn left, we have to accelerate right engine
    Serial.print("Right: ");
    Serial.print(right_light);
    Serial.print(" ");
    if (right_light >= LIGHT_THRESHOLD_MIN) {
        int left_speed = map(right_light, LIGHT_THRESHOLD_MIN, LIGHT_THRESHOLD_MAX, SPEED_MIN, SPEED_MAX);
        left_speed = constrain(left_speed, SPEED_MIN, SPEED_MAX);
        Serial.print(left_speed);
        forward("left", left_speed);
    } else {
        Serial.print("0");
        brake("left"); // If light is below minimal - brake left engine
    }

    // To turn right, we have to accelerate left engine
    Serial.print("\tLeft: ");
    Serial.print(left_light);
    Serial.print(" ");
    if (left_light >= LIGHT_THRESHOLD_MIN) {
        int right_speed = map(left_light, LIGHT_THRESHOLD_MIN, LIGHT_THRESHOLD_MAX, SPEED_MIN, SPEED_MAX);
        right_speed = constrain(right_speed, SPEED_MIN, SPEED_MAX);
        Serial.println(right_speed);
        forward("right", right_speed);
    } else {
        Serial.println("0");
        brake("right");
    }
}

/**
 * Function to move forward with given speed (0-255)
 */
void forward(String motor, int rate) {
    if (motor == "left") {
        digitalWrite(LEFT_EN, LOW);
        digitalWrite(LEFT_MC1, HIGH);
        digitalWrite(LEFT_MC2, LOW);
        analogWrite(LEFT_EN, rate);
    } else {
        digitalWrite(RIGHT_EN, LOW);
        digitalWrite(RIGHT_MC1, HIGH);
        digitalWrite(RIGHT_MC2, LOW);
        analogWrite(RIGHT_EN, rate);
    }
}

/**
 * Function to brake engine
 */
void brake(String motor) {
    if (motor == "left") {
        digitalWrite(LEFT_EN, LOW);
        digitalWrite(LEFT_MC1, LOW);
        digitalWrite(LEFT_MC2, LOW);
        digitalWrite(LEFT_EN, HIGH);
    } else {
        digitalWrite(RIGHT_EN, LOW);
        digitalWrite(RIGHT_MC1, LOW);
        digitalWrite(RIGHT_MC2, LOW);
        digitalWrite(RIGHT_EN, HIGH);
    }
}