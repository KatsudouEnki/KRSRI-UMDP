void transisi_r5_r6(){
  if(MIRROR_SIDE == 0){
    ///////////////////////////keluar darikelereng dalam kondsi nyerong
    int set_point=sp_transisi_n_1, offset=10;
    
    int state=0,repeat=0;
    while(state==0){
      compass();
      
      if(repeat==5){
        crabwalk_right();
        repeat=0;
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{
        compass();
        distance_detection();
        
        if(front_dis>22 || front_dis==0){
          walk_fast_obstacle();
          repeat=repeat+1;
        }
        else{
          state=1;
        }
      }
    }

  
    state=0;
    int status_gerak=0;
    while(state==0){
      set_point=sp_transisi_n_2; offset=15;
      compass();
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
        distance_detection();
        data_display();
        if(back_dis<25 && back_dis>0){
          state=1;
        }
        else{
          reverse_fast_obstacle();
          status_gerak++;
          if(status_gerak == 2){
            crabwalk_left_obstacle();
            status_gerak=0;
          }
        }
      }
    }
  }
  
  else{
    /************** Mirror side **************/
    ///////////////////////////keluar darikelereng kondsi nyerong
    int set_point=sp_transisi_m_1, offset=10;
    
    int state=0,repeat=0;
    while(state==0){
      compass();

      if(repeat==5){
        crabwalk_left();
        repeat=0;
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'n')){
        turn_right_obstacle();
      }
      else if(HeadingJustification(azimuth, set_point, 180, offset, 'p')){
        turn_left_obstacle();
      }
      else{//240
        compass();
        distance_detection();
        
        if(front_dis>22 || front_dis==0){
          walk_fast_obstacle();
          repeat=repeat+1;
        }
        else{
          state=1;
        }
      }
    }
   
    
    state=0;
    int status_gerak=0;
    while(state==0){//180
      set_point=sp_transisi_m_2; offset=15;
      compass();
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
        distance_detection();
        data_display();
        if(back_dis<25 && back_dis>0){
          state=1;
        }
        else{
          reverse_fast_obstacle();
          status_gerak++;
          if(status_gerak == 2){
            crabwalk_right_obstacle();
            status_gerak=0;
          }
        }
      }
    }
  }
}
