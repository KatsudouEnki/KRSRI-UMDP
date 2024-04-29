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
  // while(true){
  //   Serial.println(digitalRead(11));
  // }

  preparation();
  display.clearDisplay();
  servoAngkat.write(0);
  delay(5000);

  speed = 150;

//  obstacle_kelereng();
//  digitalWrite(7,HIGH);
//  transisi_r5_r6();
//  while(true){
////    compass();
//    distance_detection();
//    data_display();
  
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
