/*********
  HipMonsters.com
  
  See more at www.HipMonsters.com
  Simple Arduino controller for a solenoid to move a robot's leg 
  2024
*********/

// The variable storing what state the relay for the solenoid is currently in.
volatile byte solenoidSate = LOW;

// The pin for the relay that controls the solenoid.
int solenoidRelayPin = 8;

//The last time the leg moved forward.
long legMovementTime = 0;

// Defines how ow long the leg should move forward.
long legMovementLength = 10000;

// This runs when the Aruino boots up.
void setup() {

  // Let the Arduino know it can write out to the pin for the relay.
  pinMode(solenoidPin, OUTPUT);

  // Sets the relay to LOW (off).
  digitalWrite(solenoidPin, LOW);

  // Sets the last time the leg moved to right now.
  legMovementTime = millis();

  //Tells the Arduino to listen to the text port so we can send commands to it.
  Serial.begin(9600);

  //Writes to the serial port.
  Serial.println("ACTIVE!");
}

// This is the loop that continuously runs to send commands to the pin.
void loop() {

  // Here is where we define how the Arduino makes the legs move between left and right
  // The flow control logic here says: If enough time has passed and the left leg was moved last time move the right leg
  if ((millis() - legMovementTime) > legMovementLength && solenoidSate == HIGH) {

    digitalWrite(solenoidPin, LOW);
    solenoidSate = LOW;
    Serial.println("OFF");
    legMovementTime = millis();

    // The flow control logic here says: If enough time has passed and the right leg was moved last time move the left leg
  } else if ((millis() - legMovementTime) > legMovementLength && solenoidSate == LOW) {

    digitalWrite(solenoidPin, HIGH);
    solenoidSate = HIGH;
    Serial.println("ON");
    legMovementTime = millis();
  }

  // Tells the loop to pause for 50 microseconds.
  delay(50);
}

// Happy coding!
