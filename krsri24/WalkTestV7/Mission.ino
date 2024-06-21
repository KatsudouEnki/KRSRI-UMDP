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

void home(){
  if(MIRROR_SIDE == 0){
    int set_point=300, offset=5;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      // data_display();
      if(azimuth<=set_point-40 && azimuth>=set_point-180){// 260-120
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){// 295-260
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+40){//305-340
        turn_left_slow();
      }
      else if(azimuth<set_point-180 || azimuth>set_point+40){//120 ++ 340
        turn_left_fast();
      }
      else{
        crabwalk_right_test0();
        // compass();
        distance_detection();
        data_display();
    
        if(left_dis>500 || left_dis==0){
          state=1;
          default_state();
        }
      }
    }
  }
  else{
    int set_point=120, offset=5;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      data_display();
      if(azimuth<=set_point-40 || azimuth>=set_point+180){ //80 ++ 300
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){ //115-80
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+40){ //125-160
        turn_left_slow();
      }
      else if(azimuth<set_point+180 && azimuth>set_point+40){ //300 - 160
        turn_left_fast();
      }
      else{
        crabwalk_right_test0();
//        crabwalk_left_test0();
        // compass();
        distance_detection();
        data_display();
    
        if(right_dis>500 || right_dis==0){
          state=1;
          default_state();
        }
      }
    }
  }
}

void korban1(){
  if(MIRROR_SIDE == 0){
    speed=200;
    int set_point=300, offset=4;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      // data_display();
      if(azimuth<=set_point-50 && azimuth>=set_point-180){//250 120
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){//296 250
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){//304 350
        turn_left_slow();
      }
      else if(azimuth<set_point-180 || azimuth>set_point+50){//120 350
        turn_left_fast();
      }
      else{
        reverse_fast();
        // compass();
        distance_detection();
        data_display();
    
        if(back_dis<10 && back_dis>0){
          state=1;
          default_state();
        }
      } 
    } 
  }
  else{
    speed=200;
    int set_point=120, offset=4;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      // data_display();
      if(azimuth<=set_point-50 || azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth<set_point+180 && azimuth>set_point+50){
        turn_left_fast();
      }
      else{
        reverse_fast();
        // compass();
        distance_detection();
        data_display();
    
        if(back_dis<10 && back_dis>0){
          state=1;
          default_state();
        }
      } 
    }
  }
}

void obstacle_puing1(){

  if(MIRROR_SIDE == 0){
    int set_point=20, offset=10;
    int state=0;
    ////reposisioning before entering the obstacle
    while(state==0){
      compass();
      distance_detection();
      if(azimuth<set_point-offset || azimuth > set_point+180){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+180){
        turn_left_slow();
      }
      else if(right_dis>=100 || right_dis == 0){
        crabwalk_right();
      }
      else{
        state=1;
      }
    }
  
    //////////walk on the obstacle
    state=0;
    while(state==0){
      set_point=20;
      offset=20;
      compass();
      // distance_detection();
  
      if(azimuth<set_point-offset || azimuth>=set_point+180){
        turn_right_obstacle();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+180){
        turn_left_obstacle();
      }
      else{
        walk_fast_obstacle();
      }
  
      compass();
      // distance_detection();
      if(roll>=9 && (azimuth<=40 && azimuth >=0)){//the obstacle after this have roll value of  when default position and gripper on lower side of the obstacle
        state=1;
      }
      else{
        state=0;
      }
    }
  }
  else{
    int set_point=20, offset=10;
    int state=0;
    ////reposisioning before entering the obstacle
    while(state==0){
      compass();
      distance_detection();
      if(azimuth<set_point-offset || azimuth > set_point+180){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+180){
        turn_left_slow();
      }
      else if(right_dis>=100 || right_dis == 0){
        crabwalk_right();
      }
      else{
        state=1;
      }
    }
  
    //////////walk on the obstacle
    state=0;
    while(state==0){
      set_point=20;
      offset=20;
      compass();
      // distance_detection();
  
      if(azimuth<set_point-offset || azimuth>=set_point+180){
        turn_right_obstacle();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+180){
        turn_left_obstacle();
      }
      else{
        walk_fast_obstacle();
      }
  
      compass();
      // distance_detection();
      if(roll>=9 && (azimuth<=40 && azimuth >=0)){//the obstacle after this have roll value of  when default position and gripper on lower side of the obstacle
        state=1;
      }
      else{
        state=0;
      }
    }
  }
}

void obstacle_miring(){
  if(MIRROR_SIDE == 0){
    int set_point=20, offset=10;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      
      if(azimuth<set_point+320 && azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point+320 || azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+offset){
        turn_left_slow();
      }
      else if(azimuth>=set_point+offset && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        walk_fast();
      }
      compass();
      // distance_detection();
      if((roll<=3 && roll>=-3) &&(azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
  else{
    int set_point=20, offset=10;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      
      if(azimuth<set_point+320 && azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point+320 || azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+offset){
        turn_left_slow();
      }
      else if(azimuth>=set_point+offset && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        walk_fast();
      }
      compass();
      // distance_detection();
      if((roll<=3 && roll>=-3) &&(azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
}

void obstacle_batu1(){
  if(MIRROR_SIDE == 0){
    int set_point=20, offset=10;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      
      if(azimuth<set_point+320 && azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point+320 || azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+40){
        turn_left_slow();
      }
      else if(azimuth>=set_point+40 && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        walk_fast();
      }
      compass();
      distance_detection();
      if((front_dis<25 &&front_dis>0) && (roll<=4 && roll>=-4) &&(azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
  else{
    int set_point=20, offset=10;
    int state=0;
    while(state==0){
      compass();
      // distance_detection();
      
      if(azimuth<set_point+320 && azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point+320 || azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+40){
        turn_left_slow();
      }
      else if(azimuth>=set_point+40 && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        walk_fast();
      }
      compass();
      distance_detection();
      if((front_dis<25 &&front_dis>0) && (roll<=4 && roll>=-4) &&(azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
}

void safe_zone1(){
  if(MIRROR_SIDE==0){
    int set_point=30, offset=10;
    int state=0;
    while(state==0){
      compass();
      distance_detection();
      
      if(azimuth<set_point+320 && azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point+320 || azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+40){
        turn_left_slow();
      }
      else if(azimuth>=set_point+40 && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        if((front_dis<=20 && front_dis>0)){
          reverse_fast();
        }
        else if((right_dis<80 && right_dis>0)){
          crabwalk_left();
        }
        else if((right_dis>110 || right_dis ==0)){
          crabwalk_right();
        }
        else{
          walk_fast();
        }
        
      }
      compass();
      distance_detection();
      if((front_dis<=30 && front_dis>20) && (right_dis>=80 && right_dis<=110)&& (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      } 
    }
    
    servo_movement("putar", 1);
    delay(500);
    servo_movement("angkat", 2);
    delay(500);
    servo_movement("buka", 3);
    delay(500);
    servo_movement("angkat", 0);
    delay(250);
    servo_movement("buka", 0);
    servo_movement("putar", 0);
  }
  else {
    int set_point=30, offset=10;
    int state=0;
    while(state==0){
      compass();
      distance_detection();
      
      if(azimuth<set_point+320 && azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point+320 || azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+40){
        turn_left_slow();
      }
      else if(azimuth>=set_point+40 && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        if((front_dis<=20 && front_dis>0)){
          reverse_fast();
        }
        else if((left_dis<800 && left_dis>0)){
          crabwalk_right();
        }
        else if((left_dis>110 || left_dis ==0)){
          crabwalk_left();
        }
        else{
          walk_fast();
        }
        
      }
      compass();
      distance_detection();
      if((front_dis<=30 && front_dis>20) && (right_dis>=80 && right_dis<=110)&& (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      } 
    }
    
    servo_movement("putar", 3);
    delay(500);
    servo_movement("angkat", 2);
    delay(500);
    servo_movement("buka", 3);
    delay(500);
    servo_movement("angkat", 0);
    delay(250);
    servo_movement("buka", 0);
    servo_movement("putar", 0);
  }
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
    else if(right_dis>100 || right_dis==0){
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
    if((back_dis>75 || back_dis==0)&& (left_dis>500 || left_dis==0)){
//    if(front_dis<23 && front_dis>0){
      state=1;
    }
  }
}
*/

void obstacle_kelereng_w_korban(){
  if(MIRROR_SIDE == 0){
    int set_point=225, offset=7;
    int state=0;
    speed=600;
    while(state==0){
      compass();
      distance_detection();
      data_display();
      if(azimuth<set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth<set_point-180 || azimuth>set_point+offset){
        turn_left_obstacle();
      }
      else{//240
        speed=325;
        compass();
        distance_detection();
        data_display();
        if(back_dis>13 || back_dis==0){
          reverse_fast_obstacle();
        }
        else if(left_dis<=440 && left_dis>0){
          crabwalk_right_obstacle();
        }
        else if(left_dis>=540 || left_dis==0){
          crabwalk_left_obstacle();
        }
        else if((right_dis<350 && right_dis>250) || (left_dis>440 && left_dis<540)){
          state=1;
        }
        else{
          state=0;
        }
      }
      delay(100);
    }
    /////////////////////////problem when robot sidewalking because the marble making robot slip and rotates ////solved?
  
    default_state();
    servo_movement("buka", 3);
    delay(200);
    servo_movement("angkat", 5);
    delay(100);
    dummy_detection2();
    servo_movement("angkat", 0);
    servo_movement("putar", 0);
    servo_movement("buka", 2);
  
    state=0;
    speed=500;
    while(state==0){
      set_point=300; offset=10;
      compass();
      distance_detection();
      data_display();
      if(azimuth<=set_point-50 && azimuth>=set_point-180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth<set_point-180 || azimuth>set_point+50){
        turn_left_fast();
      }
      else{//240
        if(right_dis<140){
          crabwalk_left_obstacle();
        }
        else if(right_dis>180){
          crabwalk_right_obstacle();
        }
        else{
          walk_fast_obstacle();
        }
      }
  
      // compass();
      distance_detection();
      data_display();
      if((front_dis<=23 && front_dis>0) && (right_dis>=140 && right_dis<=170)){
        state=1;
      }
    }
  }
  else{
    int set_point=225, offset=7;
    int state=0;
    speed=600;
    while(state==0){
      compass();
      // distance_detection();
      // data_display();
      if(azimuth<set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth<set_point-180 || azimuth>set_point+offset){
        turn_left_obstacle();
      }
      else{//240
        speed=325;
        // compass();
        distance_detection();
        data_display();
        if(back_dis>13 || back_dis==0){
          reverse_fast_obstacle();
        }
        else if(right_dis<=440 && right_dis>0){
//          crabwalk_left_test();
        }
        else if(right_dis>=540 || right_dis==0){
          crabwalk_right_obstacle();
        }
        else if((left_dis<350 && left_dis>250) || (right_dis>440 && right_dis<540)){
          state=1;
        }
        else{
          state=0;
        }
      }
      delay(100);
    }
    /////////////////////////problem when robot sidewalking because the marble making robot slip and rotates ////solved?
  
    default_state();
    servo_movement("buka", 3);
    delay(200);
    servo_movement("angkat", 5);
    delay(100);
    dummy_detection2();
    servo_movement("angkat", 0);
    servo_movement("putar", 0);
    servo_movement("buka", 2);
  
    state=0;
    speed=500;
    while(state==0){
      set_point=120; offset=10;
      compass();
      distance_detection();
      data_display();
      if(azimuth<=set_point-50 || azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth<set_point+180 && azimuth>set_point+50){
        turn_left_fast();
      }
      else{//240
        if(left_dis<140){
          crabwalk_right_obstacle();
        }
        else if(left_dis>180){
          crabwalk_left_obstacle();
        }
        else{
          walk_fast_obstacle();
        }
      }
  
      // compass();
      distance_detection();
      data_display();
      if((front_dis<=23 && front_dis>0) && (left_dis>=140 && left_dis<=170)){
        state=1;
      }
    }
  }
}

void safe_zone2(){
  if(MIRROR_SIDE == 0){
    int set_point=300, offset=10;
    int state=0;
    speed=500;
    while(state==0){
      compass();
      // distance_detection();
      // data_display();
      if(azimuth<=set_point-50 && azimuth>=set_point-180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth<set_point-180 || azimuth>set_point+50){
        turn_left_fast();
      }
      else{//240
        state=1;
      }
    }
    servo_movement("putar", 2);
    delay(750);
    servo_movement("angkat", 3);
    delay(750);
    servo_movement("buka", 3);
    delay(750);
    servo_movement("angkat", 0);
    delay(750);
    servo_movement("buka", 0);
    servo_movement("putar", 0);
  }
  else{
    int set_point=120, offset=10;
    int state=0;
    speed=500;
    while(state==0){
      compass();
      // distance_detection();
      // data_display();
      if(azimuth<=set_point-50 || azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth<set_point+180 && azimuth>set_point+50){
        turn_left_fast();
      }
      else{//240
        state=1;
      }
    }
    servo_movement("putar", 4);
    delay(750);
    servo_movement("angkat", 3);
    delay(750);
    servo_movement("buka", 3);
    delay(750);
    servo_movement("angkat", 0);
    delay(750);
    servo_movement("buka", 0);
    servo_movement("putar", 0);
  }
}

void transisi_r5_r6(){
  if(MIRROR_SIDE == 0){
    ///////////////////////////keluar darikelereng kondsi nyerong
    int set_point=260, offset=10;
    int state=0,repeat=0;
    while(state==0){
      compass();
      distance_detection();
      data_display();
        
      if(repeat==5){
        crabwalk_right();
        repeat=0;
      }
      else if(azimuth>set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else if(azimuth<set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else{//240
        compass();
        distance_detection();
        
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
    while(state==0){//180
      set_point=230; offset=20;
      compass();
      distance_detection();
      data_display();
      if (repeat==5){
        crabwalk_right();
        repeat=0;
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth>set_point+50 || azimuth<set_point-180){
        turn_left_fast();
      }
      else if(azimuth<=set_point-50 && azimuth>=set_point-180){
        turn_right_fast();
      }
      else{//180
        if(front_dis>10 || front_dis==0){//20 pas detect bagian puing di korban// 10 pas detect dinding sebelah korban
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
    int status_gerak=0;
    while(state==0){//180
      set_point=300; offset=15;
      compass();
      distance_detection();
      data_display();
      if(azimuth<=set_point-40 && azimuth>set_point-180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+40){
        turn_left_slow();
      }
      else if(azimuth>set_point+40 || azimuth<set_point-180){
        turn_left_fast();
      }
      else{//180
  //      if(left_dis>10 || left_dis==0){
  //      if((left_dis<10 && left_dis>0) && ((back_dis<=25 &&back_dis>0) || (front_dis<=15 && front_dis>0))){
        if(back_dis<10 && back_dis>0){
          state=1;
        }
        else{
          reverse_fast();
  //        status_gerak++;
  //        if(status_gerak>8){
  //          state=1;
  //        }
        }
      }
    }
  }
  else{
    ///////////////////////////keluar darikelereng kondsi nyerong
    int set_point=160, offset=10;
    int state=0,repeat=0;
    while(state==0){
      compass();
      distance_detection();
      data_display();
        
      if(repeat==5){
        crabwalk_right();
        repeat=0;
      }
      else if(azimuth>set_point+offset && azimuth<set_point+180){
        turn_left_obstacle();
      }
      else if(azimuth<set_point-offset || azimuth>=set_point+180){
        turn_right_obstacle();
      }
      else{//240
        compass();
        distance_detection();
        
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
    while(state==0){//180
      set_point=230; offset=20;
      compass();
      distance_detection();
      data_display();
      if (repeat==5){
        crabwalk_left();
        repeat=0;
      }
      else if(azimuth<set_point-offset && azimuth > set_point-50){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+50){
        turn_left_slow();
      }
      else if(azimuth>set_point+50 || azimuth<set_point-180){
        turn_left_fast();
      }
      else if(azimuth<=set_point-50 && azimuth>=set_point-180){
        turn_right_fast();
      }
      else{//180
        if(front_dis>10 || front_dis==0){//20 pas detect bagian puing di korban// 10 pas detect dinding sebelah korban
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
    int status_gerak=0;
    while(state==0){//180
      set_point=120; offset=15;
      compass();
      distance_detection();
      data_display();
      if(azimuth<=set_point-40 || azimuth>set_point+180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+40){
        turn_left_slow();
      }
      else if(azimuth>set_point+40 && azimuth<set_point+180){
        turn_left_fast();
      }
      else{//180
  //      if(left_dis>10 || left_dis==0){
  //      if((left_dis<10 && left_dis>0) && ((back_dis<=25 &&back_dis>0) || (front_dis<=15 && front_dis>0))){
        if(back_dis<10 && back_dis>0){
          state=1;
        }
        else{
          reverse_fast();
  //        status_gerak++;
  //        if(status_gerak>8){
  //          state=1;
  //        }
        }
      }
    }
  }
}

void obstacle_puing2(){//////////////////////////////masih belum
  int set_point=300, offset=15;
  int state=0;
  while(state==0){//130
    compass();
    distance_detection();

    if(azimuth<=set_point-offset && azimuth>=set_point-180){
      turn_right_obstacle();
    }
    else if(azimuth>set_point+offset || azimuth<set_point-180){
      turn_left_obstacle();
    }
    else{//330
      crabwalk_left_obstacle();
      if(right_dis>500){
      state=1;
    }
    }
    
    // compass();
    distance_detection();
    
      default_state();
      servo_movement("buka", 3);
      delay(200);
      servo_movement("angkat", 5);
      delay(100);
      dummy_detection2();
      servo_movement("angkat", 0);
      servo_movement("putar", 0);
      servo_movement("buka", 2);

    if(left_dis>100){
      crabwalk_left();
    }

    
    // compass();
    // distance_detection();
    // if((front_dis<=20 && front_dis>0)){  
    //   state=1;
    //   default_state();
    // }
  }
}

void obstacle_batu2(){
  int set_point=210, offset=20;
  int state=0;
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
      crabwalk_right_obstacle();
    }
        
    compass();
    distance_detection();
    if(left_dis>=350 && (azimuth >set_point-offset && azimuth<set_point+offset)){
      state=1;
      default_state();
    }
  }
}

void obstacle_tangga(){
  int set_point=228, offset=3;
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
    if((left_dis>=330 &&(azimuth>=set_point-offset && azimuth<=set_point+offset)) || counter>7){
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
  set_point=228, offset=4;
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
  
  servo_movement("angkat",1);
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
        servo_movement("angkat",2);
        ladder_stand(roll);
        
        delay(100);
        compass();
        if(gripper_dis>=55 && gripper_dis<=80){
          state=4;
          servo_movement("angkat",1);
          compass();
          pre_ladder_test(roll);
          compass();
          pre_ladder_test(roll);
          compass();
          pre_ladder_test(roll);
        }
//        if(gripper_dis>=55){
//          servo_movement("angkat",0);
//          delay(250);
//          servo_movement("putar",4);
//          delay(300);
//          servo_movement("angkat",2);
//          delay(300);
//          
//        }
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
