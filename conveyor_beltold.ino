
#include <LiquidCrystal_I2C.h>
// Include the Arduino Stepper Library
#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 6, 7, 8, 9);

#define MAx_SPEED 3000
#define speedPotPin A1 // pin connected to potentiometer for speed control
byte speed = 60; // we are setting speed 0-3000
void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Conveyor Belt");
  lcd.setCursor(0,);
  lcd.print("System ....");
  delay(3000);
  lcd.clear();
  
  speed = analogRead(speedPotPin);
  speed = map(0, 1023, 0, MAX_SPEED);
}


void loop()
{
  lcd.setCurosr(0, 0);
  lcd.print("Speed:");
  lcd.cursor(7, 0);
  lcd.print(speed);
  speed = analogRead(speedPotPin);
  speed = map(0, 1023, 0, MAX_SPEED);
  myStepper.step(stepsPerRevolution);
}