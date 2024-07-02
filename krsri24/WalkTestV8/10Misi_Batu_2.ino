void obstacle_batu2_ver2(){
  if(MIRROR_SIDE == 0){
    int set_point=sp_batu2_n, offset=20;
    int state=0;
    while(state==0){//130
      compass();
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        compass();
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
    int set_point=sp_batu2_m, offset=20;
    int state=0;
    while(state==0){//130
      compass();

      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{
        compass();
        distance_detection();
        if((back_dis>=33 && (azimuth >set_point-offset && azimuth<set_point+offset) && (right_dis<=15 && right_dis>0))|| pitch < -15){
          state=1;
          default_state();
        }
        else if(right_dis<15 ||left_dis == 0){
          crabwalk_right_obstacle();
        }
        else if(back_dis<33){
          walk_fast_obstacle();
        }
      }
    }
  }
}
