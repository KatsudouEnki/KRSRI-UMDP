#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#include <MechaQMC5883.h>

MechaQMC5883 qmc;

#define STX '\x02'
#define ETX '\x03'


#define CMPS12_ADDRESS 0x60  // Address of CMPS12 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;

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

#define SONAR_NUM 4      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(42, 42, MAX_DISTANCE),  // Depan
  NewPing(34, 34, MAX_DISTANCE),  // Belakang
  NewPing(32, 32, MAX_DISTANCE),  // Kiri
  NewPing(36, 36, MAX_DISTANCE)   // Kanan
};
 

int left_dis,
    right_dis,
    front_dis,
    back_dis;

Servo myservo;  // create servo object to control a servo
Servo servoAngkat;
Servo servoBuka;
// twelve servo objects can be created on most boards

int pos =90;

//Camera Comm
int dummy_x_coor,
    dummy_y_coor,
    dummy_state;
#define STX '\x02'
#define ETX '\x03'

int x_axis, y_axis, z_axis;
int azimuth;
String buff_serial;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(19200);
  
  Dynamixel.setSerial(&Serial3);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  lcd.init();lcd.backlight();
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
  display.setTextSize(4);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text

  myservo.attach(31);
  servoAngkat.attach(29);
  servoBuka.attach(27);
  Wire.begin();

  buff_serial = "";
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(7,OUTPUT);
}

void LeftFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
  display.setCursor(80,0);
  display.print("Depan");
  
  Dynamixel.moveSpeed(3, dynamixelGammaMid(x_val,y_val,z_val,0,0),speed);
  display.setCursor(80,8);
  display.print(dynamixelGammaLFRB(x_val,y_val,z_val,0,0));
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
  display.print(dynamixelGammaLFRB(x_val,y_val,z_val,1,0));
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

int speed=600, servo_delay=0;

void default_state(){
  LeftFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
}

void cam_state(){
  LeftFront(8,8,6,speed,servo_delay);
  LeftMid(8,8,6,speed,servo_delay);
  LeftBack(8,8,6,speed,servo_delay);

  RightFront(8,8,6,speed,servo_delay);
  RightMid(8,8,6,speed,servo_delay);
  RightBack(8,8,6,speed,servo_delay);
  servoAngkat.write(0);
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

  delay(20);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  delay(60);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,6.5,speed,servo_delay);
  LeftMid(10,5,6.5,speed,servo_delay);
  RightBack(10,5,6.5,speed,servo_delay);
  
  delay(80);

  //3
  LeftFront(5,10,6.5,speed,servo_delay);
  RightMid(5,10,6.5,speed,servo_delay);
  LeftBack(5,10,6.5,speed,servo_delay);

  delay(20);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(60);

  //4
  LeftFront(10,5,6.5,speed,servo_delay);
  RightMid(10,5,6.5,speed,servo_delay);
  LeftBack(10,5,6.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(80);
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

void turn_left_slow(){
  //1
  RightFront(7.25,8.75,4.5,speed,servo_delay);
  LeftMid(8.75,7.25,4.5,speed,servo_delay);
  RightBack(7.25,8.75,4.5,speed,servo_delay);

  delay(5);

  LeftFront(7.25,8.75,3,speed,servo_delay);
  RightMid(8.75,7.25,3,speed,servo_delay);
  LeftBack(7.25,8.75,3,speed,servo_delay);

  //delay(25);

  //2
  LeftFront(8.75,7.25,3,speed,servo_delay);
  RightMid(7.25,8.75,3,speed,servo_delay);
  LeftBack(8.75,7.25,3,speed,servo_delay);

  RightFront(8.75,7.25,4.5,speed,servo_delay);
  LeftMid(7.25,8.75,4.5,speed,servo_delay);
  RightBack(8.75,7.25,4.5,speed,servo_delay);
  
  //delay(30);

  //3
  LeftFront(8.75,7.25,4.5,speed,servo_delay);
  RightMid(7.25,8.75,4.5,speed,servo_delay);
  LeftBack(8.75,7.25,4.5,speed,servo_delay);

  delay(5);

  RightFront(8.75,7.25,3,speed,servo_delay);
  LeftMid(7.25,8.75,3,speed,servo_delay);
  RightBack(8.75,7.25,3,speed,servo_delay);
  
  //delay(25);

  //4
  LeftFront(7.25,8.75,4.5,speed,servo_delay);
  RightMid(8.75,7.25,4.5,speed,servo_delay);
  LeftBack(7.25,8.75,4.5,speed,servo_delay);

  RightFront(7.25,8.75,3,speed,servo_delay);
  LeftMid(8.75,7.25,3,speed,servo_delay);
  RightBack(7.25,8.75,3,speed,servo_delay);
  
  //delay(30);
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

void turn_left_obstacle(){
  //1
  RightFront(7.25,8.75,6.5,speed,servo_delay);
  LeftMid(8.75,7.25,6.5,speed,servo_delay);
  RightBack(7.25,8.75,6.5,speed,servo_delay);

  delay(10);

  LeftFront(7.25,8.75,3.5,speed,servo_delay);
  RightMid(8.75,7.25,3.5,speed,servo_delay);
  LeftBack(7.25,8.75,3.5,speed,servo_delay);

  delay(10);

  //2
  LeftFront(8.75,7.25,3.5,speed,servo_delay);
  RightMid(7.25,8.75,3.5,speed,servo_delay);
  LeftBack(8.75,7.25,3.5,speed,servo_delay);

  RightFront(8.75,7.25,6.5,speed,servo_delay);
  LeftMid(7.25,8.75,6.5,speed,servo_delay);
  RightBack(8.75,7.25,6.5,speed,servo_delay);
  
  delay(20);

  //3
  LeftFront(8.75,7.25,6.5,speed,servo_delay);
  RightMid(7.25,8.75,6.5,speed,servo_delay);
  LeftBack(8.75,7.25,6.5,speed,servo_delay);

  delay(10);

  RightFront(8.75,7.25,3.5,speed,servo_delay);
  LeftMid(7.25,8.75,3.5,speed,servo_delay);
  RightBack(8.75,7.25,3.5,speed,servo_delay);
  
  delay(10);

  //4
  LeftFront(7.25,8.75,6.5,speed,servo_delay);
  RightMid(8.75,7.25,6.5,speed,servo_delay);
  LeftBack(7.25,8.75,6.5,speed,servo_delay);

  RightFront(7.25,8.75,3.5,speed,servo_delay);
  LeftMid(8.75,7.25,3.5,speed,servo_delay);
  RightBack(7.25,8.75,3.5,speed,servo_delay);
  
  delay(20);
}

void turn_right_slow(){
  //1
  RightFront(8.75,7.25,4.5,speed,servo_delay);
  LeftMid(7.25,8.75,4.5,speed,servo_delay);
  RightBack(8.75,7.25,4.5,speed,servo_delay);

  delay(5);

  LeftFront(8.75,7.25,3,speed,servo_delay);
  RightMid(7.25,8.75,3,speed,servo_delay);
  LeftBack(8.75,7.25,3,speed,servo_delay);

  //delay(25);

  //2
  LeftFront(7.25,8.75,3,speed,servo_delay);
  RightMid(8.75,7.25,3,speed,servo_delay);
  LeftBack(7.25,8.75,3,speed,servo_delay);

  RightFront(7.25,8.75,4.5,speed,servo_delay);
  LeftMid(8.75,7.25,4.5,speed,servo_delay);
  RightBack(7.25,8.75,4.5,speed,servo_delay);
  
  //delay(30);

  //3
  LeftFront(7.25,8.75,4.5,speed,servo_delay);
  RightMid(8.75,7.25,4.5,speed,servo_delay);
  LeftBack(7.25,8.75,4.5,speed,servo_delay);

  delay(5);

  RightFront(7.25,8.75,3,speed,servo_delay);
  LeftMid(8.75,7.25,3,speed,servo_delay);
  RightBack(7.25,8.75,3,speed,servo_delay);
  
  //delay(25);

  //4
  LeftFront(8.75,7.25,4.5,speed,servo_delay);
  RightMid(7.25,8.75,4.5,speed,servo_delay);
  LeftBack(8.75,7.25,4.5,speed,servo_delay);

  RightFront(8.75,7.25,3,speed,servo_delay);
  LeftMid(7.25,8.75,3,speed,servo_delay);
  RightBack(8.75,7.25,3,speed,servo_delay);
  
  //delay(30);
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

void turn_right_obstacle(){
  //1
  RightFront(8.75,7.25,6.5,speed,servo_delay);
  LeftMid(7.25,8.75,6.5,speed,servo_delay);
  RightBack(8.75,7.25,6.5,speed,servo_delay);

  delay(10);

  LeftFront(8.75,7.25,3.5,speed,servo_delay);
  RightMid(7.25,8.75,3.5,speed,servo_delay);
  LeftBack(8.75,7.25,3.5,speed,servo_delay);

  delay(10);

  //2
  LeftFront(7.25,8.75,3.5,speed,servo_delay);
  RightMid(8.75,7.25,3.5,speed,servo_delay);
  LeftBack(7.25,8.75,3.5,speed,servo_delay);

  RightFront(7.25,8.75,6.5,speed,servo_delay);
  LeftMid(8.75,7.25,6.5,speed,servo_delay);
  RightBack(7.25,8.75,6.5,speed,servo_delay);
  
  delay(20);

  //3
  LeftFront(7.25,8.75,6.5,speed,servo_delay);
  RightMid(8.75,7.25,6.5,speed,servo_delay);
  LeftBack(7.25,8.75,6.5,speed,servo_delay);

  delay(10);

  RightFront(7.25,8.75,3.5,speed,servo_delay);
  LeftMid(8.75,7.25,3.5,speed,servo_delay);
  RightBack(7.25,8.75,3.5,speed,servo_delay);
  
  delay(10);

  //4
  LeftFront(8.75,7.25,6.5,speed,servo_delay);
  RightMid(7.25,8.75,6.5,speed,servo_delay);
  LeftBack(8.75,7.25,6.5,speed,servo_delay);

  RightFront(8.75,7.25,3.5,speed,servo_delay);
  LeftMid(7.25,8.75,3.5,speed,servo_delay);
  RightBack(8.75,7.25,3.5,speed,servo_delay);
  
  delay(20);
}

// void crabwalk_left(){
//   //1
//   RightFront(8,5,4.5,speed,servo_delay);
//   LeftMid(9.4,9.4,4.5,speed,servo_delay);
//   RightBack(5,8,4.5,speed,servo_delay);

//   delay(5);

//   LeftFront(8,5,4,speed,servo_delay);
//   RightMid(9.4,9.4,4,speed,servo_delay);
//   LeftBack(5,8,4,speed,servo_delay);
  
//   // delay(10);

//   RightFront(10,5,4.5,speed,servo_delay);
//   LeftMid(8,8,4.5,speed,servo_delay);
//   RightBack(5,10,4.5,speed,servo_delay);

//   //2
//   LeftFront(12,5,4,speed,servo_delay);
//   RightMid(6.6,6.6,4,speed,servo_delay);
//   LeftBack(5,12,4,speed,servo_delay);

//   RightFront(12,5,4.5,speed,servo_delay);
//   LeftMid(6.6,6.6,4.5,speed,servo_delay);
//   RightBack(5,12,4.5,speed,servo_delay);

//   // delay(20);

//   //3
//   LeftFront(12,5,4.5,speed,servo_delay);
//   RightMid(6.6,6.6,4.5,speed,servo_delay);
//   LeftBack(5,12,4.5,speed,servo_delay);

//   delay(5);

//   RightFront(12,5,4,speed,servo_delay);
//   LeftMid(6.6,6.6,4,speed,servo_delay);
//   RightBack(5,12,4,speed,servo_delay);
  
//   // delay(10);

//   LeftFront(10,5,4.5,speed,servo_delay);
//   RightMid(8,8,4.5,speed,servo_delay);
//   LeftBack(5,10,4.5,speed,servo_delay);

//   //4
//   RightFront(8,5,4,speed,servo_delay);
//   LeftMid(9.4,9.4,4,speed,servo_delay);
//   RightBack(5,8,4,speed,servo_delay);

//   LeftFront(8,5,4.5,speed,servo_delay);
//   RightMid(9.4,9.4,4.5,speed,servo_delay);
//   LeftBack(5,8,4.5,speed,servo_delay);
  
//   // delay(20);
// }

void crabwalk_left(){
  //1
  RightFront(8,5,4,speed,servo_delay);
  LeftMid(9.4,9.4,4,speed,servo_delay);
  RightBack(5,8,4,speed,servo_delay);

  delay(5);

  LeftFront(8,5,3,speed,servo_delay);
  RightMid(9.4,9.4,3,speed,servo_delay);
  LeftBack(5,8,3,speed,servo_delay);
  
  // delay(10);

  // RightFront(9,5,4,speed,servo_delay);
  // LeftMid(8.7,8.7,4,speed,servo_delay);
  // RightBack(5,9,4,speed,servo_delay);

  LeftFront(12,5,3,speed,servo_delay);
  RightMid(6.6,6.6,3,speed,servo_delay);
  LeftBack(5,12,3,speed,servo_delay);
  
  RightFront(10,5,4,speed,servo_delay);
  LeftMid(8,8,4,speed,servo_delay);
  RightBack(5,10,4,speed,servo_delay);

  // RightFront(11,5,4,speed,servo_delay);
  // LeftMid(7.3,7.3,4,speed,servo_delay);
  // RightBack(5,11,4,speed,servo_delay);

  //2
  // LeftFront(12,5,3,speed,servo_delay);
  // RightMid(6.6,6.6,3,speed,servo_delay);
  // LeftBack(5,12,3,speed,servo_delay);

  RightFront(12,5,4,speed,servo_delay);
  LeftMid(6.6,6.6,4,speed,servo_delay);
  RightBack(5,12,4,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(12,5,4,speed,servo_delay);
  RightMid(6.6,6.6,4,speed,servo_delay);
  LeftBack(5,12,4,speed,servo_delay);

  delay(5);

  RightFront(12,5,3,speed,servo_delay);
  LeftMid(6.6,6.6,3,speed,servo_delay);
  RightBack(5,12,3,speed,servo_delay);
  
  // delay(10);

  // LeftFront(11,5,4,speed,servo_delay);
  // RightMid(7.3,7.3,4,speed,servo_delay);
  // LeftBack(5,11,4,speed,servo_delay);

  RightFront(8,5,3,speed,servo_delay);
  LeftMid(9.4,9.4,3,speed,servo_delay);
  RightBack(5,8,3,speed,servo_delay);

  LeftFront(10,5,4,speed,servo_delay);
  RightMid(8,8,4,speed,servo_delay);
  LeftBack(5,10,4,speed,servo_delay);

  // LeftFront(9,5,4,speed,servo_delay);
  // RightMid(8.7,8.7,4,speed,servo_delay);
  // LeftBack(5,9,4,speed,servo_delay);

  //4
  // RightFront(8,5,3,speed,servo_delay);
  // LeftMid(9.4,9.4,3,speed,servo_delay);
  // RightBack(5,8,3,speed,servo_delay);

  LeftFront(8,5,4,speed,servo_delay);
  RightMid(9.4,9.4,4,speed,servo_delay);
  LeftBack(5,8,4,speed,servo_delay);
  
  // delay(20);
}

void crabwalk_left_obstacle(){
  //1
  RightFront(8,5,6,speed,servo_delay);
  LeftMid(9.4,9.4,6,speed,servo_delay);
  RightBack(5,8,6,speed,servo_delay);

  delay(5);

  LeftFront(8,5,3,speed,servo_delay);
  RightMid(9.4,9.4,3,speed,servo_delay);
  LeftBack(5,8,3,speed,servo_delay);
  
  // delay(10);

  // RightFront(9,5,6,speed,servo_delay);
  // LeftMid(8.7,8.7,6,speed,servo_delay);
  // RightBack(5,9,6,speed,servo_delay);

  LeftFront(12,5,3,speed,servo_delay);
  RightMid(6.6,6.6,3,speed,servo_delay);
  LeftBack(5,12,3,speed,servo_delay);

  RightFront(10,5,6,speed,servo_delay);
  LeftMid(8,8,6,speed,servo_delay);
  RightBack(5,10,6,speed,servo_delay);

  // RightFront(11,5,6,speed,servo_delay);
  // LeftMid(7.3,7.3,6,speed,servo_delay);
  // RightBack(5,11,6,speed,servo_delay);

  //2
  // LeftFront(12,5,3,speed,servo_delay);
  // RightMid(6.6,6.6,3,speed,servo_delay);
  // LeftBack(5,12,3,speed,servo_delay);

  RightFront(12,5,6,speed,servo_delay);
  LeftMid(6.6,6.6,6,speed,servo_delay);
  RightBack(5,12,6,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(12,5,6,speed,servo_delay);
  RightMid(6.6,6.6,6,speed,servo_delay);
  LeftBack(5,12,6,speed,servo_delay);

  delay(5);

  RightFront(12,5,3,speed,servo_delay);
  LeftMid(6.6,6.6,3,speed,servo_delay);
  RightBack(5,12,3,speed,servo_delay);
  
  // delay(10);

  // LeftFront(11,5,6,speed,servo_delay);
  // RightMid(7.3,7.3,6,speed,servo_delay);
  // LeftBack(5,11,6,speed,servo_delay);

  RightFront(8,5,3,speed,servo_delay);
  LeftMid(9.4,9.4,3,speed,servo_delay);
  RightBack(5,8,3,speed,servo_delay);

  LeftFront(10,5,6,speed,servo_delay);
  RightMid(8,8,6,speed,servo_delay);
  LeftBack(5,10,6,speed,servo_delay);

  // LeftFront(9,5,6,speed,servo_delay);
  // RightMid(8.7,8.7,6,speed,servo_delay);
  // LeftBack(5,9,6,speed,servo_delay);

  //4
  // RightFront(8,5,3,speed,servo_delay);
  // LeftMid(9.4,9.4,3,speed,servo_delay);
  // RightBack(5,8,3,speed,servo_delay);

  LeftFront(8,5,6,speed,servo_delay);
  RightMid(9.4,9.4,6,speed,servo_delay);
  LeftBack(5,8,6,speed,servo_delay);
  
  // delay(20);
}

// void crabwalk_right(){
//   //1
//   RightFront(12,5,4.5,speed,servo_delay);
//   LeftMid(6.6,6.6,4.5,speed,servo_delay);
//   RightBack(5,12,4.5,speed,servo_delay);

//   delay(10);

//   LeftFront(12,5,3.5,speed,servo_delay);
//   RightMid(6.6,6.6,3.5,speed,servo_delay);
//   LeftBack(5,12,3.5,speed,servo_delay);
  
//   // delay(10);

//   RightFront(10,5,4.5,speed,servo_delay);
//   LeftMid(8,8,4.5,speed,servo_delay);
//   RightBack(5,10,4.5,speed,servo_delay);

//   //2
//   LeftFront(8,5,3.5,speed,servo_delay);
//   RightMid(9.4,9.4,3.5,speed,servo_delay);
//   LeftBack(5,8,3.5,speed,servo_delay);

//   RightFront(8,5,4.5,speed,servo_delay);
//   LeftMid(9.4,9.4,4.5,speed,servo_delay);
//   RightBack(5,8,4.5,speed,servo_delay);

//   // delay(20);

//   //3
//   LeftFront(8,5,4.5,speed,servo_delay);
//   RightMid(9.4,9.4,4.5,speed,servo_delay);
//   LeftBack(5,8,4.5,speed,servo_delay);

//   delay(10);

//   RightFront(8,5,3.5,speed,servo_delay);
//   LeftMid(9.4,9.4,3.5,speed,servo_delay);
//   RightBack(5,8,3.5,speed,servo_delay);
  
//   // delay(10);

//   LeftFront(10,5,4.5,speed,servo_delay);
//   RightMid(8,8,4.5,speed,servo_delay);
//   LeftBack(5,10,4.5,speed,servo_delay);

//   //4
//   RightFront(12,5,3.5,speed,servo_delay);
//   LeftMid(6.6,6.6,3.5,speed,servo_delay);
//   RightBack(5,12,3.5,speed,servo_delay);

//   LeftFront(12,5,4.5,speed,servo_delay);
//   RightMid(6.6,6.6,4.5,speed,servo_delay);
//   LeftBack(5,12,4.5,speed,servo_delay);
  
//   // delay(20);
// }

void crabwalk_right(){
  //1
  RightFront(12,5,4,speed,servo_delay);
  LeftMid(6.6,6.6,4,speed,servo_delay);
  RightBack(5,12,4,speed,servo_delay);

  delay(5);

  LeftFront(12,5,3,speed,servo_delay);
  RightMid(6.6,6.6,3,speed,servo_delay);
  LeftBack(5,12,3,speed,servo_delay);
  
  // delay(10);

  // RightFront(11,5,4,speed,servo_delay);
  // LeftMid(7.3,7.3,4,speed,servo_delay);
  // RightBack(5,11,4,speed,servo_delay);

  LeftFront(8,5,3,speed,servo_delay);
  RightMid(9.4,9.4,3,speed,servo_delay);
  LeftBack(5,8,3,speed,servo_delay);

  RightFront(10,5,4,speed,servo_delay);
  LeftMid(8,8,4,speed,servo_delay);
  RightBack(5,10,4,speed,servo_delay);

  // RightFront(9,5,4,speed,servo_delay);
  // LeftMid(8.7,8.7,4,speed,servo_delay);
  // RightBack(5,9,4,speed,servo_delay);

  //2
  // LeftFront(8,5,3,speed,servo_delay);
  // RightMid(9.4,9.4,3,speed,servo_delay);
  // LeftBack(5,8,3,speed,servo_delay);

  RightFront(8,5,4,speed,servo_delay);
  LeftMid(9.4,9.4,4,speed,servo_delay);
  RightBack(5,8,4,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(8,5,4,speed,servo_delay);
  RightMid(9.4,9.4,4,speed,servo_delay);
  LeftBack(5,8,4,speed,servo_delay);

  delay(5);

  RightFront(8,5,3,speed,servo_delay);
  LeftMid(9.4,9.4,3,speed,servo_delay);
  RightBack(5,8,3,speed,servo_delay);
  
  // delay(10);

  // LeftFront(9,5,4,speed,servo_delay);
  // RightMid(8.7,8.7,4,speed,servo_delay);
  // LeftBack(5,9,4,speed,servo_delay);

  RightFront(12,5,3,speed,servo_delay);
  LeftMid(6.6,6.6,3,speed,servo_delay);
  RightBack(5,12,3,speed,servo_delay);

  LeftFront(10,5,4,speed,servo_delay);
  RightMid(8,8,4,speed,servo_delay);
  LeftBack(5,10,4,speed,servo_delay);

  // LeftFront(11,5,4,speed,servo_delay);
  // RightMid(7.3,7.3,4,speed,servo_delay);
  // LeftBack(5,11,4,speed,servo_delay);

  //4
  // RightFront(12,5,3,speed,servo_delay);
  // LeftMid(6.6,6.6,3,speed,servo_delay);
  // RightBack(5,12,3,speed,servo_delay);

  delay(5);

  LeftFront(12,5,4,speed,servo_delay);
  RightMid(6.6,6.6,4,speed,servo_delay);
  LeftBack(5,12,4,speed,servo_delay);
  
  // delay(20);
}

void crabwalk_right_obstacle(){
  //1
  RightFront(12,5,6,speed,servo_delay);
  LeftMid(6.6,6.6,6,speed,servo_delay);
  RightBack(5,12,6,speed,servo_delay);

  delay(5);

  LeftFront(12,5,3,speed,servo_delay);
  RightMid(6.6,6.6,3,speed,servo_delay);
  LeftBack(5,12,3,speed,servo_delay);
  
  // delay(10);

  // RightFront(11,5,6,speed,servo_delay);
  // LeftMid(7.3,7.3,6,speed,servo_delay);
  // RightBack(5,11,6,speed,servo_delay);

  LeftFront(8,5,3,speed,servo_delay);
  RightMid(9.4,9.4,3,speed,servo_delay);
  LeftBack(5,8,3,speed,servo_delay);

  RightFront(10,5,6,speed,servo_delay);
  LeftMid(8,8,6,speed,servo_delay);
  RightBack(5,10,6,speed,servo_delay);

  // RightFront(9,5,6,speed,servo_delay);
  // LeftMid(8.7,8.7,6,speed,servo_delay);
  // RightBack(5,9,6,speed,servo_delay);

  //2
  // LeftFront(8,5,3,speed,servo_delay);
  // RightMid(9.4,9.4,3,speed,servo_delay);
  // LeftBack(5,8,3,speed,servo_delay);

  RightFront(8,5,6,speed,servo_delay);
  LeftMid(9.4,9.4,6,speed,servo_delay);
  RightBack(5,8,6,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(8,5,6,speed,servo_delay);
  RightMid(9.4,9.4,6,speed,servo_delay);
  LeftBack(5,8,6,speed,servo_delay);

  delay(5);

  RightFront(8,5,3,speed,servo_delay);
  LeftMid(9.4,9.4,3,speed,servo_delay);
  RightBack(5,8,3,speed,servo_delay);
  
  // delay(10);

  // LeftFront(9,5,6,speed,servo_delay);
  // RightMid(8.7,8.7,6,speed,servo_delay);
  // LeftBack(5,9,6,speed,servo_delay);

  RightFront(12,5,3,speed,servo_delay);
  LeftMid(6.6,6.6,3,speed,servo_delay);
  RightBack(5,12,3,speed,servo_delay);

  LeftFront(10,5,6,speed,servo_delay);
  RightMid(8,8,6,speed,servo_delay);
  LeftBack(5,10,6,speed,servo_delay);

  // LeftFront(11,5,6,speed,servo_delay);
  // RightMid(7.3,7.3,6,speed,servo_delay);
  // LeftBack(5,11,6,speed,servo_delay);

  //4
  // RightFront(12,5,3,speed,servo_delay);
  // LeftMid(6.6,6.6,3,speed,servo_delay);
  // RightBack(5,12,3,speed,servo_delay);

  LeftFront(12,5,6,speed,servo_delay);
  RightMid(6.6,6.6,6,speed,servo_delay);
  LeftBack(5,12,6,speed,servo_delay);
  
  // delay(20);
}

void walk_to_victim(){
  //1
  RightFront(7.25,8.75,6,speed,servo_delay);
  LeftMid(7.25,8.75,6,speed,servo_delay);
  RightBack(7.25,8.75,6,speed,servo_delay);

  delay(50);

  LeftFront(8.75,7.25,4.5,speed,servo_delay);
  RightMid(8.75,7.25,4.5,speed,servo_delay);
  LeftBack(8.75,7.25,4.5,speed,servo_delay);

  delay(50);

  //2
  LeftFront(7.25,8.75,4.5,speed,servo_delay);
  RightMid(7.25,8.75,4.5,speed,servo_delay);
  LeftBack(7.25,8.75,4.5,speed,servo_delay);

  RightFront(8.75,7.25,6,speed,servo_delay);
  LeftMid(8.75,7.25,6,speed,servo_delay);
  RightBack(8.75,7.25,6,speed,servo_delay);
  
  delay(100);

  //4
  LeftFront(7.25,8.75,6,speed,servo_delay);
  RightMid(7.25,8.75,6,speed,servo_delay);
  LeftBack(7.25,8.75,6,speed,servo_delay);

  delay(50);

  RightFront(8.75,7.25,4.5,speed,servo_delay);
  LeftMid(8.75,7.25,4.5,speed,servo_delay);
  RightBack(8.75,7.25,4.5,speed,servo_delay);
  
  delay(50);

  //4
  LeftFront(8.75,7.25,6,speed,servo_delay);
  RightMid(8.75,7.25,6,speed,servo_delay);
  LeftBack(8.75,7.25,6,speed,servo_delay);

  RightFront(7.25,8.75,4.5,speed,servo_delay);
  LeftMid(7.25,8.75,4.5,speed,servo_delay);
  RightBack(7.25,8.75,4.5,speed,servo_delay);
  
  delay(100);
}
