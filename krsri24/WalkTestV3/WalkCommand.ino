/* COMMANDS LIST
1. default_state()                    //kembali ke posisi semula
2. walk()
3. walk_fast()                        //dipakai untuk jalan cepat biasa
4. walk_fast_obstacle()               //dipakai untuk jalan di reruntuhan
5. walk_fast_balls()                  //dipakai untuk jalan di kelereng
6. reverse()
7. reverse_fast()                     //dipakai untuk balik biasa
8. turn_left_obstacle()               //dipakai untuk putar kiri di reruntuhan
9. turn_left_fast()                   //dipakai untuk putar kiri cepat
10. turn_right_obstacle()             //dipakai untuk putar kanan di reruntuhan
11. turn_right_fast()                 //dipakai untuk putar kanan cepat
12. crabwalk_left()
13. crabwalk_left_fast()              //dipakai untuk geser kiri
14. crabwalk_right()
15. crabwalk_right_fast()             //dipakai untuk geser kanan
*/

void loop(){
  //tugas utk rabu, bikin crabwalk cepet
  myservo.write(90);
  servoAngkat.write(90);
  default_state();
//  delay(1000);
  int tes=0;
//  while(true);
  distance_detection();
//  data_display();
  if(front_dis>0 && front_dis<35){
    tes=1;
  }
  else{
    tes=0;
  }
  
  while(tes==0){
    walk_fast_obstacle();
    distance_detection();
//    data_display();
    if(front_dis>0 && front_dis<35){
      tes=1;
    }
    else{
      tes=0;
    }

//    if(left_dis>0 &&left_dis<=15){
//      crabwalk_right();
//    }
//
//    if(right_dis>0 && right_dis<=15){
//      crabwalk_left();
//    }

  }
  default_state();
//  }
  
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
