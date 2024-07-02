void r10(){
  if(MIRROR_SIDE == 0){
    int set_point=sp_r10_n, offset=8;
    int state=0;
    int count=0;  
    while(state==0){//130
      compass();
      distance_detection();
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        state=1;
      }
    }
  
    speed=500;
    state=0;
    while(state == 0){
      
      crabwalk_left_obstacle();
      count++;
  
      if(count > 15){
        distance_detection();
        compass();
        if((left_dis > 0 && left_dis <= 20)){
          state=1;
        }
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=sp_r10_m, offset=8;
    int state=0;
    int count=0;  
    while(state==0){//130
      compass();
      distance_detection();
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        state=1;
      }
    }
  
    speed=500;
    state=0;
    while(state == 0){
      
      crabwalk_right_obstacle();
      count++;
  
      if(count > 15){
        distance_detection();
        compass();
        if((right_dis > 0 && right_dis <= 20)){
          state=1;
        }
      }
    }
  }
  
}
