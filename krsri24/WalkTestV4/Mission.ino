/* Mission List
1. preparation()
2. home()
3. korban1()
4. obstacle_puing1()
5. obstacle_miring()
6. obstacle_kelereng()
7. transisi_r5_r6()
8. obstacle_puing2()
9. obstacle_batu2()
10 obstacle_tangga()
*/

/*Heading setting
 * 230 gripper hadap korban
 */


void preparation(){
  myservo.write(120);
  servoAngkat.write(90);
  servoBuka.write(15);
  default_state();
}

void home(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if(azimuth<=190 && azimuth>=60){
      turn_right_fast();
    }
    else if(azimuth<230 && azimuth > 190){
      turn_right_slow();
    }
    else if(azimuth>250 && azimuth<=290){
      turn_left_slow();
    }
    else if(azimuth>290 || azimuth<60){
      turn_left_fast();
    }
    else{//240
      crabwalk_right_test();
    }
    
    compass();
    distance_detection();
    data_display();

    if(left_dis>45 || left_dis==0){
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
  ////reposisioning before entering the obstacle
  while(state==0){
    compass();
    distance_detection();
    if(azimuth<300 && azimuth > 165){
      turn_right_slow();
    }
    else if(azimuth>320 || azimuth<165){
      turn_left_slow();
    }
    else if(right_dis>=10 || right_dis == 0){
      crabwalk_right();
    }
    else{
      state=1;
      
    }
    
  }

  //////////walk on the obstacle
  state=0;
  while(state==0){//310
    compass();
    distance_detection();

    if(azimuth<=290 && azimuth>=145){
      turn_right_obstacle();
    }
//    else if(azimuth<320 && azimuth > 280){
//      turn_right_slow();
//    }
//    else if(azimuth>340 || azimuth<20){
//      turn_left_slow();
//    }
    else if(azimuth>330 || azimuth<145){
      turn_left_obstacle();
    }
    else{//330
      walk_fast_obstacle();
    }

    compass();
    distance_detection();
//    if(roll>=8 || (front_dis<=20 && front_dis>0)){//the obstacle after this have roll value of 8 when default position and gripper on lower side of the obstacle
    if(roll>=8){//the obstacle after this have roll value of 8 when default position and gripper on lower side of the obstacle
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
    
    if(azimuth<270 && azimuth>=130){
      turn_right_fast();
    }
    else if(azimuth>=270 && azimuth<300){
      turn_right_slow();
    }
    else if(azimuth>320 && azimuth<350){
      turn_left_slow();
    }
    else if(azimuth>350 || azimuth<130){
      turn_left_fast();
    }
    else{
      walk_fast();
    }
    compass();
    distance_detection();
    if((front_dis<30 &&front_dis>0) && (roll<=3 && roll>=-3) &&(azimuth<=320 && azimuth >=300)){
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
    data_display();
    if(azimuth<=190 && azimuth>=60){
      turn_right_obstacle();
    }
    else if(azimuth<230 && azimuth > 190){
      turn_right_slow();
    }
    else if(azimuth>250 && azimuth<=290){
      turn_left_slow();
    }
    else if(azimuth>290 || azimuth<60){
      turn_left_obstacle();
    }
    else{//240
      state=1;
    }
  }
  /////////////////////////problem when robot sidewalking because the marble making robot slip and rotates it
  int prep=0;
  while(prep==0){
    compass();
    distance_detection();
    data_display();
    if(right_dis>10 || right_dis==0){
      crabwalk_right();
    }
    else if(back_dis<=30 && back_dis>0){
      walk_fast_balls();
    }
    else{
      prep=1;
    }
  }

  
  state=0;
  
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if(azimuth<=190 && azimuth>=60){
      turn_right_fast();
    }
    else if(azimuth<230 && azimuth > 190){
      turn_right_slow();
    }
    else if(azimuth>250 && azimuth<=290){
      turn_left_slow();
    }
    else if(azimuth>290 || azimuth<60){
      turn_left_fast();
    }
    else{//240
      walk_fast_obstacle();
    }


    compass();
    distance_detection();
    data_display();
    if((back_dis>75 || back_dis==0)&& (left_dis>50 || left_dis==0)){
//    if(front_dis<23 && front_dis>0){
      state=1;
    }
  }

  
}

void transisi_r5_r6(){
  ///////////////////////////keluar darikelereng kondsi nyerong
  int state=0,repeat=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if(repeat==5){
      crabwalk_right();
      repeat=0;
    }
//    else if(azimuth<185 && azimuth > 145){
//      turn_right_slow();
//    }
//    else if(azimuth>205 && azimuth<=245){
//      turn_left_slow();
//    }
    else if(azimuth>210 || azimuth<15){
      turn_left_obstacle();
    }
    else if(azimuth<=200 && azimuth>=15){
      turn_right_obstacle();
    }
    else{//240
      if(front_dis>22 || front_dis==0){
        walk_fast_obstacle();
        repeat=repeat+1;
      }
      else{
//        prep=1;
        state=1;
      }
      
    }
  }
///////////////////////////keluar dari kondisi nyerong
  state=0;
  repeat=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if (repeat==5){
      crabwalk_right();
      repeat=0;
    }
    else if(azimuth<160 && azimuth > 120){
      turn_right_slow();
    }
    else if(azimuth>180 && azimuth<=220){
      turn_left_slow();
    }
    else if(azimuth>220 && azimuth<350){
      turn_left_fast();
    }
    else if(azimuth<=120 || azimuth>350){
      turn_right_fast();
    }
    else{//240
      if(front_dis>20 || front_dis==0){
        walk_fast_obstacle();
        repeat+=1;
      }
      else{
//        prep=1;
        state=1;
      }
      
    }
  }

  state=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if(azimuth<=100 || azimuth>330){
      turn_right_fast();
    }
    else if(azimuth<150 && azimuth > 110){
      turn_right_slow();
    }
    else if(azimuth>170 && azimuth<=210){
      turn_left_slow();
    }
    else if(azimuth>210 && azimuth<340){
      turn_left_fast();
    }
    else{//240
      if(left_dis>10 || left_dis==0){
        crabwalk_left_obstacle();
      }
      else{
//        prep=1;
        state=1;
      }
      
    }
  }
}

void obstacle_puing2(){
  int state=0;
  while(state==0){//130
    compass();
    distance_detection();

    if(azimuth<=140 || azimuth>=355){
      turn_right_obstacle();
    }
//    else if(azimuth<320 && azimuth > 280){
//      turn_right_slow();
//    }
//    else if(azimuth>340 || azimuth<20){
//      turn_left_slow();
//    }
    else if(azimuth>180 && azimuth<355){
      turn_left_obstacle();
    }
    else{//330
      walk_fast_obstacle();
    }
    
    compass();
    distance_detection();
    
    if(left_dis>25 || left_dis==0){
      crabwalk_left();
    }

    
    compass();
    distance_detection();
    if((front_dis<=20 && front_dis>0)){
      state=1;
      default_state();
    }
  }
}

void obstacle_batu2(){
  int state=0;
  while(state==0){//130
    compass();
    distance_detection();

    if(azimuth<=140 || azimuth>=355){
      turn_right_obstacle();
    }
//    else if(azimuth<320 && azimuth > 280){
//      turn_right_slow();
//    }
//    else if(azimuth>340 || azimuth<20){
//      turn_left_slow();
//    }
    else if(azimuth>180 && azimuth<355){
      turn_left_obstacle();
    }
    else{//330
      crabwalk_right_obstacle();
    }
        
    compass();
    distance_detection();
    if(left_dis>=35){
      state=1;
      default_state();
    }
  }
}

void obstacle_tangga(){
  
}
