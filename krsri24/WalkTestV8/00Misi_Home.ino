void home(){
  if(MIRROR_SIDE == 0){
    int set_point=335, offset=6;
    int state=0;
    while(state==0){
      compass();
      if(azimuth<=set_point-40 && azimuth>=set_point-180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset || azimuth<=set_point-320){
        turn_left_slow();
      }
      else if(azimuth<set_point-180 && azimuth>set_point-320){
        turn_left_fast();
      }
      else{
        crabwalk_right_test0();
        distance_detection();
        data_display();
    
        if(left_dis>53 || left_dis==0){
          state=1;
          default_state();
        }
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=120, offset=6;
    int state=0;
    while(state==0){
      compass();
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
        crabwalk_left();
        distance_detection();
        data_display();
    
        if(right_dis>53 || right_dis==0){
          state=1;
          default_state();
        }
      }
    }
  }
}
