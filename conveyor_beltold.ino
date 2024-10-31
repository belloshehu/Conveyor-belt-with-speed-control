#include <LiquidCrystal_I2C.h>
// Include the Arduino Stepper Library
#include <Stepper.h>

LiquidCrystal_I2C lcd(0x27,  16, 2);
// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 6, 7, 8, 9);
unsigned long timeDelay = 1500, lastTime = 0;
const unsigned short MAX_SPEED = 3000;
const int speedPotPin  = A1;  // pin connected to potentiometer for speed control
byte speed = 100; // we are setting speed 0-3000 inpercentage

void setup()
{
  Serial.begin(9600);
  lcd.init();    // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Conveyor Belt");
  lcd.setCursor(0, 1);
  lcd.print("System ....");
  delay(3000);
  lcd.clear();
  //speed = analogRead(speedPotPin);
  //speed = map(speed, 0, 1023, 0, MAX_SPEED);
  myStepper.setSpeed(speed * MAX_SPEED /100);
}


void loop()
{
  myStepper.step(stepsPerRevolution);
  readBluetooth();
  if(millis() - lastTime >= timeDelay){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed:");
    lcd.setCursor(7, 0);
    lcd.print(speed);
    lcd.setCursor(13, 0);
    lcd.print("%");
    lastTime = millis();
  }
}

void readBluetooth(){
  if(Serial.available()> 0){
    speed = Serial.readString().toInt();
    lcd.setCursor(0, 1);
    lcd.print("New speed: ");
    lcd.setCursor(11, 1);
    lcd.print(speed);
    lcd.setCursor(15, 1);
    lcd.print("%");
    delay(1500);
    Serial.flush();
    myStepper.setSpeed(speed * MAX_SPEED / 100);
  }
}