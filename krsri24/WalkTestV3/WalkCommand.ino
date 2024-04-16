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
*/

void loop(){
  //tugas utk rabu, bikin crabwalk cepet
  myservo.write(90);
  servoAngkat.write(90);
  servoBuka.write(15);
//  while(true){
//    
//    servoBuka.write(90);
//    delay(1000);
//    servoBuka.write(15);
//    delay(2000);
//    servoAngkat.write(80);
//    delay(3000);
//    servoAngkat.write(0);
//    delay(2000);
//  }
  default_state();
//  delay(1000);
  int tes=0;
  
  while(true){
    compass();
    if(angle8<55){
      turn_right_fast();
    }
    else if(angle8>=55 && angle8<117){
      turn_right_slow();
    }
    else if(angle8>137 && angle8<=200){
      turn_left_slow();
    }
    else if(angle8>200){
      turn_left_fast();
    }
    else{
      distance_detection();
      if(back_dis<=50 && back_dis>0){
        walk_fast();
      }
      else if(back_dis>50 || back_dis==0){
        walk_fast_obstacle();
      }

      distance_detection();
      if(front_dis<=20&& front_dis>0){
        delay(2000);
      }
      distance_detection();
      if(right_dis>20 || right_dis==0){
        crabwalk_right();
      }
    }
    
    
  }
  while(true){
    distance_detection();
    data_display();
    if(front_dis>0 && front_dis<20){
      tes=1; //stop
    }
    else{
      tes=0; //jalan
    }
    
    while(tes==0){
      
      distance_detection();
      data_display();
      
      if(front_dis>0 && front_dis<20 && (left_dis>20 || left_dis==0) && (right_dis>20 || right_dis==0)){
        tes=1;
      }
      else{
        walk_fast();
        tes=0;
      }
  
      if(left_dis>0 && left_dis<=20){
        crabwalk_right();
      }
  
      if(right_dis>0 && right_dis<=20){
        crabwalk_left();
      }
    }
  
    distance_detection();
    data_display();
    if((front_dis>0 && front_dis<=15) && (right_dis>0 && right_dis<=15)){
      for(int i=0;i<5;i++){
        turn_left_fast();
      }
    }

    distance_detection();
    data_display();
    if((front_dis>0 && front_dis<=15) && (left_dis>0 && left_dis<=15)){
      for(int i=0;i<4;i++){
        turn_right_fast();
      }
    }
    distance_detection();
    data_display();
    if((front_dis>0 && front_dis<=15) && (right_dis>0 && right_dis<=15)){
      for(int i=0;i<4;i++){
        turn_left_fast();
      }
    }

    distance_detection();
    data_display();
    
    if(front_dis>0 && front_dis<20){
      reverse_fast();
    }
    
    distance_detection();
    data_display();
    if(front_dis>0 && front_dis<20){
      tes=5;
    }
    if(tes==5){
      default_state();
      delay(10000);
    }
      distance_detection();
      data_display();
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

}
