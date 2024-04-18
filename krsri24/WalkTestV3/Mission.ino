/* Mission List
1. preparation()
2. home()
3. korban1()
4. obstacle_puing1()
5. obstacle_miring()
*/

void preparation(){
  myservo.write(90);
  servoAngkat.write(90);
  servoBuka.write(15);
  default_state();
}

void home(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
  
    if(angle8<90){
      turn_right_fast();
    }
    else if(angle8>=90 && angle8<122){
      turn_right_slow();
    }
    else if(angle8>132 && angle8<=165){
      turn_left_slow();
    }
    else if(angle8>165){
      turn_left_fast();
    }
    else{
      walk_fast();
    }
    
    compass();
    distance_detection();

    if(back_dis>55 || back_dis==0){
      state=1;
      default_state();
    }
  }
  
}

void korban1(){
  pos=90;
  //<60 == putar kiri
  //>120 == putar kanan
  int state=0;
  servoAngkat.write(5);
  cam_state();
  while(true){
    dummy_detection();
//    Serial.print(dummy_state);
//    Serial.print(';');
//    Serial.print(dummy_x_coor);
//    Serial.print(';');
//    Serial.println(dummy_y_coor);
    
//    if(dummy_x_coor <= -70 && dummy_state==1){
//      digitalWrite(LED_BUILTIN,LOW);
//      pos=pos-1;
//      myservo.write(pos);
//    }
//    else if(dummy_x_coor >= 70 && dummy_state==1){
//      digitalWrite(LED_BUILTIN,LOW);
//      pos=pos+1;
//      myservo.write(pos);
//    }
//    else if(dummy_state==0){
//      digitalWrite(LED_BUILTIN,HIGH);
//      pos=pos+1;
//      if(pos>=180){
//        pos=0;
//      }
//      myservo.write(pos);
//    }
//    else{
//      digitalWrite(LED_BUILTIN,LOW);
//      servoBuka.write(90);
//      delay(2000);
//      servoBuka.write(0);
//      delay(2000);
////      state=1;
//      pos=pos;
//    }
//    if(dummy_x_coor >= -70 && dummy_x_coor <= 70 && dummy_state==1){
//      digitalWrite(LED_BUILTIN,LOW);
//      servoBuka.write(90);
//      delay(2000);
//      servoBuka.write(15);
//      delay(2000);
////      state=1;
//      pos=pos;
//    }
    delay(100);
  }
  
}

void obstacle_puing1(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    if (right_dis>20||right_dis==0){
      crabwalk_right();
    }
    else{
      state=1;
    }
  }

  
  state=0;
  while(state==0){
    compass();
    distance_detection();

    if(angle8<=150 && angle8>50){
      turn_left_obstacle();
    }
//    else if(angle8>=90 && angle8<122){
//      turn_right_slow();
//    }
//    else if(angle8>132 && angle8<=165){
//      turn_left_slow();
//    }
    else if(angle8>150 || angle8<15){
      turn_right_obstacle();
    }
    else{
      walk_fast_obstacle();
    }

    compass();
    distance_detection();
    if(roll<-7 || (front_dis<=20 && front_dis>0)){//the obstacle after this have roll value of -8 when default position
      state=1;
      default_state();
    }
  }
}

void obstacle_miring(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    
    if(angle8<90){
      turn_right_fast();
    }
    else if(angle8>=90 && angle8<122){
      turn_right_slow();
    }
    else if(angle8>132 && angle8<=165){
      turn_left_slow();
    }
    else if(angle8>165){
      turn_left_fast();
    }
    else{
      walk_fast();
    }
    compass();
    distance_detection();
    if(front_dis<30 &&front_dis>0){
      state=1;
      default_state();
    }
  }
}

void obstacle_kelereng(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    
    if(angle8>=35 && angle8<70){
      turn_right_slow();
    }
    else if(angle8<=70 && angle8<127){
      turn_right_fast();
    }
    else if(angle8>=185 && angle8<=220){
      turn_left_slow();
    }
    else if(angle8>=127 && angle8<=185){
      turn_left_fast();
    }
    else{
      walk_fast_balls();
    }


    compass();
    distance_detection();
//    if(back_dis
  }
}
