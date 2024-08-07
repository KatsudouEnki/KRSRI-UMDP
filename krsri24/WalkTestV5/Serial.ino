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
  //        Serial.print("Status = "); Serial.println(dtx.toInt());
  
          dtx = get_value(rx_in,',',1);
          // Serial.print("dx = "); Serial.println(dtx.toInt());
          dty = get_value(rx_in,',',2);
          if(dtx.toInt()>=-70 && dtx.toInt()<=70 && dstate.toInt()==1){
            servo_movement("buka",1);
            walk_to_victim();

            distance_detection();
//            if(back_dis>17){//////dy>350
            if(dty.toInt()>=350){//////dy>350
              servo_movement("angkat", 2);
//              walk_to_victim();
              delay(200);
              servo_movement("buka", 2);
              delay(400);
              speed=100;
              reverse_fast();
              delay(300);
              servo_movement("angkat", 0);
              status_korban=1;
            }
            myservo.write(pos);
            Serial.print("pos = "); Serial.println(pos);
          }
          else if(dtx.toInt()<=-70 && dstate.toInt()==1){
            pos=pos-1;
            myservo.write(pos);
            } 
          else if(dtx.toInt()>=70 && dstate.toInt()==1){
            pos=pos+1;
            myservo.write(pos);
          }
          else{
            pos=pos+1;
            servo_movement("buka", 0);
            if(pos>=130){
              pos=70;
              rep++;
              if(rep>10){
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
  
//  if (Serial2.available()) {
//    if (buff_serial.length() > 16) {
//      buff_serial = "";
//    }
//    
//    String rx_in, dtx, dstate;
//    char chrx_in = Serial2.read();
//    buff_serial += String(chrx_in);
//    // check header
//    int pos_head = buff_serial.indexOf(STX);
//    int pos_tail = buff_serial.indexOf(ETX);
//    // Serial.printf("%d -- %d\n", pos_head, pos_tail);
//    if ((pos_head > -1) && (pos_tail > -1)) {
//      if (pos_head < pos_tail) {
//        rx_in = buff_serial.substring(pos_head + 1, pos_tail);
//        Serial.println(rx_in);
//
////        dtx = get_value(rx_in,',',0);
//        dstate = get_value(rx_in,',',0);
//        Serial.print("Status = "); Serial.println(dstate);
//        display.setCursor(10,10);
//        display.print(dstate);
//        display.display();
////        Serial.print("Status = "); Serial.println(dtx.toInt());
//
//        dtx = get_value(rx_in,',',1);
//        // Serial.print("dx = "); Serial.println(dtx.toInt());
//
//        
//        buff_serial = "";
//      }
//    }
//  }
}
