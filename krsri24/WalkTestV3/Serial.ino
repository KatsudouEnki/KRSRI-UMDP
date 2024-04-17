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
  if (Serial2.available()) {
    if (buff_serial.length() > 16) {
      buff_serial = "";
    }
    String rx_in, dtx;
    char chrx_in = Serial2.read();
    buff_serial += String(chrx_in);
    
    int pos_head = buff_serial.indexOf(STX);
    int pos_tail = buff_serial.indexOf(ETX);
    if ((pos_head > -1) && (pos_tail > -1)) {
      if (pos_head < pos_tail) {
        rx_in = buff_serial.substring(pos_head + 1, pos_tail);
        Serial.println(rx_in);
        
        dtx = get_value(rx_in,',',0);
        dummy_state = get_value(rx_in,',',0).toInt();
//        Serial.print("Status = "); Serial.println(dtx);
        
        dtx = get_value(rx_in,',',1);
        dummy_x_coor = get_value(rx_in,',',1).toInt();
//        Serial.print("dx = "); Serial.println(dtx);
        
        dtx = get_value(rx_in,',',2);
        dummy_y_coor = get_value(rx_in,',',2).toInt();
//        Serial.print("dy = "); Serial.println(dtx);
        
        buff_serial = "";
      }
    }
  }
}
