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
  myservo.write(90);
  servoAngkat.write(90);
  default_state();
  delay(1000);
  int tes=0;
  while(true){
//    default_state();
//  crabwalk_right_obstacle();
//    low_walk();
    distance_detection();
    data_display();
    delay(50);
    // compass();
//    if(angle8<100){
//      
//    }
  }
//  for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
//  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
//
//  for (int a = 20; a <= 90; a += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    servoAngkat.write(a);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }
//  for (int a = 90; a >= 20; a -= 1) { // goes from 180 degrees to 0 degrees
//    servoAngkat.write(a);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15 ms for the servo to reach the position
//  }

  //cek ultrasonik
  // for(float i=4.5;i>=2;i-=0.5){
  //  RightMid(8,8,i,speed,servo_delay);
  //  delay(2000);
  // }
}
