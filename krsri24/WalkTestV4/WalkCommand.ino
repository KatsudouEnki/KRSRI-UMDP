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

  speed = 100;
  
//  obstacle_kelereng();
//  digitalWrite(7,HIGH);
//  transisi_r5_r6();
  // home();
  // obstacle_puing1();
  // obstacle_miring();
  // obstacle_kelereng();
  // transisi_r5_r6();
  // while(true){
//    compass();
//    distance_detection();
//    data_display();



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
  while(false){
    // LeftMid(8,8,5,speed,servo_delay);
    // RightMid(8,8,5,speed,servo_delay);
    // delay(100);
    // LeftMid(7,7,5,speed,servo_delay);
    // RightMid(9,9,5,speed,servo_delay);
    // delay(100);
    // LeftMid(6,6,5,speed,servo_delay);
    // RightMid(10,10,5,speed,servo_delay);
    // delay(100);
    // LeftMid(5,5,5,speed,servo_delay);
    // RightMid(11,11,5,speed,servo_delay);
    // delay(100);
    // LeftMid(6,6,5,speed,servo_delay);
    // RightMid(10,10,5,speed,servo_delay);
    // delay(100);
    // LeftMid(7,7,5,speed,servo_delay);
    // RightMid(9,9,5,speed,servo_delay);
    // delay(100);
  // LeftFront(9,4,3,speed,servo_delay);
  // delay(400);
  // LeftFront(9,8,3,speed,servo_delay);
  // delay(400);
  // LeftFront(9,8,6.5,speed,servo_delay);
  // delay(400);
  // RightFront(9,4,3,speed,servo_delay);
  // delay(400);
  // RightFront(9,8,3,speed,servo_delay);
  // delay(400);
  // RightFront(9,8,6.5,speed,servo_delay);
  // delay(400);

  // LeftMid(6.5,9.5,3.5,speed,servo_delay);
  // RightMid(6.5,9.5,3.5,speed,servo_delay);
  // delay(400);
  // LeftMid(4.5,12,3.5,speed,servo_delay);
  // RightMid(4.5,12,3.5,speed,servo_delay);
  // delay(400);
  // LeftMid(4.5,12,7,speed,servo_delay);
  // RightMid(4.5,12,7,speed,servo_delay);
  // delay(400);

  // LeftBack(10.5,9,3.5,speed,servo_delay);
  // delay(400);
  // LeftBack(5,11,3.5,speed,servo_delay);
  // delay(400);
  // LeftBack(5,11,7,speed,servo_delay);
  // delay(400);
  // RightBack(10.5,9,3.5,speed,servo_delay);
  // delay(400);
  // RightBack(5,11,3.5,speed,servo_delay);
  // delay(400);
  // RightBack(5,11,7,speed,servo_delay);
  // delay(400);

  // LeftFront(9,4,6.5,speed,servo_delay);
  // RightFront(9,4,6.5,speed,servo_delay);
  
  // LeftMid(6.5,9.5,7,speed,servo_delay);
  // RightMid(6.5,9.5,7,speed,servo_delay);

  // LeftBack(10.5,9,7,speed,servo_delay);
  // RightBack(10.5,9,7,speed,servo_delay);

  // delay(1000);
  /////////////////////////
  /**/
  LeftFront(9,4,3,speed,servo_delay);//angkat
  RightBack(10.5,9,3.5,speed,servo_delay);//angkat

  RightFront(9,8,6.5,speed,servo_delay);//turun
  LeftBack(5,11,7,speed,servo_delay);//turun
  delay(500);
  

  LeftFront(9,8,3,speed,servo_delay);//maju
  RightBack(5,11,3.5,speed,servo_delay);//maju

  RightFront(9,4,5.5,speed,servo_delay);//tarik
  LeftBack(10.5,9,8,speed,servo_delay);//tarik

  LeftMid(7.5,8.5,6,speed,servo_delay);//tarik
  RightMid(7.5,8.5,6,speed,servo_delay);//tarik
  
  delay(500);
  LeftFront(9,8,6.5,speed,servo_delay);//turun
  RightBack(5,11,7,speed,servo_delay);//
  
  RightFront(9,4,3,speed,servo_delay);//angkat
  LeftBack(10.5,9,3.5,speed,servo_delay);//angkat
  delay(500);
  //LFRB tancap tanah

  LeftFront(9,4,5.5,speed,servo_delay);//tarik
  RightBack(10.5,9,8,speed,servo_delay);//tarik

  RightFront(9,8,3,speed,servo_delay);//maju
  LeftBack(5,11,3.5,speed,servo_delay);//maju

  LeftMid(8.5,7.5,7,speed,servo_delay);//tarik
  RightMid(8.5,7.5,7,speed,servo_delay);//tarik
  delay(500);

  LeftMid(8.5,7.5,3.5,speed,servo_delay);//angkat
  RightMid(8.5,7.5,3.5,speed,servo_delay);//angkat
  delay(500);

  LeftMid(6.5,9.5,3.5,speed,servo_delay);//angkat
  RightMid(6.5,9.5,3.5,speed,servo_delay);//angkat
  delay(500);
  LeftMid(6.5,9.5,5,speed,servo_delay);//turun
  RightMid(6.5,9.5,5,speed,servo_delay);//turun
  delay(500);
  /**/
  /////////////////////////
  // LeftFront(9,4,3,speed,servo_delay);
  // RightBack(10.5,9,3.5,speed,servo_delay);
  // delay(800);
  // //LFRB naik
  // RightFront(9,4,6.5,speed,servo_delay);
  // LeftBack(10.5,9,7,speed,servo_delay);
  // //RFLB geser default
  // LeftMid(5.5,10.5,7,speed,servo_delay);
  // RightMid(5.5,10.5,7,speed,servo_delay);
  // delay(800);
  // //Mid geser 1

  // LeftFront(9,8,3,speed,servo_delay);
  // RightBack(5,11,3.5,speed,servo_delay);
  // delay(400);
  // LeftFront(9,8,6.5,speed,servo_delay);
  // RightBack(5,11,7,speed,servo_delay);
  // delay(400);
  // //LFRB tancap tanah

  // RightFront(9,4,3,speed,servo_delay);
  // LeftBack(10.5,9,3.5,speed,servo_delay);
  // // delay(800);
  // //RFLB naik
  // LeftFront(9,4,6.5,speed,servo_delay);
  // RightBack(10.5,9,7,speed,servo_delay);
  // //LFRB geser default
  // LeftMid(6.5,9.5,7,speed,servo_delay);
  // RightMid(6.5,9.5,7,speed,servo_delay);
  // delay(800);
  // //Mid geser 2

  // RightFront(9,8,3,speed,servo_delay);
  // LeftBack(5,11,3.5,speed,servo_delay);
  // delay(400);
  // RightFront(9,8,6.5,speed,servo_delay);
  // LeftBack(5,11,7,speed,servo_delay);
  // delay(400);
  // //RFLB tancap tanah



  

  // delay(500);

  }
  digitalWrite(7, LOW);
  default_state();


}
