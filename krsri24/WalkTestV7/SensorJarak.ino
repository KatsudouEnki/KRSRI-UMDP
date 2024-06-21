void distance_detection(){
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!

  // print sensor one reading
//  Serial.print("1: ");
  if(measure1.RangeStatus != 4) {     // if not out of range
    left_dis = measure1.RangeMilliMeter;    
//    Serial.print(measure1.RangeMilliMeter);
//    Serial.print("measure1.RangeMilliMeter");    
  } else {
    left_dis = left_dis;
    Serial.print("Out of range");
  }
  
//  Serial.print(" ");

  // print sensor two reading
//  Serial.print("2: ");
  if(measure2.RangeStatus != 4) {
    right_dis = measure2.RangeMilliMeter;
//    Serial.print(sensor2);
//    Serial.print("mm");
  } else {
    right_dis=right_dis;
    Serial.print("Out of range");
  }

  
//  left_dis=sonar[2].ping_cm();
//  right_dis=sonar[3].ping_cm();
  front_dis=sonar[0].ping_cm();
  back_dis=sonar[1].ping_cm();
  // gripper_dis=sonar[4].ping_cm();
}



void setID() {///pas boot awal
  

  Serial.println("Both in reset mode...(pins are low)");
  
  
  Serial.println("Starting...");
  
  // all reset
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  delay(10);
  // all unreset
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS, true,true)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
}
