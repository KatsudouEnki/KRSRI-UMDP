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

  speed = 400;

  obstacle_kelereng();
  digitalWrite(7,HIGH);
  transisi_r5_r6();
  while(true){
//    compass();
    distance_detection();
    data_display();
  }
  while(true){
  LeftFront(8,6,2,speed,servo_delay);
  RightFront(8,6,2,speed,servo_delay);
  delay(400);
  LeftFront(8,10,2,speed,servo_delay);
  RightFront(8,10,2,speed,servo_delay);
  delay(400);
  LeftFront(8,10,6.5,speed,servo_delay);
  RightFront(8,10,6.5,speed,servo_delay);
  delay(400);
  



  }
  digitalWrite(7, LOW);
  default_state();


}
