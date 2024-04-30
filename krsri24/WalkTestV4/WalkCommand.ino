/* COMMANDS LIST
1.  default_state()
2.  walk_fast()
3.  walk_fast_obstacle()
4.  walk_fast_balls()
5.  reverse_fast()
6.  turn_left_slow()
7.  turn_left_fast()
8.  turn_left_obstacle()
9.  turn_right_slow()
10. turn_right_fast()
11. turn_right_obstacle()
12. crabwalk_left()
13. crabwalk_left_obstacle()
14. crabwalk_right()
15. crabwalk_right_obstacle()
16. cam_state()
17. walk_to_victim()
*/

void loop(){
  
  preparation();
  display.clearDisplay();
  servoAngkat.write(0);
  delay(2000);

  unsigned long timer=millis();
  
//  obstacle_kelereng();
//  digitalWrite(7,HIGH);
//  transisi_r5_r6();
  while(true){
    
    if(digitalRead(11)==HIGH){
      digitalWrite(7,LOW);
      home();
      digitalWrite(7,!digitalRead(7));
      obstacle_puing1();
      digitalWrite(7,!digitalRead(7));
      obstacle_miring();
      digitalWrite(7,!digitalRead(7));
      obstacle_kelereng();
      digitalWrite(7,!digitalRead(7));
      transisi_r5_r6();
      digitalWrite(7,!digitalRead(7));
      obstacle_puing2();
      digitalWrite(7,!digitalRead(7));
      while(true){
        compass();
        distance_detection();
        if(roll > -17){
          pre_ladder();
        }else{
          ladder();
        }
      }
    }
    else{
      unsigned long now=millis();
      if(now - timer>750){
        digitalWrite(7,!digitalRead(7));
        delay(250);
        timer=now;
      }
    }
  }
//  // while(true){
////    compass();
////    distance_detection();
////    data_display();
//  digitalWrite(7,HIGH);
//  obstacle_batu2();
//  
  
  while(true){
    compass();
    distance_detection();
    if(roll >= -17){
      pre_ladder();
    }else{
      ladder();
    }
  }
  
  while(false){
  LeftMid(7,9,4.5,speed,servo_delay);
  RightMid(7,9,4.5,speed,servo_delay);

  LeftBack(11.5,5.5,7.75,speed,servo_delay);
  RightBack(11.5,5.5,7.5,speed,servo_delay);
  
  LeftFront(6,6,2.25,speed,servo_delay);
  RightFront(6,6,2.25,speed,servo_delay);
  delay(2000);
  LeftFront(6,6,1.5,speed,servo_delay);
  //RightFront(6,6,1.5,speed,servo_delay);
  delay(2000);
  LeftFront(8,8,1.5,speed,servo_delay);
  //RightFront(6,6,1.5,speed,servo_delay);
  delay(2000);
  }
  // LeftMid(7,9,4.5,speed,servo_delay);
  // RightMid(7,9,4.5,speed,servo_delay);

  // LeftBack(11.5,5.5,7.75,speed,servo_delay);
  // RightBack(11.5,5.5,7.5,speed,servo_delay);

  while(true){
  LeftMid(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);

  LeftBack(11,3.5,7.5,speed,servo_delay);
  RightBack(11,3.5,7.5,speed,servo_delay);

  LeftFront(4.2,13.2,3.25,speed,servo_delay);
  RightFront(4.2,13.2,3.25,speed,servo_delay);

  delay(3000);

  LeftBack(14.3,4.55,7.5,speed,servo_delay);
  RightBack(14.3,4.55,7.5,speed,servo_delay);

  LeftFront(2.45,7.7,3.25,speed,servo_delay);
  RightFront(2.45,7.7,3.25,speed,servo_delay);

  delay(3000);

  LeftBack(14.3,4.55,6,speed,servo_delay);
  RightBack(14.3,4.55,6,speed,servo_delay);

  LeftFront(2.45,7.7,1.75,speed,servo_delay);
  RightFront(2.45,7.7,1.75,speed,servo_delay);

  delay(3000);

  LeftBack(11,3.5,6,speed,servo_delay);
  RightBack(11,3.5,6,speed,servo_delay);

  LeftFront(4.2,13.2,1.75,speed,servo_delay);
  RightFront(4.2,13.2,1.75,speed,servo_delay);

  delay(3000);
  }
    // while(true){ladder();}
  while(true){
    LeftFront(4.55,14.3,3.25,speed,servo_delay);
    RightFront(4.55,14.3,3.25,speed,servo_delay);
    LeftMid(6,10,5.5,speed,servo_delay);
    RightMid(6,10,5.5,speed,servo_delay);
    LeftBack(9.9,3.15,7.5,speed,servo_delay);
    RightBack(9.9,3.15,7.5,speed,servo_delay);
    delay(500);
    
    LeftFront(2.8,8.8,3.25,speed,servo_delay);
    RightFront(2.8,8.8,3.25,speed,servo_delay);
    LeftMid(10,6,5.5,speed,servo_delay);
    RightMid(10,6,5.5,speed,servo_delay);
    LeftBack(14.3,4.55,7.5,speed,servo_delay);
    RightBack(14.3,4.55,7.5,speed,servo_delay);
    delay(750);
    
    LeftFront(2.8,8.8,0.6,speed,servo_delay);
    RightBack(14.3,4.55,5,speed,servo_delay);
    delay(100);
    LeftFront(3.15,9.9,0.6,speed,servo_delay);
    delay(150);
    LeftFront(3.5,11,0.6,speed,servo_delay);
    delay(150);
    LeftFront(3.85,12.1,0.6,speed,servo_delay);
    RightBack(11,3.5,5,speed,servo_delay);
    delay(150);
    LeftFront(4.2,13.2,0.6,speed,servo_delay);
    delay(150);
    LeftFront(4.55,14.3,0.6,speed,servo_delay);
    delay(150);
    LeftFront(4.9,15.4,0.6,speed,servo_delay);
    RightBack(9.9,3.15,5,speed,servo_delay);
    delay(150);
    LeftFront(4.55,14.3,3.25,speed,servo_delay);
    RightBack(9.9,3.15,7.5,speed,servo_delay);
    delay(400);
    
    RightFront(2.8,8.8,0.6,speed,servo_delay);
    LeftBack(14.3,4.55,5,speed,servo_delay);
    delay(100);
    RightFront(3.15,9.9,0.6,speed,servo_delay);
    delay(150);
    RightFront(3.5,11,0.6,speed,servo_delay);
    delay(150);
    RightFront(3.85,12.1,0.6,speed,servo_delay);
    LeftBack(11,3.5,5,speed,servo_delay);
    delay(150);
    RightFront(4.2,13.2,0.6,speed,servo_delay);
    delay(150);
    RightFront(4.55,14.3,0.6,speed,servo_delay);
    delay(150);
    RightFront(4.9,15.4,0.6,speed,servo_delay);
    LeftBack(9.9,3.15,5,speed,servo_delay);
    delay(150);
    RightFront(4.55,14.3,3.25,speed,servo_delay);
    LeftBack(9.9,3.15,7.5,speed,servo_delay);
    delay(400);
    
    LeftMid(10,6,3.5,speed,servo_delay);
    RightMid(10,6,3.5,speed,servo_delay);
    delay(200);
    LeftMid(6,10,3.5,speed,servo_delay);
    RightMid(6,10,3.5,speed,servo_delay);
    delay(200);
    LeftMid(6,10,5.5,speed,servo_delay);
    RightMid(6,10,5.5,speed,servo_delay);
    delay(200);

  }
  digitalWrite(7, LOW);
  default_state();


}
