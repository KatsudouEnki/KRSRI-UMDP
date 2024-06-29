void safe_zone1(){
  speed=550;
  if(MIRROR_SIDE==0){
    int set_point=55, offset=10;
    
    int state=0;
    while(state==0){
      compass();
      distance_detection();
      
      if(azimuth<set_point-40 || azimuth>=set_point+180){
        turn_right_fast();
      }
      else if(azimuth>=set_point-40 && azimuth<set_point-offset){
        turn_right_slow();
      }
      else if(azimuth>set_point+offset && azimuth<set_point+40){
        turn_left_slow();
      }
      else if(azimuth>=set_point+40 && azimuth<set_point-180){
        turn_left_fast();
      }
      else{
        if((front_dis<=15 && front_dis>0)){
          reverse_fast();
        }
        else if((right_dis<11 && right_dis>0)){
          crabwalk_left();
        }
        else if((right_dis>16 || right_dis ==0)){
          crabwalk_right();
        }
        else{
          walk_fast();
        }
        
      }
      compass();
      distance_detection();
      if((front_dis<=25 && front_dis>20) && (right_dis>=11 && right_dis<=16)&& (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      } 
    }
    
    servo_movement("putar", 1);//penyesuaian lokasi gripper
    delay(500);
    servo_movement("angkat", 2);//peletakan arm gripper
    delay(500);
    servo_movement("buka", 3);//pelepasan korban
    delay(500);
    servo_movement("angkat", 0);//pengangkatan arm gripper
    delay(250);
    servo_movement("buka", 0);//menutup grip
    servo_movement("putar", 0);//mengembalikan lokasi gripper
  }
  
  else {
    /************** Mirror side **************/
    int set_point=55, offset=10;
    
    int state=0;
    while(state==0){
      compass();
      distance_detection();
      
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
        if((front_dis<=15 && front_dis>0)){
          reverse_fast();
        }
        else if((left_dis<11 && left_dis>0)){
          crabwalk_right();
        }
        else if((left_dis>16 || left_dis ==0)){
          crabwalk_left();
        }
        else{
          walk_fast();
        }
        
      }
      compass();
      distance_detection();
      if((front_dis<=25 && front_dis>15) && (left_dis>=11 && left_dis<=16)&& (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      } 
    }
    
    servo_movement("putar", 3);//penyesuaian lokasi gripper
    delay(500);
    servo_movement("angkat", 2);//peletakan arm gripper
    delay(500);
    servo_movement("buka", 3);//pelepasan korban
    delay(750);
    servo_movement("angkat", 0);//pengangkatan arm gripper
    delay(250);
    servo_movement("buka", 0);//menutup grip
    servo_movement("putar", 0);//mengembalikan lokasi gripper
  }
  speed=800;
}
