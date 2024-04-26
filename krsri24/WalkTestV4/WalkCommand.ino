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
  delay(5000);

  speed = 100;

//  obstacle_kelereng();
//  digitalWrite(7,HIGH);
//  transisi_r5_r6();
//  while(true){
////    compass();
//    distance_detection();
//    data_display();
  
  while(true){ladder();}
  // while(true){
  // LeftFront(8,6,2.5,speed,servo_delay);
  // delay(400);
  // LeftFront(8,10,2.5,speed,servo_delay);
  // delay(400);
  // LeftFront(8,10,7,speed,servo_delay);
  // delay(400);
  // RightFront(8,6,2.5,speed,servo_delay);
  // delay(400);
  // RightFront(8,10,2.5,speed,servo_delay);
  // delay(400);
  // RightFront(8,10,7,speed,servo_delay);
  // delay(400);

//  LeftMid(8,5,2.5,speed,servo_delay);
//  RightMid(8,5,2.5,speed,servo_delay);
//  delay(400);
//  LeftMid(5,8,2.5,speed,servo_delay);
//  RightMid(5,8,2.5,speed,servo_delay);
//  delay(400);
//  LeftMid(5,8,7,speed,servo_delay);
//  RightMid(5,8,7,speed,servo_delay);
//  delay(400);
//
//  LeftBack(10,8,2.5,speed,servo_delay);
//  RightBack(10,8,2.5,speed,servo_delay);
//  delay(400);
//  LeftBack(6,8,2.5,speed,servo_delay);
//  RightBack(6,8,2.5,speed,servo_delay);
//  delay(400);
//  LeftBack(6,8,7,speed,servo_delay);
//  RightBack(6,8,7,speed,servo_delay);
//  delay(400);
//
//  LeftFront(8,6,7,speed,servo_delay);
//  RightFront(8,6,7,speed,servo_delay);
//  
//  LeftMid(8,5,7,speed,servo_delay);
//  RightMid(8,5,7,speed,servo_delay);
//
//  LeftBack(10,8,7,speed,servo_delay);
//  RightBack(10,8,7,speed,servo_delay);
//
//  delay(500);

  digitalWrite(7, LOW);
  default_state();


}
