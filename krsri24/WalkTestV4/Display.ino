void data_display(){
  display.clearDisplay();
  lcd.clear();
  display.setCursor(50,0);
  display.print("F=");
  display.print(front_dis);
  Serial.print("F=");
  Serial.print(front_dis);
  Serial.print("\t");
//  lcd.setCursor(0,0);
//  lcd.write("F=");
//  lcd.write(front_dis);
//  
  display.setCursor(0,32);
  display.print("L=");
  display.print(left_dis);
  Serial.print("L=");
  Serial.print(left_dis);
  Serial.print("\t");
//  lcd.setCursor(0,1);
//  lcd.write("L=");
//  lcd.write(left_dis);
//  
  display.setCursor(80,32);
  display.print("R=");
  display.print(right_dis);
  Serial.print("R=");
  Serial.print(right_dis);
  Serial.print("\t");
//  lcd.setCursor(8,0);
//  lcd.write("R=");
//  lcd.write(right_dis);
//  
  display.setCursor(50,50);
  display.print("B=");
  display.print(back_dis);
  Serial.print("B=");
  Serial.println(back_dis);
//  lcd.setCursor(8,1);
//  lcd.write("B=");
//  lcd.write(back_dis);
//  
  display.display();
//  lcd.display();
}
