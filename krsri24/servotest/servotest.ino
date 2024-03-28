#include <Wire.h>
#include <DynamixelSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define plus_button 5
#define minus_button 6
int pot1, id=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Dynamixel.setSerial(&Serial);
//  Dynamixel.setSerial(&Serial1);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  displaySetup();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  int del=100;

  if(digitalRead(plus_button)==HIGH && digitalRead(minus_button)==LOW){
    id++;
    delay(del);
  } 
  else if(digitalRead(plus_button)==LOW && digitalRead(minus_button)==HIGH){
    id--;
    delay(del);
  }
  else{
    id=id;
    delay(del);
  }

  display.setCursor(55,0);             // Start at top-left corner
  display.clearDisplay();
  display.print(id);
  display.display();
  Serial.print(id);
  pot1=analogRead(A0);
  
  display.setCursor(55,15);             // Start at top-left corner
  display.print(pot1);
  Serial.print("\t");
  Serial.println(pot1);
  display.display();
  
  Dynamixel.moveSpeed(id, pot1,500);
  
}


void displaySetup(){
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
}
