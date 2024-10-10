void obstacle_puing1(){
  speed=800;
  if(MIRROR_SIDE == 0){
    int set_point=sp_puing1_n, offset=10;
    
    int state=0;
    ////reposisioning before entering the obstacle
    while(state==0){
      compass();
      distance_detection();
      if(HeadingJustification(azimuth, set_point, 50, offset, 'n')){//54 && 14
        turn_right_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 50, offset, 'p')){//74 && 244
        turn_left_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 50, 'n')){//14 || 244
        turn_right_fast();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 50, 'p')){//74 && 224
        turn_left_fast();
      }
      else if(right_dis>=15 || right_dis == 0){
        crabwalk_right();
      }
      else{
        state=1;
      }
    }
  
    //////////walk on the obstacle
    
    offset=15;
    
    state=0;
    compass();
    while(state==0){
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{
        walk_fast_obstacle();
      }
      compass();
      if(roll>=9){//the obstacle after this have roll value of  when default position and gripper on lower side of the obstacle
        state=1;
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=sp_puing1_m, offset=10;
    
    int state=0;
    ////reposisioning before entering the obstacle
    while(state==0){
      compass();
      distance_detection();
      if(HeadingJustification(azimuth, set_point, 50, offset, 'n')){//54 && 14
        turn_right_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 50, offset, 'p')){//74 && 244
        turn_left_slow();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 50, 'n')){//14 || 244
        turn_right_fast();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 50, 'p')){//74 && 224
        turn_left_fast();
      }
      else if(left_dis>=15 || left_dis == 0){
        crabwalk_left();
      }
      else{
        state=1;
      }
    }
  
    //////////walk on the obstacle
    offset=15;
    
    state=0;
    compass();
    while(state==0){
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{
        walk_fast_obstacle();
      }
      compass();
      if(roll>=9){//the obstacle after this have roll value of  when default position and gripper on lower side of the obstacle
        state=1;
      }
    }
  }
}
