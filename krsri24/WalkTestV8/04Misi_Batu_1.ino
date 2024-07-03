void obstacle_batu1(){
  for (int i=0;i<3;i++){
    walk_fast_obstacle();
  }
  if(MIRROR_SIDE == 0){
    int set_point=sp_batu1_n, offset=10;
    int state=0;compass();
    while(state==0){
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
      else{
        walk_fast();
      }
      compass();
      distance_detection();
      if((front_dis<25 &&front_dis>0) && (roll<=2 && roll>=-2) && (galatArahHitung(set_point, azimuth)>=(-1*offset) && galatArahHitung(set_point, azimuth)<=offset)){
        state=1;
        default_state();
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=sp_batu1_m, offset=10;
    int state=0;
    compass();
    while(state==0){
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
      else{
        walk_fast();
      }
      
      compass();
      distance_detection();
      if((front_dis<25 &&front_dis>0) && (roll<=2 && roll>=-2) && (galatArahHitung(set_point, azimuth)>=(-1*offset) && galatArahHitung(set_point, azimuth)<=offset)){
        state=1;
        default_state();
      }
      
    }
  }
}
