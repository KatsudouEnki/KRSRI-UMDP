/**
 * get value from string delimited by char
 * @method getValue
 * @param  data      the string input_string
 * @param  separator char separator data
 * @param  index     index data from 0
 * @return           string
 */
String get_value(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]):"";
}

void dummy_detection(){
  speed=200;
  int status_korban=0, rep=0;
  while(status_korban==0){
    if (Serial2.available()) {
      if (buff_serial.length() > 16) {
        buff_serial = "";
      }
      
      String rx_in, dtx, dty, dstate;
      char chrx_in = Serial2.read();
      buff_serial += String(chrx_in);
      // check header
      int pos_head = buff_serial.indexOf(STX);
      int pos_tail = buff_serial.indexOf(ETX);
      // Serial.printf("%d -- %d\n", pos_head, pos_tail);
      if ((pos_head > -1) && (pos_tail > -1)) {
        if (pos_head < pos_tail) {
          rx_in = buff_serial.substring(pos_head + 1, pos_tail);
          Serial.println(rx_in);
  
  //        dtx = get_value(rx_in,',',0);
          dstate = get_value(rx_in,',',0);
          Serial.print("Status = "); Serial.println(dstate);
          display.setCursor(10,10);
          display.print(dstate);
          display.display();
  
          dtx = get_value(rx_in,',',1);
  
          if(dtx.toInt()>=-70 && dtx.toInt()<=70 && dstate.toInt()==1){
            servo_movement("buka",1);
            walk_to_victim();

            distance_detection();
            if(back_dis>17 || dty.toInt()>350){
              servo_movement("angkat", 1);
              walk_to_victim();
              walk_to_victim();
              delay(200);
              servo_movement("buka", 2);
              delay(800);
//              servo_movement("angkat", 3);
              delay(250);
              speed=100;
              servoAngkat.write(180);
              reverse_fast();
              delay(600);
              servo_movement("angkat", 0);
              status_korban=1;
            }
            
            myservo.write(pos);
            Serial.print("pos = "); Serial.println(pos);
          }
          else if(dtx.toInt()<=-70 && dstate.toInt()==1){
            servo_movement("buka",1);
            pos=pos-1;
             if(pos<=82){
               turn_left_slow();
               pos = 92;
             }
            myservo.write(pos);
            } 
          else if(dtx.toInt()>=70 && dstate.toInt()==1){
            servo_movement("buka",1);
            pos=pos+1;
             if(pos>=122){
               turn_right_slow();
               pos=112;
             }
            myservo.write(pos);
          }
          else{
            pos=pos+1;
            if(pos>=122){
              pos=82;
              rep++;
              if(rep>5){
                status_korban=1;
              }
            }
            Serial.println(myservo.read());
            myservo.write(pos);
          }
          delay(10);
          //////////////////////////////////////////////////////////////////// pakai sensor jarak atau koordinat Y dari kamera
          buff_serial = "";
        }
      }
    }
  }
}

void dummy_detection2(){
  speed=200;
  int status_korban=0, rep=0;
  while(status_korban==0){
    if (Serial2.available()) {
      if (buff_serial.length() > 16) {
        buff_serial = "";
      }
      
      String rx_in, dtx, dty, dstate;
      char chrx_in = Serial2.read();
      buff_serial += String(chrx_in);
      // check header
      int pos_head = buff_serial.indexOf(STX);
      int pos_tail = buff_serial.indexOf(ETX);
      if ((pos_head > -1) && (pos_tail > -1)) {
        if (pos_head < pos_tail) {
          rx_in = buff_serial.substring(pos_head + 1, pos_tail);
          Serial.println(rx_in);

          dstate = get_value(rx_in,',',0);
          Serial.print("Status = "); Serial.println(dstate);
          display.setCursor(10,10);
          display.print(dstate);
          display.display();
  
          dtx = get_value(rx_in,',',1);
  
          if(dtx.toInt()>=-70 && dtx.toInt()<=70 && dstate.toInt()==1){
//            servo_movement("buka",4);
            walk_to_victim_obstacle();

            distance_detection();
            if(back_dis>19 || dty.toInt()>325){
              // default_state();
              servo_movement("angkat", 5);
              servo_movement("angkat", 7);
              servo_movement("buka", 2);
              delay(800);
              servo_movement("angkat", 6);
              delay(250);
              speed=100;
              reverse_fast();
              servo_movement("buka", 2);
              delay(600);
              servo_movement("angkat", 0);
              status_korban=1;
            }
            
            myservo.write(pos);
            Serial.print("pos = "); Serial.println(pos);
          }
          else if(dtx.toInt()<=-70 && dstate.toInt()==1){
            servo_movement("buka",4);
            pos=pos-1;
             if(pos<82){
               turn_left_slow();
               pos = 92;
             }
            myservo.write(pos);
            } 
          else if(dtx.toInt()>=70 && dstate.toInt()==1){
            servo_movement("buka",4);
            pos=pos+1;
             if(pos>=122){
               turn_right_slow();
               pos=112;
             }
            myservo.write(pos);
          }
          else{
            pos=pos-1;
            if(pos<=82){
              while(pos<=122){
                pos=pos+10;
                myservo.write(pos);
                delay(20);
              }
              rep++;
              if(rep>2){
                reverse_fast_obstacle();
                delay(100);
                default_state();
                servo_movement("angkat", 5);
              }
              if(rep>5){
                status_korban=1;
              }
            }
            myservo.write(pos);
            delay(10);
          }
          delay(150);
          buff_serial = "";
        }
      }
    }
  }
}

void dummy_detection3(){
  speed=200;
  int status_korban=0, rep=0;
  while(status_korban==0){
    if (Serial2.available()) {
      if (buff_serial.length() > 16) {
        buff_serial = "";
      }
      
      String rx_in, dtx, dty, dstate;
      char chrx_in = Serial2.read();
      buff_serial += String(chrx_in);
      // check header
      int pos_head = buff_serial.indexOf(STX);
      int pos_tail = buff_serial.indexOf(ETX);
      if ((pos_head > -1) && (pos_tail > -1)) {
        if (pos_head < pos_tail) {
          rx_in = buff_serial.substring(pos_head + 1, pos_tail);
          Serial.println(rx_in);

          dstate = get_value(rx_in,',',0);
          Serial.print("Status = "); Serial.println(dstate);
          display.setCursor(10,10);
          display.print(dstate);
          display.display();
  
          dtx = get_value(rx_in,',',1);
  
          if(dtx.toInt()>=-70 && dtx.toInt()<=70 && dstate.toInt()==1){
            
            walk_to_victim_obstacle();

            distance_detection();
            if(back_dis>35 || dty.toInt()>375){
              // default_state();
              servo_movement("angkat", 5);
              walk_to_victim_obstacle();
              walk_to_victim_obstacle();
              servo_movement("buka",4);
              servo_movement("angkat", 7);
              servo_movement("buka", 2);
              delay(800);
              servo_movement("angkat", 6);
              delay(250);
              speed=100;
              reverse_fast_obstacle();
              servo_movement("buka", 2);
              delay(600);
              servo_movement("angkat", 0);
              status_korban=1;
              speed=800;
            }
            
            myservo.write(pos);
            Serial.print("pos = "); Serial.println(pos);
          }
          else if(dtx.toInt()<=-70 && dstate.toInt()==1){
            servo_movement("buka",4);
            pos=pos-1;
            // if(pos<72){
            //   pos=72;
            // }
            myservo.write(pos);
            } 
          else if(dtx.toInt()>=70 && dstate.toInt()==1){
            servo_movement("buka",4);
            pos=pos+1;
            // if(pos>=122){
            //   pos=132;
            // }
            myservo.write(pos);
          }
          else{
            pos=pos-1;
            if(pos<=82){
              while(pos<=122){
                pos=pos+10;
                myservo.write(pos);
                delay(20);
              }
              rep++;
//              if(rep>2){
//                reverse_fast_obstacle();
//                delay(100);
//                default_state();
//                servo_movement("angkat", 5);
//              }
              if(rep>5){
                status_korban=1;
              }
            }
            myservo.write(pos);
            delay(10);
          }
          delay(50);
          buff_serial = "";
        }
      }
    }
  }
}
