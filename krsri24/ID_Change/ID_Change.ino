#include <DynamixelSerial.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Dynamixel.setSerial(&Serial3);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  delay(2000);

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  delay(500);
//  Dynamixel.setID(ID_lama, ID_baru);
//   Dynamixel.setID(1,15);
  
  digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int id =15;
  for(id=0; id<40;id++){
    Serial.println(id);
    Dynamixel.moveSpeed(id, 475,200);
    delay(500);
    Dynamixel.moveSpeed(id,625,200);
    delay(500);
  }
}
