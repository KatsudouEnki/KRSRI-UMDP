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
  if (Serial2.available()) {
    if (buff_serial.length() > 16) {
      buff_serial = "";
    }
    
    String rx_in, dtx, dstate;
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

        if(dtx.toInt()>=-70 && dtx.toInt()<=70 && dstate.toInt()==1){
          servoBuka.write(90);
          walk_to_victim();
//          delay(1000);
//          servoBuka.write(0);
//          delay(1000);
        
          myservo.write(pos);
          Serial.print("pos = "); Serial.println(pos);
        }
        else if(dtx.toInt()<=-70 && dstate.toInt()==1){
          pos=pos-1;
//          servoBuka.write(0);
          myservo.write(pos);
          } 
        else if(dtx.toInt()>=70 && dstate.toInt()==1){
          pos=pos+1;
//          servoBuka.write(0);
          myservo.write(pos);
        }
        else{
          pos=pos+1;
          servoBuka.write(0);
          if(pos>=150){
            pos=90;
          }
          Serial.println(myservo.read());
          myservo.write(pos);
        }
        //////////////////////////////////////////////////////////////////// pakai sensor jarak atau koordinat Y dari kamera
        

//        dstate = get_value(rx_in,',',0);
//        Serial.print("position = ");
//        Serial.println(myservo.read());
//        
//        if(dstate.toInt()==1 && dtx.toInt()<=70 && dtx.toInt()>=-70 && myservo.read()<=95 && myservo.read()>=85){
//          servoBuka.write(90);
//          walk_to_victim();
//        }
//        else if(dstate.toInt()==1 && dtx.toInt()<=70 && dtx.toInt()>=-70 && myservo.read()<85){
//          crabwalk_left();
//          delay(100);
//        }
//        else if(dstate.toInt()==1 && dtx.toInt()<=70 && dtx.toInt()>=-70 && myservo.read()>95){
//          crabwalk_right_test();
//          delay(100);
//        }
//        else{
//          cam_state();
//          servoBuka.write(0);
//        }
//        
        
        buff_serial = "";
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
