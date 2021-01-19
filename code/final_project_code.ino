/*
  LiquidCrystal Library - display() and noDisplay()

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD and uses the
  display() and noDisplay() functions to turn on and off
  the display.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay

*/

// include the library code:
#include <LiquidCrystal.h>
#include <dmtimer.h>

DMTimer myTimer(30000000); //Create a timer and specify its interval in microseconds 30 sec
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int sensorValue;
int tempsensorValue;
int volttempsensorValue;
int temperature;
int moistureValue;
int pump;
int switchState;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initiating ...");
  //begin serial
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, INPUT);
  digitalWrite(8, LOW);

}

void loop() {
  // determine state of switch
  switchState = digitalRead(10);
  Serial.print("Button: ");
  Serial.println(switchState);
  // turn light on manually from button
  if (switchState == HIGH)
  {
    digitalWrite(8, HIGH);
  }
  else if (switchState == LOW)
  {
    digitalWrite(8, LOW);
  }
  // Turn on the display:
  lcd.display();
  // Clear Display
  lcd.clear();
  // Read Value of photoresistor
  sensorValue = analogRead(A0);
  Serial.print("Light Sensor: ");
  Serial.println(sensorValue);
  // Print value of photoresistor
  lcd.println("Light Sensor:");
  lcd.println(sensorValue);
  delay(1000);
  // Read value of TMP Sensor
  tempsensorValue = analogRead(A1);
  float volttempsensorValue = (tempsensorValue / 1024.0) * 5.0;
  // output value of temp sensor to COM3
  Serial.print("tempsensevoltage: ");
  Serial.println(volttempsensorValue);
  // converting analog temp sensor to celsius
  float temperature = (volttempsensorValue - 0.5) * 100;
  // output to COM3
  Serial.print("Temp: " );
  Serial.print(temperature);
  lcd.clear();
  // output to LCD displaying temp
  lcd.print("Temperature: ");
  //lcd.setCursor(0, 1);
  lcd.println(temperature);
  lcd.print("C");
  delay(1000);
  // getting mositure value
  moistureValue = analogRead(A2);
  // output to COM3
  Serial.print("MoistureValue: ");
  Serial.println(moistureValue);
  float moisturePercent = -(moistureValue - 465);
  Serial.print("MoisturePercent: ");
  Serial.println(moisturePercent);
  lcd.clear();
  // output to LCD displaying moisture percentage
  lcd.print("Moisture: ");
  lcd.println(moisturePercent);
  delay(1000);


  // determing the range for watering
  if (moistureValue < 465)
  {
    digitalWrite(7, HIGH);
  }
  else
  {
    digitalWrite(7, LOW);
  }
  // Turns the light on and off based on the timer value
  // check if execution time has been reached
  if (myTimer.isTimeReached()) {
    //call what you need
    digitalWrite(8, HIGH);
    delay(10000);  // 10 seconds
    lcd.clear();
  }
  else {
    digitalWrite(8, LOW);
  }
}
