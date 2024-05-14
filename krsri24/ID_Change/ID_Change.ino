#include <DynamixelSerial.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial3);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  delay(2000);

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  delay(500);
//  Dynamixel.setID(ID_lama, ID_baru);
   Dynamixel.setID(12,1);
  
  digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int id =17;
  for(id=0; id<20;id++){
    Serial.println(id);
  Dynamixel.moveSpeed(id, 800,500);
  delay(2000);
  Dynamixel.moveSpeed(id,900,500);
  delay(2000);
  }
}
