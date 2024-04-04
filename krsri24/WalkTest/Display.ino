void data_display(){
  display.clearDisplay();
  display.setCursor(50,0);
  display.print("F=");
  display.print(front_dis);
  Serial.print(front_dis);
  Serial.print("\t");
  
  display.setCursor(0,32);
  display.print("L=");
  display.print(left_dis);
  Serial.print(left_dis);
  Serial.print("\t");
  
  display.setCursor(80,32);
  display.print("R=");
  display.print(right_dis);
  Serial.print(right_dis);
  Serial.print("\t");
  
  display.setCursor(50,50);
  display.print("B=");
  display.print(back_dis);
  Serial.println(back_dis);
  
  display.display();
}
