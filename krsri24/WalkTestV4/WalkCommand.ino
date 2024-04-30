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
  
  while(true){
    ladder_right();
  }
  
  digitalWrite(7, LOW);
  default_state();


}
