void obstacle_tangga2(){
  if(MIRROR_SIDE == 0){
    int set_point=sp_tangga_n, offset=15;
    int state=0;
    int count=0;  
    while(state==0){//130
      compass();
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      
      else{//330
        distance_detection();
        if(front_dis <= 12){
          state=1;
        }
        else{
          walk_fast_obstacle();
        }
      }
    }
    state=0;
    while(state == 0){
      
      crabwalk_left_ladder();
      count++;
  
      if(count > 15){
        distance_detection();
        compass();
        if((left_dis > 0 && left_dis <= 27) &&(pitch >=-5 && pitch <=10)){
          state=1;
        }
      }
    }
    for(int i=0;i<4;i++){
      crabwalk_left_ladder();
    }
  }

  else{
    /************** Mirror side **************/
    int set_point=sp_tangga_m, offset=15;
    int state=0;
    int count=0;  /*
    while(state==0){//130
      compass();  
      if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//330
        distance_detection();
        if(front_dis <= 12){
          state=1;
        }
        else{
          walk_fast_obstacle();
        }
      }
    }
    */
    set_point=sp_tangga_n;
    while(state==0){//130
      compass();  
      if(HeadingJustification(azimuth, set_point, 180, 40, 'n')){
        turn_right_obstacle_fast();
      }
      else if(HeadingJustification(azimuth, set_point, 40, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 40, offset, 'p')){
        turn_left_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, 40, 'p')){
        turn_left_obstacle_fast();
      }
      else{//330
        distance_detection();
        if(back_dis <= 12){
          state=1;
        }
        else{
          reverse_fast_obstacle();
        }
      }
    }
    
    state=0;
    while(state == 0){
      
      crabwalk_left_ladder();
      count++;
  
      if(count > 15){
        distance_detection();
        compass();
        if((left_dis > 0 && left_dis <= 27) &&(pitch >=-5 && pitch <=10)){
          state=1;
        }
      }
    }
    for(int i=0;i<4;i++){
      crabwalk_left_ladder();
    }
  }
}
