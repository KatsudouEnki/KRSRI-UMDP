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
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if(azimuth<=260 && azimuth>=120){
      turn_right_fast();
    }
    else if(azimuth<290 && azimuth > 250){
      turn_right_slow();
    }
    else if(azimuth>310 && azimuth<=350){
      turn_left_slow();
    }
    else if(azimuth<120 || azimuth>350){
      turn_left_fast();
    }
    else{//310
      crabwalk_right_test();
    }
    
    compass();
    distance_detection();
    data_display();

    if(left_dis>50 || left_dis==0){
      state=1;
      default_state();
    }
  }
  
}

void korban1(){
  speed=200;
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
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
    else{//310
      reverse_fast();
    }
    
    compass();
    distance_detection();
    data_display();

    if(back_dis<10 && back_dis>0){
      state=1;
      default_state();
    }
  }
  
}

void obstacle_puing1(){
  int state=0;
  ////reposisioning before entering the obstacle
  while(state==0){
    compass();
    distance_detection();
    if(azimuth<10 || azimuth > 235){
      turn_right_slow();
    }
    else if(azimuth>30 && azimuth<=235){
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
  while(state==0){
    compass();
    distance_detection();

    if(azimuth<0 || azimuth>=235){
      turn_right_obstacle();
    }
    else if(azimuth>40 && azimuth<235){
      turn_left_obstacle();
    }
    else{
      walk_fast_obstacle();
    }

    compass();
    distance_detection();
//    if(roll>=8 || (front_dis<=20 && front_dis>0)){//the obstacle after this have roll value of 8 when default position and gripper on lower side of the obstacle
    if(roll>=9 && (azimuth<=40 && azimuth >=0)){//the obstacle after this have roll value of  when default position and gripper on lower side of the obstacle
      state=1;
//      default_state();
    }
    else{
      state=0;
    }
  }
}

void obstacle_miring(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    
    if(azimuth<340 && azimuth>=200){
      turn_right_fast();
    }
    else if(azimuth>=340 || azimuth<10){
      turn_right_slow();
    }
    else if(azimuth>30 && azimuth<60){
      turn_left_slow();
    }
    else if(azimuth>=60 && azimuth<200){
      turn_left_fast();
    }
    else{
      walk_fast();
    }
    compass();
    distance_detection();
//    if((front_dis<25 && front_dis>0) && (roll<=3 && roll>=-3) &&(azimuth<=30 && azimuth >=10)){
    if((roll<=3 && roll>=-3) &&(azimuth<=30 && azimuth >=10)){
      state=1;
      default_state();
    }
  }
}

void obstacle_batu1(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    
    if(azimuth<340 && azimuth>=200){
      turn_right_fast();
    }
    else if(azimuth>=340 || azimuth<10){
      turn_right_slow();
    }
    else if(azimuth>30 && azimuth<60){
      turn_left_slow();
    }
    else if(azimuth>=60 && azimuth<200){
      turn_left_fast();
    }
    else{
      walk_fast();
    }
    compass();
    distance_detection();
    if((front_dis<25 &&front_dis>0) && (roll<=4 && roll>=-4) &&(azimuth<=30 && azimuth >=10)){
      state=1;
      default_state();
    }
  }
}

void safe_zone1(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    
    if(azimuth<350 && azimuth>=210){
      turn_right_fast();
    }
    else if(azimuth>=310 || azimuth<20){
      turn_right_slow();
    }
    else if(azimuth>40 && azimuth<70){
      turn_left_slow();
    }
    else if(azimuth>=70 && azimuth<210){
      turn_left_fast();
    }
    else{
      walk_fast();
    }
    compass();
    distance_detection();
    if((front_dis<=30) && (azimuth<=40 && azimuth >=20)){
      state=1;
      default_state();
    }
//    else if(front_dis<20 && front_dis>0){
//      reverse_fast();
//    }
  }
  
  servo_movement("putar", 2);
  delay(500);
  servo_movement("angkat", 1);
  delay(500);
  servo_movement("buka", 1);
  delay(500);
  servo_movement("angkat", 0);
  delay(250);
  servo_movement("buka", 0);
  servo_movement("putar", 0);
}

void obstacle_kelereng(){
  int state=0;
  while(state==0){
    compass();
    distance_detection();
    data_display();
    if(azimuth<=250 && azimuth>=120){
      turn_right_obstacle();
    }
    else if(azimuth<290 && azimuth > 250){
      turn_right_slow();
    }
    else if(azimuth>310 && azimuth<=350){
      turn_left_slow();
    }
    else if(azimuth<120 || azimuth>350){
      turn_left_obstacle();
    }
    else{//240
      state=1;
    }
  }
  /////////////////////////problem when robot sidewalking because the marble making robot slip and rotates ////solved?
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
    else if(azimuth>280 || azimuth<75){
      turn_left_obstacle();
    }
    else if(azimuth<250 && azimuth>=75){
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
    compass();
    distance_detection();
    data_display();
    if (repeat==5){
      crabwalk_right();
      repeat=0;
    }
    else if(azimuth<210 && azimuth > 180){
      turn_right_slow();
    }
    else if(azimuth>250 && azimuth<=280){
      turn_left_slow();
    }
    else if(azimuth>280 || azimuth<50){
      turn_left_fast();
    }
    else if(azimuth<=180 && azimuth>=50){
      turn_right_fast();
    }
    else{//180
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
  int status_gerak=0;
  while(state==0){//180
    compass();
    distance_detection();
    data_display();
    if(azimuth<=170 && azimuth>30){
      turn_right_fast();
    }
    else if(azimuth<195 && azimuth > 170){
      turn_right_slow();
    }
    else if(azimuth>215 && azimuth<=270){
      turn_left_slow();
    }
    else if(azimuth>270 || azimuth<40){
      turn_left_fast();
    }
    else{//180
//      if(left_dis>10 || left_dis==0){
//      if((left_dis<10 && left_dis>0) && ((back_dis<=25 &&back_dis>0) || (front_dis<=15 && front_dis>0))){
      if((left_dis<10 && left_dis>0) && (back_dis<=25 &&back_dis>0)){
        state=1;
      }
      else{
        crabwalk_left_obstacle();
        status_gerak++;
        if(status_gerak>8){
          state=1;
        }
      }
    }
    
  }
  
}

void obstacle_puing2(){
  int state=0;
  while(state==0){//130
    compass();
    distance_detection();

    if(azimuth<=200 && azimuth>=45){
      turn_right_obstacle();
    }
//    else if(azimuth<320 && azimuth > 280){
//      turn_right_slow();
//    }
//    else if(azimuth>340 || azimuth<20){
//      turn_left_slow();
//    }
    else if(azimuth>230 || azimuth<45){
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

    if(azimuth<=190 && azimuth>=45){
      turn_right_obstacle();
    }
//    else if(azimuth<320 && azimuth > 280){
//      turn_right_slow();
//    }
//    else if(azimuth>340 || azimuth<20){
//      turn_left_slow();
//    }
    else if(azimuth>=230 || azimuth<45){
      turn_left_obstacle();
    }
    else{//330
      crabwalk_right_obstacle();
    }
        
    compass();
    distance_detection();
    if(left_dis>=35 && (azimuth >190 && azimuth<230)){
      state=1;
      default_state();
    }
  }
}

void obstacle_tangga(){
  int state=0;
  while(state==0){//130
    compass();
    distance_detection();

    if(azimuth<=220 && azimuth>=45){
      turn_right_obstacle();
    }
    else if(azimuth>230|| azimuth<45){
      turn_left_obstacle();
    }
    else{//330
      crabwalk_right_obstacle();
    }
        
    compass();
    distance_detection();
    if(left_dis>=35 &&(azimuth >220 && azimuth<230)){
      state=1;
      default_state();
    }
  }
  display.clearDisplay();
  
  
  while(state==1){
    compass();
    distance_detection();
    pre_ladder();
    if(roll<-10){
      state=2;
    }
  }
  
  while(state==2){
    int counter = 0;
    compass();
    distance_detection();
    digitalWrite(7, !digitalRead(7));

    if(azimuth<=220 && azimuth>=45){
      ladder_right();
    }else if(azimuth>=230|| azimuth<45){
      ladder_left();
    }else if(roll>-16 && counter>=15){
      state=3;
    }else{
     ladder();
     counter++;
    }

     compass();
     distance_detection();
     digitalWrite(7, !digitalRead(7));
    }

    while(state==3){
    compass();
    distance_detection();
    digitalWrite(7, !digitalRead(7));

    post_ladder();
    if(roll>-2 && front_dis>0 && front_dis<25){
      default_state();
      state=4;
    }
    }
    
}
