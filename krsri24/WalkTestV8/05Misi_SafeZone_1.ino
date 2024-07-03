void safe_zone1(){
  speed=550;
  if(MIRROR_SIDE==0){
    int set_point=sp_sz1_n, offset=10;
    
    int state=0;
    while(state==0){
      compass();
      distance_detection();
      
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
        distance_detection();
        if((front_dis<=17 && front_dis>0)){
          reverse_fast_obstacle();
        }
        else if((right_dis<11 && right_dis>0)){
          crabwalk_left();
        }
        else if((right_dis>16 || right_dis ==0)){
          crabwalk_right();
        }
        else{
          walk_fast_obstacle();
        }
        
      }
      compass();
      distance_detection();
      if((front_dis<=25 && front_dis>17) && (right_dis>=11 && right_dis<=16)&& (azimuth<=set_point+offset && azimuth >=set_point-offset)){
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
    int set_point=sp_sz1_m, offset=10;
    
    int state=0;
    while(state==0){
      compass();
      distance_detection();
      
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
        distance_detection();
        if((front_dis<=17 && front_dis>0)){
          reverse_fast_obstacle();
        }
        else if((left_dis<11 && left_dis>0)){
          crabwalk_right();
        }
        else if((left_dis>16 || left_dis ==0)){
          crabwalk_left();
        }
        else{
          walk_fast_obstacle();
        }
        
      }
      compass();
      distance_detection();
      if((front_dis<=25 && front_dis>17) && (left_dis>=11 && left_dis<=16)&& (azimuth<=set_point+offset && azimuth >=set_point-offset)){
        state=1;
        default_state();
      } 
    }
    
    servo_movement("putar", 3);//penyesuaian lokasi gripper
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
  speed=800;
}
