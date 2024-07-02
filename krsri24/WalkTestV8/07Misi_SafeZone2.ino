void safe_zone2(){
  if(MIRROR_SIDE == 0){
    int set_point=321, offset=10;
    int state=0;
    speed=500;
    
    while(state==0){
      compass();

      if(HeadingJustification(azimuth, set_point, 180, 50, 'n')){
        turn_right_fast();
      }
      else if(HeadingJustification(azimuth, set_point, 50, offset, 'n')){
        turn_right_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 50, offset, 'p')){
        turn_left_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 50, 'p')){
        turn_left_fast();
      }
      else{//240
        distance_detection();
        if(right_dis<16){
          crabwalk_left_obstacle();
        }
        else if(right_dis>21){
          crabwalk_right_obstacle();
        }
        else if((front_dis>0 && front_dis<=26) && (left_dis >=40 || left_dis == 0)){
          state=1;
        }
        else{
          walk_fast_obstacle();
        }
      }
    }
    servo_movement("putar", 2);
    delay(750);
    servo_movement("angkat", 4);
    delay(750);
    servo_movement("buka", 3);
    delay(750);
    servo_movement("angkat", 0);
    delay(750);
    servo_movement("buka", 0);
    servo_movement("putar", 0);
  }
  else{
    /************** Mirror side **************/
    int set_point=120, offset=10;
    int state=0;
    speed=500;

    while(state==0){
      compass();

      if(HeadingJustification(azimuth, set_point, 180, 50, 'n')){
        turn_right_fast();
      }
      else if(HeadingJustification(azimuth, set_point, 50, offset, 'n')){
        turn_right_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 50, offset, 'p')){
        turn_left_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 50, 'p')){
        turn_left_fast();
      }
      else{//240
        distance_detection();
        if(left_dis<16){
          crabwalk_right_obstacle();
        }
        else if(left_dis>21){
          crabwalk_left_obstacle();
        }
        else if((front_dis>0 && front_dis<=26) && (right_dis >=40 || left_dis == 0)){
          state=1;
        }
        else{
          walk_fast_obstacle();
        }
      }
    }
    servo_movement("putar", 4);
    delay(750);
    servo_movement("angkat", 4);
    delay(750);
    servo_movement("buka", 3);
    delay(750);
    servo_movement("angkat", 0);
    delay(750);
    servo_movement("buka", 0);
    servo_movement("putar", 0);
  }
}
