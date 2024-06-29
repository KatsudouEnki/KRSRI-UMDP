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
  servo_movement("putar", 0);
  servo_movement("angkat", 0);
  servo_movement("buka",0);
  default_state();
}











/*
void obstacle_kelereng(){
  int state=0;
  while(state==0){
    compass();
    // distance_detection();
    // data_display();
    if(azimuth<=250 && azimuth>=120){
      turn_right_obstacle_fast();
    }
    else if(azimuth<290 && azimuth > 250){
      turn_right_obstacle();
    }
    else if(azimuth>310 && azimuth<=350){
      turn_left_obstacle();
    }
    else if(azimuth<120 || azimuth>350){
      turn_left_obstacle_fast();
    }
    else{//240
      state=1;
    }
  }
  /////////////////////////problem when robot sidewalking because the marble making robot slip and rotates ////solved?
  int prep=0;
  while(prep==0){
    // compass();
    distance_detection();
    data_display();
    if(back_dis<=30 && back_dis>0){
      walk_fast_balls();
    }
    else if(right_dis>10 || right_dis==0){
      crabwalk_right();
    }
    else{
      prep=1;
    }
  }
  state=0;
  
  while(state==0){
    compass();
    // distance_detection();
    // data_display();
    if(azimuth<=250 && azimuth>=120){
      turn_right_fast();
    }
    else if(azimuth<290 && azimuth > 250){
      turn_right_slow();
    }
    else if(azimuth>310 && azimuth<=350){
      turn_left_slow();
    }
    else if(azimuth<130 || azimuth>350){
      turn_left_fast();
    }
    else{//240
      walk_fast_obstacle();
    }


    // compass();
    distance_detection();
    data_display();
    if((back_dis>75 || back_dis==0)&& (left_dis>50 || left_dis==0)){
//    if(front_dis<23 && front_dis>0){
      state=1;
    }
  }
}
*/









void obstacle_batu2(){
  if(MIRROR_SIDE == 0){
    int set_point=207, offset=20;
    int state=0, counter=0;
    while(state==0){//130
      compass();
      // distance_detection();

      if(azimuth<=set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>=set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{//330
        
        compass();
        distance_detection();
        if((left_dis>=33 && (azimuth >set_point-offset && azimuth<set_point+offset) && (front_dis<=15 && front_dis>0))|| counter>=4  || roll < -6){
          state=1;
          default_state();
        }
        else if(front_dis>15 || front_dis==0){
          walk_fast_obstacle();
        }
        else if(left_dis<33){
          crabwalk_right_obstacle();
          counter++;
        }
      }
    }
  }
  else{
    int set_point=210, offset=20;
    int state=0, counter=0;
    while(state==0){//130
      compass();
      // distance_detection();

      if(azimuth<=set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>=set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{//330
        
        compass();
        distance_detection();
        if((right_dis>=33 && (azimuth >set_point-offset && azimuth<set_point+offset) && (front_dis<=17 && front_dis>0))|| counter>=4 || roll < -6){
          state=1;
          default_state();
        }
        else if(right_dis<33){
          crabwalk_left_obstacle();
          counter++;
        }
        else if(front_dis>17 || front_dis==0){
          walk_fast_obstacle();
        }
      }
    }
  }
}



void obstacle_tangga(){
  if(MIRROR_SIDE == 0){
    int set_point=207, offset=3;
    int state=0, counter=0;
    while(state==0){//130
      compass();
      // distance_detection();

      if(azimuth<set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>set_point+offset|| azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{//330
        crabwalk_right_obstacle();
        counter++;
      }
          
      compass();
      distance_detection();
      if((left_dis>=33 &&(azimuth>=set_point-offset && azimuth<=set_point+offset)) || counter>7){
        state=1;
        default_state();
      }
    }
    display.clearDisplay();
    
    
    while(state==1){
      compass();
      // distance_detection();
      if(roll < -20){
        state=2;
      }
      else{
        pre_ladder_test(roll);
      }
    }
    
    servo_movement("angkat",4);
    
    counter = 0;
    set_point=230, offset=4;
    while(state==2){//sdh di tangga
      compass();
      // distance_detection();
      digitalWrite(7, !digitalRead(7));

      if(azimuth<set_point-offset && azimuth>=set_point-180){
        ladder_right();
        counter=counter-1;
        if(counter<=0){
          counter=0;
        }
      }
      else if(azimuth> set_point+offset || azimuth<set_point-180){
        ladder_left();
        counter=counter-1;
        if(counter<=0){
          counter=0;
        }
      }
      else if(counter>=12){
  //    else if(roll>-16 && counter>=5){
        state=3;
      }
      else{
      //  ladder();
        pre_ladder_test(roll);
        counter++;
      }
    }
    
    servo_movement("angkat",4);//servo_movement("angkat",1);
    counter=0;

    //bagian atas tangga
    while(state==3){
      compass();
      distance_detection();
      if(roll>-18 && counter>7){
        state=4;
      }
      else{
        pre_ladder_test(roll);
        if(counter>11){
          servo_movement("angkat",5);//servo_movement("angkat",2);
          ladder_stand(roll);
          
          delay(100);
          compass();
          if(gripper_dis>=55 && gripper_dis<=80){
            state=4;
            servo_movement("angkat",4);//servo_movement("angkat",1);
            compass();
            pre_ladder_test(roll);
            compass();
            pre_ladder_test(roll);
            compass();
            pre_ladder_test(roll);
          }
        }
        counter++;
      }
      delay(200);
    }
    
    while(state==4){
      compass();
      distance_detection();
      digitalWrite(7, !digitalRead(7));
    
      post_ladder();
      post_ladder_rev(roll);
      post_ladder_rev(roll);
      if(roll>7){
        default_state();
        state=5;
      }
    }
    while(state==5){
      compass();
      post_ladder_rev(roll);
    }
  }
  else{//////////////mirror side
    int set_point=210, offset=3;
    int state=0, counter=0;
    while(state==0){//130
      compass();
      // distance_detection();

      if(azimuth<set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>set_point+offset|| azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{//330
        crabwalk_left_obstacle();
        counter++;
      }
          
      compass();
      distance_detection();
      if((right_dis>=33 &&(azimuth>=set_point-offset && azimuth<=set_point+offset)) || counter>7){
        state=1;
        default_state();
      }
    }
    display.clearDisplay();
    
    
    while(state==1){
      compass();
      // distance_detection();
      if(roll < -20){
        state=2;
      }
      else{
        pre_ladder_test(roll);
      }
    }
    
    servo_movement("angkat",4);
    
    counter = 0;
    set_point=208, offset=4;
    while(state==2){//sdh di tangga
      compass();
      // distance_detection();
      digitalWrite(7, !digitalRead(7));

      if(azimuth<set_point-offset && azimuth>=set_point-180){
        ladder_right();
        counter=counter-1;
        if(counter<=0){
          counter=0;
        }
      }
      else if(azimuth> set_point+offset || azimuth<set_point-180){
        ladder_left();
        counter=counter-1;
        if(counter<=0){
          counter=0;
        }
      }
      else if(counter>=12){
  //    else if(roll>-16 && counter>=5){
        state=3;
      }
      else{
      //  ladder();
        pre_ladder_test(roll);
        counter++;
      }
    }
    
    servo_movement("angkat",4);//servo_movement("angkat",1);
    counter=0;

    //bagian atas tangga
    while(state==3){
      compass();
      distance_detection();
      if(roll>-18 && counter>7){
        state=4;
      }
      else{
        pre_ladder_test(roll);
        if(counter>11){
          servo_movement("angkat",5);//servo_movement("angkat",2);
          ladder_stand(roll);
          
          delay(100);
          compass();
          if(gripper_dis>=55 && gripper_dis<=80){
            state=4;
            servo_movement("angkat",4);//servo_movement("angkat",1);
            compass();
            pre_ladder_test(roll);
            compass();
            pre_ladder_test(roll);
            compass();
            pre_ladder_test(roll);
          }
        }
        counter++;
      }
      delay(200);
    }
    
    while(state==4){
      compass();
      distance_detection();
      digitalWrite(7, !digitalRead(7));
    
      post_ladder();
      post_ladder_rev(roll);
      post_ladder_rev(roll);
      if(roll>7){
        default_state();
        state=5;
      }
    }
    while(state==5){
      compass();
      post_ladder_rev(roll);
    }
      
  }
}



void korban5(){
  int set_point=321, offset=10;
  int state=0,repeat=0;

  while(state==0){
    compass();
    distance_detection();

    if(azimuth<=set_point-offset && azimuth>=set_point-180){
      turn_right_obstacle();
    }
    else if(azimuth>set_point+offset || azimuth<set_point-180){
      turn_left_obstacle();
    }
    else{//330
      distance_detection();
      if(front_dis <= 10){
        state=1;
      }
      else{
        walk_fast_obstacle();
      }
    }
  }

  set_point=250, offset=10;
  state=0,repeat=0;
  
  state=0;
  while(state==0){
    compass();
    if(azimuth>set_point+offset || azimuth<set_point-180){
      turn_left_obstacle();
    }
    else if(azimuth<set_point-offset && azimuth>=set_point-180){
      turn_right_obstacle();
    }
    else{//240
      state=1;
    }
  }
  for(int i=0; i<2;i++){
    walk_fast_obstacle();
  }
  default_state();
  servo_movement("buka", 3);
  servo_movement("angkat", 0);
  delay(200);
  servo_movement("angkat", 5);
  delay(1000);
  dummy_detection3();
  servo_movement("angkat", 0);
  servo_movement("putar", 0);
  servo_movement("buka", 2);
}
