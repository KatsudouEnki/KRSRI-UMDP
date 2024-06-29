void korban1(){
  if(MIRROR_SIDE == 0){
    speed=200;
    int set_point=335, offset=6;
    
    int state=0;
    while(state==0){
      compass();
//      if(azimuth<=set_point-50 && azimuth>=set_point-180){//285 155
//        turn_right_fast();
//      }
//      else if(azimuth<set_point-offset && azimuth > set_point-50){//329 285
//        turn_right_slow();
//      }
//      else if(azimuth>set_point+offset || azimuth<=set_point-310){//341 25
//        turn_left_slow();
//      }
//      else if(azimuth<set_point-180 && azimuth>set_point-310){//285 25
//        turn_left_fast();
//      }
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
      else{
        reverse_fast();
        distance_detection();
    
        if(back_dis<10 && back_dis>0){
          state=1;
          default_state();
        }
      } 
    } 
  }
  else{
    /************** Mirror side **************/
    speed=200;
    int set_point=120, offset=6;
    
    int state=0;
    while(state==0){
      compass();
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
        distance_detection();
    
        if(back_dis<10 && back_dis>0){
          state=1;
          default_state();
        }
      } 
    }
  }
}
