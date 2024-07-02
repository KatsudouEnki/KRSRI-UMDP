void obstacle_puing2(){
  if(MIRROR_SIDE == 0){
    int set_point=sp_puing2_n, offset=15;
    int state=0;
    int count=0;
    while(state==0){//130
      compass();
      distance_detection();
      
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        distance_detection();
        if(back_dis>12 || back_dis == 0){
          reverse_fast_obstacle();
          count++;
          if(count >=4){
            crabwalk_left_obstacle();
            count=0;
          }
        } 
        else if(right_dis > 50 || right_dis == 0){
          state=1;
        }
        else{
          crabwalk_left_obstacle();
        }
      }
    }
    walk_fast_obstacle();
    walk_fast_obstacle();
    
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

    speed=800;
    state=0;
    while(state==0){
      distance_detection();
      if(left_dis>18 || left_dis==0){
        crabwalk_left_obstacle();
      }
      else{
        state=1;
      }
    }
  }
  
  else{
    /************** Mirror side **************/
    int set_point=sp_puing2_m, offset=15;
    int state=0;
    int count=0;
    while(state==0){//130
      compass();
      distance_detection();

       if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        distance_detection();
        if(back_dis>12 || back_dis == 0){
          reverse_fast_obstacle();
          count++;
          if(count >=4){
            crabwalk_right_obstacle();
            count=0;
          }
        }
        else if(left_dis < 50 || left_dis == 0){
          state=1;
        }
        else{
          crabwalk_right_obstacle();
        }
      }
    }
      
      walk_fast_obstacle();
      walk_fast_obstacle();
      
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

    speed=800;
    state=0;
    while(state==0){
      distance_detection();
      if(right_dis>18 || right_dis==0){
        crabwalk_right_obstacle();
      }
      else{
        state=1;
      }
    }
  }
  speed=800;
}
