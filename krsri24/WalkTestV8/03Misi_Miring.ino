void obstacle_miring(){
  if(MIRROR_SIDE == 0){
    int set_point=60, offset=10;
    
    int state=0;
    while(state==0){
      compass();
      
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{
        walk_fast();
      }
      
      compass();
      if((roll<=3 && roll>=-3) &&(azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=60, offset=10;
    
    int state=0;
    while(state==0){
      compass();
      
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{
        walk_fast();
      }
      
      compass();
      if((roll<=3 && roll>=-3) &&(azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      }
    }
  }
}
