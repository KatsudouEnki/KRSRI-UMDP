/* Mission List
1. preparation()
2. home()
3. korban1()
4. obstacle_puing1()
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

    if(back_dis>50 || back_dis==0){
      state=1;
      default_state();
    }
  }
}

void korban1(){
  
}

void obstacle_puing1(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();

    if(angle8<100){
      turn_right_obstacle();
    }
//    else if(angle8>=90 && angle8<122){
//      turn_right_slow();
//    }
//    else if(angle8>132 && angle8<=165){
//      turn_left_slow();
//    }
    else if(angle8>155){
      turn_left_obstacle();
    }
    else{
      walk_fast_obstacle();
    }

    compass();
    distance_detection();
    if(pitch>10){
      state=1;
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
    }
  }
}
