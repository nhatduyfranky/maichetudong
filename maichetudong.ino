

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

const int sensorMin = 0;
// min analog input: 
const int sensorMax = 1024;

const int congtachanhtrinh1 = 5;  // Dây ra công tăc hành trình dây màu xanh nối chân 5
const int congtachanhtrinh2 = 6;  // Dây ra công tăc hành trình dây màu xanh nối chân 6
int giatri1 = 0;
int giatri2 = 0;
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  pinMode(congtachanhtrinh1, INPUT);
  pinMode(congtachanhtrinh2, INPUT);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  myMotor->run(BACKWARD);
  myMotor->run(RELEASE);
  
  
}
void loop() {
  uint8_t i;

  giatri1 = digitalRead(congtachanhtrinh1);
  giatri2 = digitalRead(congtachanhtrinh2);

    
  // doc ngo vao tuan tu 
  int sensorReading = analogRead(A0); 
  // map gia tri vào khoang analog: 
  // ex: 'long int map(long int, long int, long int, long int, long int)' 
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3); 
  // range value: 
  switch (range) { 
    case 1:
    if (giatri1 == 0 && giatri2 == 1){
      Serial.println("Troi mua");
      Serial.println("Mai che bat dau duoc dua ra");
      myMotor->run(FORWARD);
        myMotor->setSpeed(200);  
        delay(200);
        }
     else {
      if (giatri1 == 1 && giatri2 == 1){
      Serial.println("Mai che dang duoc dua ra");
      myMotor->run(FORWARD);
        myMotor->setSpeed(200);    
         delay(200);
          }
       else {
        if (giatri1 == 1 && giatri2 == 0){
          myMotor->run(RELEASE);
          Serial.println("Mai che da duoc dua ra");
          delay(500);
           }
         }
       }
       break;
    case 2: 
    if (giatri2 == 0 && giatri1 == 1 ) {
        Serial.println("Troi nang");
        Serial.println("Mai che bat dau thu vao");
        myMotor->run(BACKWARD);
             myMotor->setSpeed(200);
             delay(200);   
        }
        else {
        if (giatri2 == 1 && giatri1 == 1) {
          Serial.println("Mai che dang duoc thu vao");
        myMotor->run(BACKWARD);
             myMotor->setSpeed(200); 
             delay(200);  
          }
         else {
        if (giatri1 == 0 && giatri2 == 1){
          myMotor->run(RELEASE);
          Serial.println("Mai che da duoc thu vao");
           delay(1000); 
           }
          }
        }
      }
  }
