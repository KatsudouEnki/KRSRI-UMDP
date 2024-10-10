void home(){
  if(MIRROR_SIDE == 0){
    int set_point=sp_home_n, offset=7;
    int state=0;
    while(state==0){
      compass();
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
      else{
        crabwalk_right_test0();
        distance_detection();
//        data_display();
    
        if(left_dis>53 || left_dis==0){
          state=1;
          default_state();
        }
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=sp_home_m, offset=7;
    int state=0;
    while(state==0){
      compass();
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
      else{
        crabwalk_left();
        distance_detection();
//        data_display();
    
        if(right_dis>53 || right_dis==0){
          state=1;
          default_state();
        }
      }
    }
  }
}
