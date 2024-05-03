/* COMMANDS LIST
1.  default_state()
2.  walk_fast()
3.  walk_fast_obstacle()
4.  walk_fast_balls()
5.  reverse_fast()
6.  turn_left_slow()
7.  turn_left_fast()
8.  turn_left_obstacle()
9.  turn_right_slow()
10. turn_right_fast()
11. turn_right_obstacle()
12. crabwalk_left()
13. crabwalk_left_obstacle()
14. crabwalk_right()
15. crabwalk_right_obstacle()
16. cam_state()
17. walk_to_victim()
*/

void loop(){
  
  preparation();
  display.clearDisplay();
  servoAngkat.write(0);
  delay(2000);

  unsigned long timer=millis();
  
//  obstacle_kelereng();
//  digitalWrite(7,HIGH);
//  transisi_r5_r6();
//  while(true){
//    compass();
////    distance_detection();
////    data_display();
////    if(azimuth<=190 && azimuth>=60){
////      turn_right_fast();
////    }
////    else if(azimuth<230 && azimuth > 190){
////      turn_right_slow();
////    }
////    else if(azimuth>250 && azimuth<=290){
////      turn_left_slow();
////    }
////    else if(azimuth>290 || azimuth<60){
////      turn_left_fast();
////    }
////    else{//240
////      default_state();
////    }
//  }
  while(true){
    
    if(digitalRead(11)==HIGH){
      digitalWrite(7,LOW);
      home();
      digitalWrite(7,!digitalRead(7));
      obstacle_puing1();
      digitalWrite(7,!digitalRead(7));
      obstacle_miring();
      digitalWrite(7,!digitalRead(7));
      obstacle_kelereng();
      digitalWrite(7,!digitalRead(7));

//      while(true){
//        default_state();
//        distance_detection();
////        data_display;
//
//        display.clearDisplay();
//        display.setCursor(50,0);
//        display.print("F=");
//        display.print(front_dis);
//        display.setCursor(0,32);
//        display.print("L=");
//        display.print(left_dis);
//        display.setCursor(80,32);
//        display.print("R=");
//        display.print(right_dis);
//        display.setCursor(50,50);
//        display.print("B=");
//        display.print(back_dis);
//        display.display();
//        delay(100);
////        timer=now;
//      }
      transisi_r5_r6();
      digitalWrite(7,!digitalRead(7));
      obstacle_puing2();
      digitalWrite(7,!digitalRead(7));
      obstacle_batu2();
      digitalWrite(7,!digitalRead(7));
      while(true){
        compass();
        distance_detection();
        if(roll > -16){
          pre_ladder();
        }else{
          ladder();
        }
      }
    }
    else{
      unsigned long now=millis();
      compass();
      if(now - timer>750){
        digitalWrite(7,!digitalRead(7));
        
        distance_detection();
//        data_display;

//        display.clearDisplay();
//        display.setCursor(50,0);
//        display.print("F=");
//        display.print(front_dis);
//        display.setCursor(0,32);
//        display.print("L=");
//        display.print(left_dis);
//        display.setCursor(80,32);
//        display.print("R=");
//        display.print(right_dis);
//        display.setCursor(50,50);
//        display.print("B=");
//        display.print(back_dis);
//        display.display();
        delay(100);
        timer=now;
      }
      
      
    }
  }
//  // while(true){
////    compass();
////    distance_detection();
////    data_display();
//  digitalWrite(7,HIGH);
//  obstacle_batu2();
//  

  
  while(true){
    ladder_right();
  }
  
  digitalWrite(7, LOW);
  default_state();


}
