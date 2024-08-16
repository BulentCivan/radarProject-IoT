#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo servo_9;


int trigPin = 11;
int echoPin = 10;
long duration;
int distance;


void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  servo_9.attach(12, 500, 2500);
  lcd.init();
  lcd.backlight();
}

void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i = 15; i <= 165; i++) {  
    servo_9.write(i);
    delay(30);
    distance = 0.01723 * readUltrasonicDistance(trigPin, echoPin);
    // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    
    Serial.print(i); 
    // Sends the current degree into the Serial Port
    Serial.print(","); 
    // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); 
    // Sends the distance value into the Serial Port
    Serial.print("."); 
    // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    
    lcd.clear();        
    lcd.setCursor(0, 0);
    lcd.print("ANGLE :");
    lcd.print(i);
      
    lcd.setCursor(0, 1);
    lcd.print("DISTANCE :");
    lcd.print(distance);
    lcd.print("cm");
  }
  // Repeats the previous lines from 165 to 15 degrees
  for(int i = 165; i > 15; i--) {  
    servo_9.write(i);
    delay(30);
    distance = 0.01723 * readUltrasonicDistance(trigPin, echoPin);
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
      
    lcd.clear();        
    lcd.setCursor(0, 0);
    lcd.print("ANGLE :");
    lcd.print(i);
      
    lcd.setCursor(0, 1);
    lcd.print("DISTANCE :");
    lcd.print(distance);
    lcd.print("cm");
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
}
