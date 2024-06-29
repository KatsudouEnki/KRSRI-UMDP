void obstacle_batu2_ver2(){
  if(MIRROR_SIDE == 0){
    int set_point=321, offset=20;
    int state=0, counter=0;
    while(state==0){//130
      compass();

//      if(azimuth<=set_point-offset && azimuth>=set_point-180){
//        turn_right_obstacle();
//      }
//      else if(azimuth>=set_point+offset || azimuth<set_point-180){
//        turn_left_obstacle();
//      }
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        
        distance_detection();
        if((back_dis>=33 && (azimuth >set_point-offset && azimuth<set_point+offset) && (left_dis<=15 && left_dis>0))|| pitch >= 15){
          state=1;
          default_state();
        }
        else if(left_dis>15 || left_dis==0){
          crabwalk_left_obstacle();
        }
        else if(back_dis<33){
          walk_fast_obstacle();
        }
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=210, offset=20;
    int state=0, counter=0;
    while(state==0){//130
      compass();

      if(azimuth<=set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>=set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{
        
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
