void obstacle_miring(){
  if(MIRROR_SIDE == 0){
    int set_point=sp_miring_n, offset=10;
    
    int state=0;
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
      if((roll<=2 && roll>=-2) && (galatArahHitung(set_point, azimuth)>=(-1*offset) && galatArahHitung(set_point, azimuth)<=offset)){
        state=1;
        default_state();
      }
    }
  }
  else{
    /************** Mirror side **************/
    int set_point=sp_miring_m, offset=10;
    
    int state=0;
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
      if((roll<=2 && roll>=-2) && (galatArahHitung(set_point, azimuth)>=(-1*offset) && galatArahHitung(set_point, azimuth)<=offset)){
        state=1;
        default_state();
      }

    }
  }
}
