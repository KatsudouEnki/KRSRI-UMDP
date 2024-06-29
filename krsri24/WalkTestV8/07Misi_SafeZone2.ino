void safe_zone2(){
  if(MIRROR_SIDE == 0){
    int set_point=321, offset=10;
    int state=0;
    speed=500;
    
    while(state==0){
      compass();
//      if(azimuth<=set_point-50 && azimuth>=set_point-180){
//        turn_right_obstacle_fast();
//      }
//      else if(azimuth<set_point-offset && azimuth > set_point-50){
//        turn_right_obstacle();
//      }
//      else if(azimuth>set_point+offset || azimuth<=set_point-310){
//        turn_left_obstacle();
//      }
//      else if(azimuth<set_point-180 && azimuth>set_point-310){
//        turn_left_obstacle_fast();
//      }
      if(HeadingJustification(azimuth, set_point, 180, 40, 'n')){
        turn_right_fast();
      }
      else if(HeadingJustification(azimuth, set_point, 40, offset, 'n')){
        turn_right_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 40, offset, 'p')){
        turn_left_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 40, 'p')){
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
        distance_detection();
        if((back_dis>=60 && back_dis<=75) || (front_dis <=25 && front_dis>=15)){
          state=1;
        }
        else if((back_dis >75 || back_dis ==0) || (front_dis <15)){
          reverse_fast();
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
