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
18. pre_ladder()
19. pre_ladder_right()
20. pre_ladder_left()
21. ladder()
22. ladder_right()
23. ladder_left()
24. post_ladder()
reverse_fast_obstacle()
*/

void loop(){
  Serial.println("Loop");
  
//  preparation();
  Serial.println("cl"); 
  display.clearDisplay();

  servo_movement("putar", 0);
//  delay(2000);
//  servo_movement("angkat", 0);
  delay(2000);
    Serial.println("go"); 
  unsigned long timer=millis();
  int start_state;
  while(false){
    Serial.println(start_state);
    
    if(digitalRead(46) == 1){
      digitalWrite(7,LOW);
      Serial.println("start");
      home();
      digitalWrite(7,LOW);
      korban1();
      servo_movement("buka", 1);
      delay(200);
      servo_movement("angkat", 2);
      dummy_detection();
      digitalWrite(7,!digitalRead(7));
      speed=800;
      servo_movement("angkat", 0);
      servo_movement("putar", 0);
      servo_movement("buka", 2);
      obstacle_puing1();
      digitalWrite(7,!digitalRead(7));
      obstacle_miring();
      digitalWrite(7,!digitalRead(7));
      obstacle_batu1();
      digitalWrite(7,!digitalRead(7));
      safe_zone1();
      digitalWrite(7,!digitalRead(7));
      obstacle_kelereng_w_korban();
      digitalWrite(7,!digitalRead(7));
      safe_zone2();
      digitalWrite(7,!digitalRead(7));
      transisi_r5_r6();
      digitalWrite(7,!digitalRead(7));
      obstacle_puing2();
      digitalWrite(7,!digitalRead(7));
      obstacle_batu2();
      digitalWrite(7,!digitalRead(7));
      obstacle_tangga();
      while(true);
    }
    else{
      unsigned long now=millis();
//      compass();
      default_state();
      
//      servo_movement("angkat",2);
//      ladder_stand(roll);
      servo_movement("putar", 0);
      delay(500);
      servo_movement("putar", 1);
      if(now - timer>750){
        digitalWrite(7,!digitalRead(7));
        distance_detection();
      //  data_display();

//        display.clearDisplay();
//        display.setCursor(50,0);
//        display.print("F=");
//        display.print(front_dis);
//        display.setCursor(0,32);
//        display.print("L=");
//        display.print(left_dis);
//        display.setCursor(90,32);
//        display.print("R=");
//        display.print(right_dis);
//        display.setCursor(50,50);
//        display.print("B=");
//        display.print(back_dis);
//        display.setCursor(40,32);
//        display.print("G=");
//        display.print(gripper_dis);
//        display.display();
        delay(100);
        timer=now;
      }
    }
  }
  Serial.println("standby");
  while(true){

//    default_state();
  Serial.println("go");
  servo_movement("putar", 0);
  servo_movement("angkat", 0);
  speed=300;
  walk_fast();
  Serial.println(servoBuka.read());
//  servoBuka.write(90);//buka
//  delay(1000);
  servoBuka.write(160);//tutup
  while(1);
    while(1){
    
    delay(1000);
    servoBuka.write(80);
    delay(1000);
    servoBuka.write(130);
    delay(4000);
  }
//    LeftFront(8,8,4.5,speed,servo_delay);
//    LeftMid(8,8,4.5,speed,servo_delay);
//  LeftBack(8,8,4.5,speed,servo_delay);
//    RightFront(8,8,4.5,speed,servo_delay);
//    RightMid(8,8,4.5,speed,servo_delay);
//  RightBack(8,8,4.5,speed,servo_delay);
//  default_state();
//  Dynamixel.moveSpeed(19,250, 500);
//  delay(500);
//  Dynamixel.moveSpeed(19,400, 50);
//  delay(3000);
  }
  
  digitalWrite(7, LOW);
  default_state();


}
