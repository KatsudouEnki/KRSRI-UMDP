void obstacle_batu1(){
  if(MIRROR_SIDE == 0){
    int set_point=55, offset=10;
    int state=0;
    while(state==0){
      compass();
      
//      if(azimuth<set_point-40 || azimuth>=set_point+180){
//        turn_right_fast();
//      }
//      else if(azimuth>=set_point-40 && azimuth<set_point-offset){
//        turn_right_slow();
//      }
//      else if(azimuth>set_point+offset && azimuth<set_point+40){
//        turn_left_slow();
//      }
//      else if(azimuth>=set_point+40 && azimuth<set_point+180){
//        turn_left_fast();
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
      else{
        walk_fast();
      }
      
      compass();
      distance_detection();
      if((front_dis<25 &&front_dis>0) && (roll<=4 && roll>=-4) && (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=55, offset=10;
    int state=0;
    while(state==0){
      compass();
      
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
      if((front_dis<25 &&front_dis>0) && (roll<=4 && roll>=-4) && (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
}
