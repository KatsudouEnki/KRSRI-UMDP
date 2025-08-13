/* COMMANDS LIST
1.  default_state()
2.  walk_fast() .
3.  walk_fast_obstacle() .
4.  walk_fast_balls()
5.  reverse_fast() .
6.  turn_left_slow() 
7.  turn_left_fast() .
8.  turn_left_obstacle() 
9.  turn_right_slow()
10. turn_right_fast() .
11. turn_right_obstacle()
12. crabwalk_left() .
13. crabwalk_left_obstacle() crabwalkLeftObstacle
14. crabwalk_right() .
15. crabwalk_right_obstacle()
16. cam_state()
17. walk_to_victim()
18. pre_ladder()
19. pre_ladder_right()
20. pre_ladder_left()
21. ladder()
22. ladder_right()
23. ladder_left()
24. post_ladder()
reverse_fast_obstacle() .
*/

void loop(){
  boot_state();
  randomSeed(analogRead(A0));
  
//  preparation();
  display.clearDisplay();
  delay(500);
  
  servo_movement("angkat", 0);
  
  servo_movement("putar", 0);
  default_state();
  delay(500);
  default_state();
  unsigned long timer=millis();
  int start_state;
  speed=800;
  delay(500);
  while(true){//untuk pameran
    Serial.println(digitalRead(A10));
//    Dynamixel.moveSpeed(3, 90,speed);
    if(digitalRead(A10) == HIGH){
      int rand_val = random(1,10);
      default_state();
      for(int i=0;i<4;i++){
        switch(rand_val){
          case 1:
            walk_fast();
            break;
          case 2:
            reverse_fast();
            break;
          case 3:
            turn_left_fast();
            break;
          case 4:
            turn_right_fast();
            break;
          case 5:
            crabwalk_left();
            break;
          case 6:
            crabwalk_right();
            break;
          case 7:
          case 8:
            myservo.write(82);
            delay(100);
            myservo.write(122);
            delay(100);
            myservo.write(102);
            delay(50);
            break;
          case 9:
            servo_movement("buka",1);
            servo_movement("angkat", 1);
            delay(200);
            servo_movement("angkat", 2);
            delay(200);
            servo_movement("buka", 2);
            delay(350);
            speed=100;
            servoAngkat.write(150);
            delay(400);
            servo_movement("buka",0);
            servo_movement("angkat", 0);
            delay(500);
            break;
        }
        if(rand_val == 9){
          break;
        }
      }
      delay(100);
      speed=800;
      default_state();
      delay(5000);
    }
    else{
      default_state();
      Serial.println("State Default");
      delay(500);
    }
  }
  
  digitalWrite(7, LOW);
  default_state();


}
