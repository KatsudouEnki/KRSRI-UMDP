void obstacle_kelereng_w_korban(){
  if(MIRROR_SIDE == 0){
    digitalWrite(11,LOW);
    digitalWrite(9,LOW);

    int set_point=sp_kelereng_n, offset=6;
    int state=0;
    int count=0;
    speed=500;
    
    int state_compass = 0;
    while(state_compass != 1){
      digitalWrite(9,LOW);
      digitalWrite(11,HIGH);
      compass();

      if(!( azimuth >=set_point-offset && azimuth <= set_point+offset)){
        state_compass = 0;
        state=0;
        
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
      }
      else{
        state_compass=1;
      }
    }


    distance_detection();
    compass();
    count=0;
    while( !( (galatArahHitung(set_point, azimuth)>=(-1*offset) && galatArahHitung(set_point, azimuth)<=offset) && (back_dis>=12 && back_dis<=16) && (right_dis>= 36 && right_dis<=54) && (count>=6))){
      //compass();
      //distance_detection();

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
      else{//240
        speed=375;
        if(count<6){
          //distance_detection();
          if(back_dis>16 || back_dis==0){
            reverse_fast_obstacle();
          }
          else if(back_dis<12 && back_dis>0){
            walk_fast_obstacle();
          }
          else{
            crabwalk_right_obstacle();
            count++;
          }
        }
        else{
          // compass();
          default_state_obstacle();
          delay(125);
          distance_detection();
          data_display();
          if(back_dis>16 || back_dis==0){
            reverse_fast_obstacle();
          }
          else if(back_dis<12 && back_dis>0){
            walk_fast_obstacle();
          }
          else if(right_dis<36 && right_dis>0){
            crabwalk_left_obstacle();
          }
          else if(right_dis>54 || right_dis == 0){
            crabwalk_right_obstacle();
          }
        }
      }
      delay(10);
      compass();
      distance_detection();
      data_display();
    }

    
    default_state();
    servo_movement("buka", 3);
    delay(200);
    servo_movement("angkat", 5);
    delay(1000);
    dummy_detection2();
    servo_movement("angkat", 0);
    servo_movement("putar", 0);
    servo_movement("buka", 2);
    speed = 800;
  }
  else{
    /************** Mirror side **************/
    digitalWrite(11,LOW);
    digitalWrite(9,LOW);

    int set_point=sp_kelereng_m, offset=6;
    int state=0;
    int count=0;
    speed=500;
    
    int state_compass = 0;
    while(state_compass != 1){
      digitalWrite(9,LOW);
      digitalWrite(11,HIGH);
      compass();

      if(!( azimuth >=set_point-offset && azimuth <= set_point+offset)){
        state_compass = 0;
        state=0;
        
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
      }
      else{
        state_compass=1;
      }
    }


    distance_detection();
    compass();
    while( !((galatArahHitung(set_point, azimuth)>=(-1*offset) && galatArahHitung(set_point, azimuth)<=offset) && (back_dis>=12 && back_dis<=16) && (left_dis>=36 && left_dis<=54) && (count>=6))){
//      compass();
//      distance_detection();
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
      else{//240
        speed=375;
        if(count<6){
          distance_detection();
          data_display();
          if(back_dis>16 || back_dis==0){
            reverse_fast_obstacle();
          }
          else if(back_dis<12 && back_dis>0){
            walk_fast_obstacle();
          }
          else{
            crabwalk_left_obstacle();
            count++;
          }
        }
        else{
          // compass();
          default_state_obstacle();
          delay(125);
          distance_detection();
          data_display();
          if(back_dis>16 || back_dis==0){
            reverse_fast_obstacle();
          }
          else if(back_dis<12 && back_dis>0){
            walk_fast_obstacle();
          }
          else if(left_dis<36 && left_dis>0){
            crabwalk_right_obstacle();
          }
          else if(left_dis>54 || left_dis == 0){
            crabwalk_left_obstacle();
          }
        }
      }
      delay(10);
      distance_detection();
      compass();
    }
  
    default_state();
    servo_movement("buka", 3);
    delay(200);
    servo_movement("angkat", 5);
    delay(1100);
    dummy_detection2();
    servo_movement("angkat", 0);
    servo_movement("putar", 0);
    servo_movement("buka", 2);
  }
  speed=800;
}
