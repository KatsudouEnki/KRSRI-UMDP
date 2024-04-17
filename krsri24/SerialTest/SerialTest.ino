#define STX '\x02'
#define ETX '\x03'

String buff_serial;


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

void setup(){
  Serial.begin(115200);
  Serial2.begin(19200);

  buff_serial = "";

}
void loop(){
//  if(Serial2.available()){
//    Serial.write(Serial2.read());
//  }
  test();

}

void test(){
  if (Serial2.available()) {
    if (buff_serial.length() > 16) {
      buff_serial = "";
    }

//    Serial.println("Got data");

//    String rx_in = Serial2.readString();
String rx_in, dtx;
char chrx_in = Serial2.read();
    buff_serial += String(chrx_in);

//    Serial.println(buff_serial);

    // check header
    int pos_head = buff_serial.indexOf(STX);
    int pos_tail = buff_serial.indexOf(ETX);
    // Serial.printf("%d -- %d\n", pos_head, pos_tail);
    if ((pos_head > -1) && (pos_tail > -1)) {
      if (pos_head < pos_tail) {
        rx_in = buff_serial.substring(pos_head + 1, pos_tail);
//        if (rx_in.equals("1")) {
//          Serial.print(buff_serial);
//          relay_open();
//        }
        Serial.println(rx_in);

        dtx = get_value(rx_in,',',0);
        
        Serial.print("Status = "); Serial.println(dtx.toInt());

        dtx = get_value(rx_in,',',1);
        Serial.print("dx = "); Serial.println(dtx.toInt());

        dtx = get_value(rx_in,',',2);
        Serial.print("dy = "); Serial.println(dtx.toInt());
        
        buff_serial = "";
   }
}
}
}
