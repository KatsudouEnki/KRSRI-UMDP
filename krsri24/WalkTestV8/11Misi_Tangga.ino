void obstacle_tangga2(){
  if(MIRROR_SIDE == 0){
    int set_point=321, offset=15;
    int state=0;
    int count=0;  
    while(state==0){//130
      compass();
      distance_detection();
  
      if(azimuth<=set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{//330
        distance_detection();
        if(front_dis <= 10){
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
    int set_point=321, offset=15;
    int state=0;
    int count=0;  
    while(state==0){//130
      compass();
      distance_detection();
  
      if(azimuth<=set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
      }
      else if(azimuth>set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else{//330
        distance_detection();
        if(front_dis <= 10){
          state=1;
        }
        else{
          walk_fast_obstacle();
        }
      }
    }
    
    state=0;
    while(state == 0){
      
      crabwalk_right_ladder();
      count++;
  
      if(count > 15){
        distance_detection();
        compass();
        if((right_dis > 0 && right_dis <= 27) &&(pitch >=-10 && pitch <=5)){
          state=1;
        }
      }
    }
    for(int i=0;i<4;i++){
      crabwalk_right_ladder();
    }
  }
}
