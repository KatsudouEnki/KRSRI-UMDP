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
13. crabwalk_left_obstacle() crabwalkLeftObstacle
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
  boot_state();
//  digitalWrite(9, 1);
  while(0){
    for(pos=100; pos<=122;pos++){
      myservo.write(pos);
      delay(25);
    }
    for(pos=122; pos>=82;pos--){
      myservo.write(pos); 
      delay(25);
    }
    for(pos=82; pos<=100;pos++){
      myservo.write(pos);
      delay(25);
    }
//    obstacle_kelereng_w_korban();
  }
//  preparation();
  display.clearDisplay();
  delay(500);
  
  servo_movement("angkat", 0);
  
  servo_movement("putar", 0);
  delay(500);
  default_state();
  unsigned long timer=millis();
  int start_state;
  speed=800;
  
  while(false){
    reverse_fast_obstacle();
  }

  while(true){
//    Serial.println(start_state);
    
//    if(1){
    if(digitalRead(A10) == HIGH){
      digitalWrite(9, HIGH);
      digitalWrite(11, LOW);
      Serial.println("start");
      /* */
//      home();
//      digitalWrite(7,LOW);
//      korban1();
//      servo_movement("buka", 1);
//      delay(200);
//      // servo_movement("angkat", 2);
//      servo_movement("angkat", 1);
//      delay(2000);
//      dummy_detection();
//      speed=800;
//      servo_movement("angkat", 0);
//      servo_movement("putar", 0);
//      servo_movement("buka", 2);
//      obstacle_puing1();
//      obstacle_miring();
//      /* */
//      obstacle_batu1();
//      safe_zone1();
//      obstacle_kelereng_w_korban();
//      safe_zone2();
//      transisi_r5_r6();
//      obstacle_puing2();
//      obstacle_batu2_ver2();
//      obstacle_tangga2();
//      korban5();
      r10();
      while(true);
    }
    else{
      unsigned long now=millis();
      default_state();
      
      servo_movement("putar", 0);
      if(now - timer>750){
        digitalWrite(11, !digitalRead(11));
        delay(50);
        digitalWrite(11, !digitalRead(11));
        delay(50);
        digitalWrite(11, !digitalRead(11));
        delay(50);
        digitalWrite(11, !digitalRead(11));
        delay(50);
        
        compass();
        distance_detection();
//       data_display();

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

  //testing
  while(true){
    
    home();
    korban1();
    speed=800;
    obstacle_puing1();
    obstacle_miring();
    obstacle_batu1();
//    safe_zone1();
//    obstacle_kelereng_w_korban();
//    safe_zone2();
//    transisi_r5_r6();
//    obstacle_puing2();
    while(1);
    obstacle_batu2();
    obstacle_tangga();
  }
  
  digitalWrite(7, LOW);
  default_state();


}
