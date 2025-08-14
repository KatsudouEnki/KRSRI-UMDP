/* COMMANDS LIST
1.  default_state()
2.  walk_fast() .
3.  walk_fast_obstacle() .
4.  walk_fast_balls()
5.  reverse_fast() .
6.  turn_left_slow() 
7.  turn_left_fast() .
8.  turn_left_obstacle() 
9.  turn_right_slow()
10. turn_right_fast() .
11. turn_right_obstacle()
12. crabwalk_left() .
13. crabwalk_left_obstacle() crabwalkLeftObstacle
14. crabwalk_right() .
15. crabwalk_right_obstacle()
16. cam_state()
17. walk_to_victim()
18. pre_ladder()
19. pre_ladder_right()
20. pre_ladder_left()
21. ladder()
22. ladder_right()
23. ladder_left()
24. post_ladder()
reverse_fast_obstacle() .
*/

void loop(){
  boot_state();
//  randomSeed(analogRead(A0));/
  
  display.clearDisplay();
  delay(500);
  
  servo_movement("angkat", 0);
  
  servo_movement("putar", 0);
  default_state();
  delay(500);
  default_state();
  unsigned long timer=millis();
  int start_state;
  speed=800;
  delay(500);
  
  while(true){//untuk pameran
    Serial.println(digitalRead(A10));
    if(digitalRead(A10) == HIGH){
      servo_movement("buka", 1);
      delay(200);
      // servo_movement("angkat", 2);
      servo_movement("angkat", 1);
      
      delay(100);
      speed=200;
      int status_korban=0, rep=0;
      while(status_korban==0){
        if (Serial2.available()) {
          if (buff_serial.length() > 16) {
            buff_serial = "";
          }
          
          String rx_in, dtx, dty, dstate;
          char chrx_in = Serial2.read();
          buff_serial += String(chrx_in);
          // check header
          int pos_head = buff_serial.indexOf(STX);
          int pos_tail = buff_serial.indexOf(ETX);
          // Serial.printf("%d -- %d\n", pos_head, pos_tail);
          if ((pos_head > -1) && (pos_tail > -1)) {
            if (pos_head < pos_tail) {
              rx_in = buff_serial.substring(pos_head + 1, pos_tail);
              Serial.println(rx_in);
              dstate = get_value(rx_in,',',0);
              Serial.print("Status = "); Serial.println(dstate);
              
              display.setCursor(10,10);
              display.print(dstate);
              display.display();
      
              dtx = get_value(rx_in,',',1);
              Serial.print("dtx = "); Serial.println(dtx);
              dty = get_value(rx_in,',',2);
    
              Serial.print("dty = "); Serial.println(dty);
              if(dtx.toInt()>=-70 && dtx.toInt()<=70 && dstate.toInt()==1){
                servo_movement("buka",1);
                walk_to_victim();
    
                distance_detection();
                if(dty.toInt()>=300){
                  servo_movement("angkat", 1);
                  
                  delay(200);
                  servo_movement("angkat", 3);
                  walk_to_victim();
                  walk_to_victim();
                  delay(800);
                  servo_movement("buka", 2); 
                  delay(250);
                  speed=100;
                  servoAngkat.write(150);
                  delay(100);
                  servo_movement("buka", 2);
                  delay(100);
                  reverse_fast();
                  delay(100);
                  servo_movement("buka", 2);
                  delay(600);
                  servo_movement("angkat", 0);
                  status_korban=1;
                } 
                
                myservo.write(pos);
                Serial.print("pos = "); Serial.println(pos);
              }
              else if(dtx.toInt()<=-70 && dstate.toInt()==1){
                servo_movement("buka",1);
                pos=pos-1;
                 if(pos<=82){
                   turn_left_slow();
                   pos = 92;
                 }
                myservo.write(pos);
                } 
              else if(dtx.toInt()>=70 && dstate.toInt()==1){
                servo_movement("buka",1);
                pos=pos+1;
                 if(pos>=122){
                   turn_right_slow();
                   pos=112;
                 }
                myservo.write(pos);
              }
              else{
                pos=pos+1;
                if(pos>=122){
                  pos=82;
                  rep++;
                  if(rep>5){
                    status_korban=1;
                  }
                }
                Serial.println(myservo.read());
                myservo.write(pos);
              }
              delay(10);
              //////////////////////////////////////////////////////////////////// pakai sensor jarak atau koordinat Y dari kamera
              buff_serial = "";
              
            }
          }
        }
        else{
          Serial.println("Tidak ada Input dari RASPI");
        }
      }
      delay(1000);
    }
    else{
      default_state();
      Serial.println("State Default");
      delay(500);
    }
  }
  
  digitalWrite(7, LOW);
  default_state();


}


void randomSequence(){
  int rand_val = random(1,10);
  default_state();
  for(int i=0;i<4;i++){
    switch(rand_val){
      case 1:
        walk_fast();
        break;
      case 2:
        reverse_fast();
        break;
      case 3:
        turn_left_fast();
        break;
      case 4:
        turn_right_fast();
        break;
      case 5:
        crabwalk_left();
        break;
      case 6:
        crabwalk_right();
        break;
      case 7:
      case 8:
        myservo.write(82);
        delay(100);
        myservo.write(122);
        delay(100);
        myservo.write(102);
        delay(50);
        break;
      case 9:
        servo_movement("buka",1);
        servo_movement("angkat", 1);
        delay(200);
        servo_movement("angkat", 2);
        delay(200);
        servo_movement("buka", 2);
        delay(350);
        speed=100;
        servoAngkat.write(150);
        delay(400);
        servo_movement("buka",0);
        servo_movement("angkat", 0);
        delay(500);
        break;
    }
    if(rand_val == 9){
      break;
    }
  }
  delay(100);
  speed=800;
  default_state();
  delay(5000);
}
