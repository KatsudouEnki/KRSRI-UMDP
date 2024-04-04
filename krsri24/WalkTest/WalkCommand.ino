/* COMMANDS LIST
1. default_state()
2. walk()
3. walk_fast()
4. walk_fast_obstacle()
5. walk_fast_balls()
5. reverse()
6. reverse_fast()
7. turn_left()
8. turn_left_fast()
9. turn_right()
10. turn_right_fast()
11. crabwalk_left()
12. crabwalk_right()
*/

void loop(){
  //tugas utk rabu, bikin crabwalk cepet

  //default_state1();
  for(int i=0;i<5;i++){
    low_walk();
    distance_detection();
    data_display();
    delay(20);
  }
  for (pos = 45; pos <= 135; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 135; pos >= 45; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

  //cek ultrasonik
  // for(float i=4.5;i>=2;i-=0.5){
  //  RightMid(8,8,i,speed,servo_delay);
  //  delay(2000);
  // }
}
