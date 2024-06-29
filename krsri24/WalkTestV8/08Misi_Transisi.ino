void transisi_r5_r6(){
  if(MIRROR_SIDE == 0){
    ///////////////////////////keluar darikelereng dalam kondsi nyerong
    int set_point=250, offset=10;
    
    int state=0,repeat=0;
    while(state==0){
      compass();
      
      if(repeat==5){
        crabwalk_right();
        repeat=0;
      }
      else if(azimuth>set_point+offset || azimuth<set_point-180){
        turn_left_obstacle();
      }
      else if(azimuth<set_point-offset && azimuth>=set_point-180){
        turn_right_obstacle();
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
    while(state==0){
      set_point=313; offset=15;
      compass();
      
      if(azimuth<=set_point-40 && azimuth>set_point-180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+40){
        turn_left_slow();
      }
      else if(azimuth>set_point+40 || azimuth<set_point-180){
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
    int set_point=180, offset=10;
    
    int state=0,repeat=0;
    while(state==0){
      compass();
      if(repeat==5){
        crabwalk_left();
        repeat=0;
      }
      else if(azimuth>set_point+offset && azimuth<set_point+180){
        turn_left_obstacle();
      }
      else if(azimuth<set_point-offset || azimuth>=set_point+180){
        turn_right_obstacle();
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
      set_point=120; offset=15;
      compass();
      
      if(azimuth<=set_point-40 || azimuth>set_point+180){
        turn_right_fast();
      }
      else if(azimuth<set_point-offset && azimuth > set_point-40){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<=set_point+40){
        turn_left_slow();
      }
      else if(azimuth>set_point+40 && azimuth<set_point+180){
        turn_left_fast();
      }
      else{
        distance_detection();
        data_display();
        if(back_dis<10 && back_dis>0){
          state=1;
        }
        else{
          reverse_fast_obstacle();
        }
      }
    }
  }
}
