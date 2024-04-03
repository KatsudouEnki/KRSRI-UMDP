#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  float test_x= 8,
        test_y= 8,
        test_z= 2,
        
        default_x=8,
        default_y=8,
        default_z=4.5;
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(dynamixelGammaMid(test_x,test_y,test_z,0,0));
  Serial.println(dynamixelAlpha(test_x,test_y,test_z,0,0));
  Serial.println(dynamixelBeta(test_x,test_y,test_z,0,0));
  
  Serial.println(dynamixelGammaMid(default_x,default_y,default_z,0,0));
  Serial.println(dynamixelAlpha(default_x,default_y,default_z,0,0));
  Serial.println(dynamixelBeta(default_x,default_y,default_z,0,0));
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
//
//  Serial.print("gamma:");
//  Serial.print(gamma_cal(7,7,3));
//  Serial.print("\t beta:");
//  Serial.print(beta_cal(7,7,3));
//  Serial.print("\t Alpha:");
//  Serial.println(alpha_sum(7,7,3));
//
//  Serial.print("gamma:");
//  Serial.print(AngleCalc(gamma_cal(7,7,3),0));
//  Serial.print("\t beta:");
//  Serial.print(beta_cal(7,7,3));
//  Serial.print("\t Alpha:");
//  Serial.println(alpha_sum(7,7,3));
//  
//  Serial.print(AngleCalc(150,0));
}

void LeftFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
  display.setCursor(80,0);
  display.print("Depan");
  
  Dynamixel.moveSpeed(3, dynamixelGammaMid(x_val,y_val,z_val,0,0),speed);
  display.setCursor(80,8);
  display.print(dynamixelGammaMid(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(2, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
  display.setCursor(80,16);
  display.print(dynamixelAlpha(x_val,y_val,z_val,0,1));
  delay(servo_delay);

  Dynamixel.moveSpeed(1, dynamixelBeta(x_val,y_val,z_val,1,1), speed);
  display.setCursor(80,24);
  display.print(dynamixelBeta(x_val,y_val,z_val,1,1));
  delay(servo_delay);
}
void LeftMid(float x_val, float y_val,float z_val, int speed,int servo_delay){
  display.setCursor(40,0);
  display.print("MID");
  
  Dynamixel.moveSpeed(9, dynamixelGammaMid(x_val,y_val,z_val,0,0),speed);
  display.setCursor(40,8);
  display.print(dynamixelGammaMid(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(8, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
  display.setCursor(40,16);
  display.print(dynamixelAlpha(x_val,y_val,z_val,0,1));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(7, dynamixelBeta(x_val,y_val,z_val,1,1), speed);
  display.setCursor(40,24);
  display.print(dynamixelBeta(x_val,y_val,z_val,1,1));
  delay(servo_delay);
}
void LeftBack(float x_val, float y_val,float z_val, int speed,int servo_delay){
  display.setCursor(0,0);
  display.print("Back");
  
  Dynamixel.moveSpeed(15, dynamixelGamma(x_val,y_val,z_val,0,0), speed);
  display.setCursor(0,8);
  display.print(dynamixelGamma(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(14, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
  display.setCursor(0,16);
  display.print(dynamixelAlpha(x_val,y_val,z_val,0,1));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(13, dynamixelBeta(x_val,y_val,z_val,1,1), speed);
  display.setCursor(0,24);
  display.print(dynamixelBeta(x_val,y_val,z_val,1,1));
  delay(servo_delay);
}

void RightFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(4, dynamixelGamma(x_val,y_val,z_val,1,0),speed);
  display.setCursor(80,35);
  display.print(dynamixelGamma(x_val,y_val,z_val,1,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(5, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
  display.setCursor(80,43);
  display.print(dynamixelAlpha(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(6, dynamixelBeta(x_val,y_val,z_val,1,0), speed);
  display.setCursor(80,51);
  display.print(dynamixelBeta(x_val,y_val,z_val,1,0));
  delay(servo_delay);
}
void RightMid(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(10, dynamixelGammaMid(x_val,y_val,z_val,1,0),speed);
  display.setCursor(40,35);
  display.print(dynamixelGammaMid(x_val,y_val,z_val,1,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(11, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
  display.setCursor(40,43);
  display.print(dynamixelAlpha(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(12, dynamixelBeta(x_val,y_val,z_val,1,0), speed);
  display.setCursor(40,51);
  display.print(dynamixelBeta(x_val,y_val,z_val,1,0));
  delay(servo_delay);
}
void RightBack(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(16, dynamixelGammaMid(x_val,y_val,z_val,1,0),speed);
  display.setCursor(0,35);
  display.print(dynamixelGammaMid(x_val,y_val,z_val,1,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(17, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
  display.setCursor(0,43);
  display.print(dynamixelAlpha(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(18, dynamixelBeta(x_val,y_val,z_val,1,0), speed);
  display.setCursor(0,51);
  display.print(dynamixelBeta(x_val,y_val,z_val,1,0));
  delay(servo_delay);
}

int speed=400, servo_delay=1;

void default_state(){
  LeftFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
}

void walk(){
  //1
  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(3);

  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(12);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(15);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(3);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(12);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(15);
}

void walk_fast(){
  //1
  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(5);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  // delay(25);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);
  
  // delay(30);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  // delay(25);

  //4
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  // delay(30);
}

void walk_fast_obstacle(){
  //1
  RightFront(5,10,6.5,speed,servo_delay);
  LeftMid(5,10,6.5,speed,servo_delay);
  RightBack(5,10,6.5,speed,servo_delay);

  delay(40);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  delay(80);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,6.5,speed,servo_delay);
  LeftMid(10,5,6.5,speed,servo_delay);
  RightBack(10,5,6.5,speed,servo_delay);
  
  delay(120);

  //3
  LeftFront(5,10,6.5,speed,servo_delay);
  RightMid(5,10,6.5,speed,servo_delay);
  LeftBack(5,10,6.5,speed,servo_delay);

  delay(40);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(80);

  //4
  LeftFront(10,5,6.5,speed,servo_delay);
  RightMid(10,5,6.5,speed,servo_delay);
  LeftBack(10,5,6.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(120);
}

void walk_fast_balls(){
  //1
  RightFront(5,10,3.75,speed,servo_delay);
  LeftMid(5,10,3.75,speed,servo_delay);
  RightBack(5,10,3.75,speed,servo_delay);

  delay(20);

  LeftFront(10,5,2.5,speed,servo_delay);
  RightMid(10,5,2.5,speed,servo_delay);
  LeftBack(10,5,2.5,speed,servo_delay);

  delay(80);

  //2
  LeftFront(5,10,2.5,speed,servo_delay);
  RightMid(5,10,2.5,speed,servo_delay);
  LeftBack(5,10,2.5,speed,servo_delay);

  RightFront(10,5,3.75,speed,servo_delay);
  LeftMid(10,5,3.75,speed,servo_delay);
  RightBack(10,5,3.75,speed,servo_delay);

  delay(100);

  //3
  LeftFront(5,10,3.75,speed,servo_delay);
  RightMid(5,10,3.75,speed,servo_delay);
  LeftBack(5,10,3.75,speed,servo_delay);

  delay(20);

  RightFront(10,5,2.5,speed,servo_delay);
  LeftMid(10,5,2.5,speed,servo_delay);
  RightBack(10,5,2.5,speed,servo_delay);

  delay(80);

  //4
  LeftFront(10,5,3.75,speed,servo_delay);
  RightMid(10,5,3.75,speed,servo_delay);
  LeftBack(10,5,3.75,speed,servo_delay);

  RightFront(5,10,2.5,speed,servo_delay);
  LeftMid(5,10,2.5,speed,servo_delay);
  RightBack(5,10,2.5,speed,servo_delay);

  delay(100);
}

void reverse(){
  //1
  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(5);

  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(25);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(5);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(25);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(30);
}

void reverse_fast(){
  //1
  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(5);

  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  // delay(25);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);
  
  // delay(30);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(5);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  // delay(25);

  //4
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  // delay(30);
}

void turn_left(){
  //1
  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(5);

  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(25);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(5);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(25);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(30);
}

void turn_left_fast(){
  //1
  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(5);

  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  // delay(25);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);
  
  // delay(30);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  // delay(25);

  //4
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  // delay(30);
}

void turn_right(){
  //1
  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(5);

  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(25);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(5);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(25);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(30);
}

void turn_right_fast(){
  //1
  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(10);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  // delay(25);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);
  
  // delay(30);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(5);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  // delay(25);

  //4
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  // delay(30);
}

void crabwalk_left(){
  //1
  RightFront(8,5,4.5,speed,servo_delay);
  LeftMid(9.4,9.4,4.5,speed,servo_delay);
  RightBack(5,8,4.5,speed,servo_delay);

  delay(5);

  LeftFront(8,5,4,speed,servo_delay);
  RightMid(9.4,9.4,4,speed,servo_delay);
  LeftBack(5,8,4,speed,servo_delay);
  
  // delay(10);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  //lanjut ke x = 9, 10, 11, 12

  //2
  LeftFront(12,5,4,speed,servo_delay);
  RightMid(6.6,6.6,4,speed,servo_delay);
  LeftBack(5,12,4,speed,servo_delay);

  RightFront(12,5,4.5,speed,servo_delay);
  LeftMid(6.6,6.6,4.5,speed,servo_delay);
  RightBack(5,12,4.5,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(12,5,4.5,speed,servo_delay);
  RightMid(6.6,6.6,4.5,speed,servo_delay);
  LeftBack(5,12,4.5,speed,servo_delay);

  delay(5);

  RightFront(12,5,4,speed,servo_delay);
  LeftMid(6.6,6.6,4,speed,servo_delay);
  RightBack(5,12,4,speed,servo_delay);
  
  // delay(10);

  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  //4
  RightFront(8,5,3.5,speed,servo_delay);
  LeftMid(9.4,9.4,3.5,speed,servo_delay);
  RightBack(5,8,3.5,speed,servo_delay);

  LeftFront(8,5,4.5,speed,servo_delay);
  RightMid(9.4,9.4,4.5,speed,servo_delay);
  LeftBack(5,8,4.5,speed,servo_delay);
  
  // delay(20);
}

void crabwalk_right(){
  //1
  RightFront(12,5,4.5,speed,servo_delay);
  LeftMid(6.6,6.6,4.5,speed,servo_delay);
  RightBack(5,12,4.5,speed,servo_delay);

  delay(10);

  LeftFront(12,5,3.5,speed,servo_delay);
  RightMid(6.6,6.6,3.5,speed,servo_delay);
  LeftBack(5,12,3.5,speed,servo_delay);
  
  // delay(10);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  //2
  LeftFront(8,5,3.5,speed,servo_delay);
  RightMid(9.4,9.4,3.5,speed,servo_delay);
  LeftBack(5,8,3.5,speed,servo_delay);

  RightFront(8,5,4.5,speed,servo_delay);
  LeftMid(9.4,9.4,4.5,speed,servo_delay);
  RightBack(5,8,4.5,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(8,5,4.5,speed,servo_delay);
  RightMid(9.4,9.4,4.5,speed,servo_delay);
  LeftBack(5,8,4.5,speed,servo_delay);

  delay(10);

  RightFront(8,5,3.5,speed,servo_delay);
  LeftMid(9.4,9.4,3.5,speed,servo_delay);
  RightBack(5,8,3.5,speed,servo_delay);
  
  // delay(10);

  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  //4
  RightFront(12,5,3.5,speed,servo_delay);
  LeftMid(6.6,6.6,3.5,speed,servo_delay);
  RightBack(5,12,3.5,speed,servo_delay);

  LeftFront(12,5,4.5,speed,servo_delay);
  RightMid(6.6,6.6,4.5,speed,servo_delay);
  LeftBack(5,12,4.5,speed,servo_delay);
  
  // delay(20);
}
