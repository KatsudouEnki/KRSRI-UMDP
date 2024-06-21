#include <DynamixelSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <MechaQMC5883.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>
#include <Adafruit_VL53L0X.h>

MechaQMC5883 qmc;

#define STX '\x02'
#define ETX '\x03'

#define CMPS12_ADDRESS 0x60  // Address of CMPS12 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from

#define MIRROR_SIDE 0


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

#define SONAR_NUM 5      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(34, 34, MAX_DISTANCE),  // Depan
  NewPing(32, 32, MAX_DISTANCE),  // Belakang
  NewPing(31, 31, MAX_DISTANCE),  // Kiri
  NewPing(35, 35, MAX_DISTANCE),   // Kanan
  NewPing(37, 37, MAX_DISTANCE)
};


///TOF
#define LOX1_ADDRESS 0x30 //Address TOF sensor 1
#define LOX2_ADDRESS 0x31 //Address TOF sensor 2
// set the pins to shutdown
#define SHT_LOX1 66 //A12
#define SHT_LOX2 68 //A14
// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;


int left_dis,
    right_dis,
    front_dis,
    back_dis,
    gripper_dis;

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


#define BNO055_SAMPLERATE_DELAY_MS (10)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

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

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.clearDisplay();
  Serial.println(dynamixelGammaMid(test_x,test_y,test_z,0,0));
  Serial.println(dynamixelAlpha(test_x,test_y,test_z,0,0));
  Serial.println(dynamixelBeta(test_x,test_y,test_z,0,0));
  
  Serial.println(dynamixelGammaMid(default_x,default_y,default_z,0,0));
  Serial.println(dynamixelAlpha(default_x,default_y,default_z,0,0));
  Serial.println(dynamixelBeta(default_x,default_y,default_z,0,0));
//  delay(2000);
  display.clearDisplay();
  
//  qmc.init();
  myservo.attach(44);
  servoAngkat.attach(40);//A10
  servoBuka.attach(42);//A8
  Wire.begin();  
 
  // bno_init();

  //
  pinMode(SHT_LOX1, OUTPUT);
  pinMode(SHT_LOX2, OUTPUT);

  Serial.println("Shutdown pins inited...");

  digitalWrite(SHT_LOX1, LOW);
  digitalWrite(SHT_LOX2, LOW);

  // setID();
  buff_serial = "";
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(11,INPUT_PULLUP);
}

void LeftFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
//  display.setCursor(80,0);
//  display.print("Depan");
  
  Dynamixel.moveSpeed(3, dynamixelGammaLFRB(x_val,y_val,z_val,0,0),speed);
//  display.setCursor(80,8);
//  display.print(dynamixelGammaLFRB(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(2, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
//  display.setCursor(80,16);
//  display.print(dynamixelAlpha(x_val,y_val,z_val,0,1));
  delay(servo_delay);

  Dynamixel.moveSpeed(1, dynamixelBeta(x_val,y_val,z_val,1,1), speed);
//  display.setCursor(80,24);
//  display.print(dynamixelBeta(x_val,y_val,z_val,1,1));
  delay(servo_delay);
}
void LeftMid(float x_val, float y_val,float z_val, int speed,int servo_delay){
//  display.setCursor(40,0);
//  display.print("MID");
  
  Dynamixel.moveSpeed(9, dynamixelGammaMid(x_val,y_val,z_val,0,0),speed);
//  display.setCursor(40,8);
//  display.print(dynamixelGammaMid(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(8, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
//  display.setCursor(40,16);
//  display.print(dynamixelAlpha(x_val,y_val,z_val,0,1));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(7, dynamixelBeta(x_val,y_val,z_val,1,1), speed);
//  display.setCursor(40,24);
//  display.print(dynamixelBeta(x_val,y_val,z_val,1,1));
  delay(servo_delay);
}
void LeftBack(float x_val, float y_val,float z_val, int speed,int servo_delay){
//  display.setCursor(0,0);
//  display.print("Back");
//  
  Dynamixel.moveSpeed(15, dynamixelGamma(x_val,y_val,z_val,0,0), speed);
//  display.setCursor(0,8);
//  display.print(dynamixelGamma(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(14, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
//  display.setCursor(0,16);
//  display.print(dynamixelAlpha(x_val,y_val,z_val,0,1));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(13, dynamixelBeta(x_val,y_val,z_val,1,1), speed);
//  display.setCursor(0,24);
//  display.print(dynamixelBeta(x_val,y_val,z_val,1,1));
  delay(servo_delay);
}

void RightFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(4, dynamixelGamma(x_val,y_val,z_val,1,0),speed);
//  display.setCursor(80,35);
//  display.print(dynamixelGamma(x_val,y_val,z_val,1,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(5, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
//  display.setCursor(80,43);
//  display.print(dynamixelAlpha(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(6, dynamixelBeta(x_val,y_val,z_val,1,0), speed);
//  display.setCursor(80,51);
//  display.print(dynamixelBeta(x_val,y_val,z_val,1,0));
  delay(servo_delay);
}
void RightMid(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(10, dynamixelGammaMid(x_val,y_val,z_val,1,0),speed);
//  display.setCursor(40,35);
//  display.print(dynamixelGammaMid(x_val,y_val,z_val,1,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(11, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
//  display.setCursor(40,43);
//  display.print(dynamixelAlpha(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(12, dynamixelBeta(x_val,y_val,z_val,1,0), speed);
//  display.setCursor(40,51);
//  display.print(dynamixelBeta(x_val,y_val,z_val,1,0));
  delay(servo_delay);
}
void RightBack(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(16, dynamixelGammaLFRB(x_val,y_val,z_val,1,0),speed);
//  display.setCursor(0,35);
//  display.print(dynamixelGammaLFRB(x_val,y_val,z_val,1,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(17, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
//  display.setCursor(0,43);
//  display.print(dynamixelAlpha(x_val,y_val,z_val,0,0));
  delay(servo_delay);
  
  Dynamixel.moveSpeed(18, dynamixelBeta(x_val,y_val,z_val,1,0), speed);
//  display.setCursor(0,51);
//  display.print(dynamixelBeta(x_val,y_val,z_val,1,0));
  delay(servo_delay);
}

int speed=800, servo_delay=0;

void default_state(){
  LeftFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  servo_movement("angkat", 0);
  servo_movement("buka", 0);
  servo_movement("putar",0);
}

void cam_state(){
  LeftFront(8,8,6,speed,servo_delay);
  LeftMid(8,8,6,speed,servo_delay);
  LeftBack(8,8,6,speed,servo_delay);

  RightFront(8,8,6,speed,servo_delay);
  RightMid(8,8,6,speed,servo_delay);
  RightBack(8,8,6,speed,servo_delay);
  servo_movement("angkat",1);
  digitalWrite(7, HIGH);
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

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,4.5,speed/3,servo_delay);
  LeftMid(10,5,4.5,speed/3,servo_delay);
  RightBack(10,5,4.5,speed/3,servo_delay);

  delay(50);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);

  //4
  LeftFront(10,5,4.5,speed/3,servo_delay);
  RightMid(10,5,4.5,speed/3,servo_delay);
  LeftBack(10,5,4.5,speed/3,servo_delay);

  delay(50);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(6,9,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
}

void walk_fast_test(){
  //1
  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);
  delay(5);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,4.5,speed/3,servo_delay);
  LeftMid(10,5,4.5,speed/3,servo_delay);
  RightBack(10,5,4.5,speed/3,servo_delay);

  delay(50);

  //3
  LeftFront(5,10,4.9,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);

  //4
  LeftFront(10,5,4.9,speed/3.6,servo_delay);
  RightMid(10,5,4.5,speed/3,servo_delay);
  LeftBack(10,5,4.5,speed/3,servo_delay);

  delay(50);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(6,9,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
}

void walk_fast_obstacle(){
  //1
  RightFront(5,10,6.5,speed,servo_delay);
  LeftMid(5,10,6.5,speed,servo_delay);
  RightBack(5,10,6.5,speed,servo_delay);

  delay(5);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  delay(20);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,6.5,speed/3,servo_delay);
  LeftMid(10,5,6.5,speed/3,servo_delay);
  RightBack(10,5,6.5,speed/3,servo_delay);
  
  delay(60);

  //3
  LeftFront(5,10,6.5,speed,servo_delay);
  RightMid(5,10,6.5,speed,servo_delay);
  LeftBack(5,10,6.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(20);

  //4
  LeftFront(10,5,6.5,speed/3,servo_delay);
  RightMid(10,5,6.5,speed/3,servo_delay);
  LeftBack(10,5,6.5,speed/3,servo_delay);
  
  delay(60);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(6,9,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
}

void walk_fast_balls(){
  //1
  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(20);

  LeftFront(10,5,2.75,speed,servo_delay);
  RightMid(10,5,2.75,speed,servo_delay);
  LeftBack(10,5,2.75,speed,servo_delay);

  delay(80);

  //2
  LeftFront(5,10,2.75,speed,servo_delay);
  RightMid(5,10,2.75,speed,servo_delay);
  LeftBack(5,10,2.75,speed,servo_delay);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(100);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(20);

  RightFront(10,5,2.75,speed,servo_delay);
  LeftMid(10,5,2.75,speed,servo_delay);
  RightBack(10,5,2.75,speed,servo_delay);

  delay(80);

  //4
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  RightFront(5,10,2.75,speed,servo_delay);
  LeftMid(6,9,2.75,speed,servo_delay);
  RightBack(5,10,2.75,speed,servo_delay);

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

void reverse_fast_obstacle(){
  //1
  RightFront(10,5,5.5,speed,servo_delay);
  LeftMid(10,5,5.5,speed,servo_delay);
  RightBack(10,5,5.5,speed,servo_delay);

  delay(5);

  LeftFront(5,10,3.5,speed,servo_delay);
  RightMid(5,10,3.5,speed,servo_delay);
  LeftBack(5,10,3.5,speed,servo_delay);

  // delay(25);

  //2
  LeftFront(10,5,3.5,speed,servo_delay);
  RightMid(10,5,3.5,speed,servo_delay);
  LeftBack(10,5,3.5,speed,servo_delay);

  RightFront(5,10,5.5,speed,servo_delay);
  LeftMid(5,10,5.5,speed,servo_delay);
  RightBack(5,10,5.5,speed,servo_delay);
  
  // delay(30);

  //3
  LeftFront(10,5,5.5,speed,servo_delay);
  RightMid(10,5,5.5,speed,servo_delay);
  LeftBack(10,5,5.5,speed,servo_delay);

  delay(5);

  RightFront(5,10,3.5,speed,servo_delay);
  LeftMid(5,10,3.5,speed,servo_delay);
  RightBack(5,10,3.5,speed,servo_delay);
  
  // delay(25);

  //4
  LeftFront(5,10,5.5,speed,servo_delay);
  RightMid(5,10,5.5,speed,servo_delay);
  LeftBack(5,10,5.5,speed,servo_delay);

  RightFront(10,5,3.5,speed,servo_delay);
  LeftMid(10,5,3.5,speed,servo_delay);
  RightBack(10,5,3.5,speed,servo_delay);
  
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

  //2
  LeftFront(8.75,7.25,3,speed,servo_delay);
  RightMid(7.25,8.75,3,speed,servo_delay);
  LeftBack(8.75,7.25,3,speed,servo_delay);

  RightFront(8.75,7.25,4.5,speed/3,servo_delay);
  LeftMid(7.25,8.75,4.5,speed/3,servo_delay);
  RightBack(8.75,7.25,4.5,speed/3,servo_delay);
  
  delay(20);

  //3
  LeftFront(8.75,7.25,4.5,speed,servo_delay);
  RightMid(7.25,8.75,4.5,speed,servo_delay);
  LeftBack(8.75,7.25,4.5,speed,servo_delay);

  delay(5);

  RightFront(8.75,7.25,3,speed,servo_delay);
  LeftMid(7.25,8.75,3,speed,servo_delay);
  RightBack(8.75,7.25,3,speed,servo_delay);
  
  //4
  LeftFront(7.25,8.75,4.5,speed/3,servo_delay);
  RightMid(8.75,7.25,4.5,speed/3,servo_delay);
  LeftBack(7.25,8.75,4.5,speed/3,servo_delay);

  delay(20);

  RightFront(7.25,8.75,3,speed,servo_delay);
  LeftMid(8.75,7.25,3,speed,servo_delay);
  RightBack(7.25,8.75,3,speed,servo_delay);
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

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(10,5,4.5,speed/3,servo_delay);
  LeftMid(5,10,4.5,speed/3,servo_delay);
  RightBack(10,5,4.5,speed/3,servo_delay);

  delay(50);
  
  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  //4
  LeftFront(5,10,4.5,speed/3,servo_delay);
  RightMid(10,5,4.5,speed/3,servo_delay);
  LeftBack(5,10,4.5,speed/3,servo_delay);

  delay(50);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
}

void turn_left_obstacle(){
  //1
  RightFront(7.25,8.75,6.5,speed,servo_delay);
  LeftMid(8.75,7.25,6.5,speed,servo_delay);
  RightBack(7.25,8.75,6.5,speed,servo_delay);

  delay(5);

  LeftFront(7.25,8.75,3.5,speed,servo_delay);
  RightMid(8.75,7.25,3.5,speed,servo_delay);
  LeftBack(7.25,8.75,3.5,speed,servo_delay);

  delay(10);

  //2
  LeftFront(8.75,7.25,3.5,speed,servo_delay);
  RightMid(7.25,8.75,3.5,speed,servo_delay);
  LeftBack(8.75,7.25,3.5,speed,servo_delay);

  RightFront(8.75,7.25,6.5,speed/3,servo_delay);
  LeftMid(7.25,8.75,6.5,speed/3,servo_delay);
  RightBack(8.75,7.25,6.5,speed/3,servo_delay);

  delay(20);

  //3
  LeftFront(8.75,7.25,6.5,speed,servo_delay);
  RightMid(7.25,8.75,6.5,speed,servo_delay);
  LeftBack(8.75,7.25,6.5,speed,servo_delay);

  delay(5);

  RightFront(8.75,7.25,3.5,speed,servo_delay);
  LeftMid(7.25,8.75,3.5,speed,servo_delay);
  RightBack(8.75,7.25,3.5,speed,servo_delay);

  delay(10);
  
  //4
  LeftFront(7.25,8.75,6.5,speed/3,servo_delay);
  RightMid(8.75,7.25,6.5,speed/3,servo_delay);
  LeftBack(7.25,8.75,6.5,speed/3,servo_delay);

  delay(20);

  RightFront(7.25,8.75,3.5,speed,servo_delay);
  LeftMid(8.75,7.25,3.5,speed,servo_delay);
  RightBack(7.25,8.75,3.5,speed,servo_delay);
}

void turn_left_obstacle_fast(){
  //1
  RightFront(5,10,6.5,speed,servo_delay);
  LeftMid(10,5,6.5,speed,servo_delay);
  RightBack(5,10,6.5,speed,servo_delay);

  delay(5);

  LeftFront(5,10,3.5,speed,servo_delay);
  RightMid(10,5,3.5,speed,servo_delay);
  LeftBack(5,10,3.5,speed,servo_delay);

  delay(10);

  //2
  LeftFront(10,5,3.5,speed,servo_delay);
  RightMid(5,10,3.5,speed,servo_delay);
  LeftBack(10,5,3.5,speed,servo_delay);

  RightFront(10,5,6.5,speed/3,servo_delay);
  LeftMid(5,10,6.5,speed/3,servo_delay);
  RightBack(10,5,6.5,speed/3,servo_delay);

  delay(60);

  //3
  LeftFront(10,5,6.5,speed,servo_delay);
  RightMid(5,10,6.5,speed,servo_delay);
  LeftBack(10,5,6.5,speed,servo_delay);

  delay(5);

  RightFront(10,5,3.5,speed,servo_delay);
  LeftMid(5,10,3.5,speed,servo_delay);
  RightBack(10,5,3.5,speed,servo_delay);

  delay(10);
  
  //4
  LeftFront(5,10,6.5,speed/3,servo_delay);
  RightMid(10,5,6.5,speed/3,servo_delay);
  LeftBack(5,10,6.5,speed/3,servo_delay);

  delay(60);

  RightFront(5,10,3.5,speed,servo_delay);
  LeftMid(10,5,3.5,speed,servo_delay);
  RightBack(5,10,3.5,speed,servo_delay);
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

  //2
  LeftFront(7.25,8.75,3,speed,servo_delay);
  RightMid(8.75,7.25,3,speed,servo_delay);
  LeftBack(7.25,8.75,3,speed,servo_delay);

  RightFront(7.25,8.75,4.5,speed/3,servo_delay);
  LeftMid(8.75,7.25,4.5,speed/3,servo_delay);
  RightBack(7.25,8.75,4.5,speed/3,servo_delay);
  
  delay(20);

  //3
  LeftFront(7.25,8.75,4.5,speed,servo_delay);
  RightMid(8.75,7.25,4.5,speed,servo_delay);
  LeftBack(7.25,8.75,4.5,speed,servo_delay);

  delay(5);

  RightFront(7.25,8.75,3,speed,servo_delay);
  LeftMid(8.75,7.25,3,speed,servo_delay);
  RightBack(7.25,8.75,3,speed,servo_delay);
  
  //4
  LeftFront(8.75,7.25,4.5,speed/3,servo_delay);
  RightMid(7.25,8.75,4.5,speed/3,servo_delay);
  LeftBack(8.75,7.25,4.5,speed/3,servo_delay);

  delay(20);

  RightFront(8.75,7.25,3,speed,servo_delay);
  LeftMid(7.25,8.75,3,speed,servo_delay);
  RightBack(8.75,7.25,3,speed,servo_delay);
}

void turn_right_fast(){
  //1
  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(5);

  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(5,10,4.5,speed/3,servo_delay);
  LeftMid(10,5,4.5,speed/3,servo_delay);
  RightBack(5,10,4.5,speed/3,servo_delay);
  
  delay(50);

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
  LeftFront(10,5,4.5,speed/3,servo_delay);
  RightMid(5,10,4.5,speed/3,servo_delay);
  LeftBack(10,5,4.5,speed/3,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(6,9,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(50);
}

void turn_right_obstacle(){
  //1
  RightFront(8.75,7.25,6.5,speed,servo_delay);
  LeftMid(7.25,8.75,6.5,speed,servo_delay);
  RightBack(8.75,7.25,6.5,speed,servo_delay);

  delay(5);

  LeftFront(8.75,7.25,3.5,speed,servo_delay);
  RightMid(7.25,8.75,3.5,speed,servo_delay);
  LeftBack(8.75,7.25,3.5,speed,servo_delay);

  delay(10);

  //2
  LeftFront(7.25,8.75,3.5,speed,servo_delay);
  RightMid(8.75,7.25,3.5,speed,servo_delay);
  LeftBack(7.25,8.75,3.5,speed,servo_delay);

  RightFront(7.25,8.75,6.5,speed/3,servo_delay);
  LeftMid(8.75,7.25,6.5,speed/3,servo_delay);
  RightBack(7.25,8.75,6.5,speed/3,servo_delay);
  
  delay(20);

  //3
  LeftFront(7.25,8.75,6.5,speed,servo_delay);
  RightMid(8.75,7.25,6.5,speed,servo_delay);
  LeftBack(7.25,8.75,6.5,speed,servo_delay);

  delay(5);

  RightFront(7.25,8.75,3.5,speed,servo_delay);
  LeftMid(8.75,7.25,3.5,speed,servo_delay);
  RightBack(7.25,8.75,3.5,speed,servo_delay);

  delay(10);
  
  //4
  LeftFront(8.75,7.25,6.5,speed/3,servo_delay);
  RightMid(7.25,8.75,6.5,speed/3,servo_delay);
  LeftBack(8.75,7.25,6.5,speed/3,servo_delay);

  delay(20);

  RightFront(8.75,7.25,3.5,speed,servo_delay);
  LeftMid(7.25,8.75,3.5,speed,servo_delay);
  RightBack(8.75,7.25,3.5,speed,servo_delay);
}

void turn_right_obstacle_fast(){
  //1
  RightFront(10,5,6.5,speed,servo_delay);
  LeftMid(5,10,6.5,speed,servo_delay);
  RightBack(10,5,6.5,speed,servo_delay);

  delay(5);

  LeftFront(10,5,3.5,speed,servo_delay);
  RightMid(5,10,3.5,speed,servo_delay);
  LeftBack(10,5,3.5,speed,servo_delay);

  delay(10);

  //2
  LeftFront(5,10,3.5,speed,servo_delay);
  RightMid(10,5,3.5,speed,servo_delay);
  LeftBack(5,10,3.5,speed,servo_delay);

  RightFront(5,10,6.5,speed/3,servo_delay);
  LeftMid(10,5,6.5,speed/3,servo_delay);
  RightBack(5,10,6.5,speed/3,servo_delay);
  
  delay(60);

  //3
  LeftFront(5,10,6.5,speed,servo_delay);
  RightMid(10,5,6.5,speed,servo_delay);
  LeftBack(5,10,6.5,speed,servo_delay);

  delay(5);

  RightFront(5,10,3.5,speed,servo_delay);
  LeftMid(10,5,3.5,speed,servo_delay);
  RightBack(5,10,3.5,speed,servo_delay);

  delay(10);
  
  //4
  LeftFront(10,5,6.5,speed/3,servo_delay);
  RightMid(5,10,6.5,speed/3,servo_delay);
  LeftBack(10,5,6.5,speed/3,servo_delay);

  delay(60);

  RightFront(10,5,3.5,speed,servo_delay);
  LeftMid(6,9,3.5,speed,servo_delay);
  RightBack(10,5,3.5,speed,servo_delay);
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

  LeftFront(8,5,2.75,speed,servo_delay);
  RightMid(9.4,9.4,2.75,speed,servo_delay);
  LeftBack(5,8,2.75,speed,servo_delay);
  
  // delay(10);

  // RightFront(9,5,4,speed,servo_delay);
  // LeftMid(8.7,8.7,4,speed,servo_delay);
  // RightBack(5,9,4,speed,servo_delay);

  LeftFront(12,5,2.75,speed,servo_delay);
  RightMid(6.6,6.6,2.75,speed,servo_delay);
  LeftBack(5,12,2.75,speed,servo_delay);
  
  RightFront(10,5,4,speed,servo_delay);
  LeftMid(8,8,4,speed,servo_delay);
  RightBack(5,10,4,speed,servo_delay);

  // RightFront(11,5,4,speed,servo_delay);
  // LeftMid(7.3,7.3,4,speed,servo_delay);
  // RightBack(5,11,4,speed,servo_delay);

  //2
  // LeftFront(12,5,2.75,speed,servo_delay);
  // RightMid(6.6,6.6,2.75,speed,servo_delay);
  // LeftBack(5,12,2.75,speed,servo_delay);

  RightFront(12,5,4,speed,servo_delay);
  LeftMid(6.6,6.6,4,speed,servo_delay);
  RightBack(5,12,4,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(12,5,4,speed,servo_delay);
  RightMid(6.6,6.6,4,speed,servo_delay);
  LeftBack(5,12,4,speed,servo_delay);

  delay(5);

  RightFront(12,5,2.75,speed,servo_delay);
  LeftMid(6.6,6.6,2.75,speed,servo_delay);
  RightBack(5,12,2.75,speed,servo_delay);
  
  // delay(10);

  // LeftFront(11,5,4,speed,servo_delay);
  // RightMid(7.3,7.3,4,speed,servo_delay);
  // LeftBack(5,11,4,speed,servo_delay);

  RightFront(8,5,2.75,speed,servo_delay);
  LeftMid(9.4,9.4,2.75,speed,servo_delay);
  RightBack(5,8,2.75,speed,servo_delay);

  LeftFront(10,5,4,speed,servo_delay);
  RightMid(8,8,4,speed,servo_delay);
  LeftBack(5,10,4,speed,servo_delay);

  // LeftFront(9,5,4,speed,servo_delay);
  // RightMid(8.7,8.7,4,speed,servo_delay);
  // LeftBack(5,9,4,speed,servo_delay);

  //4
  // RightFront(8,5,2.75,speed,servo_delay);
  // LeftMid(9.4,9.4,2.75,speed,servo_delay);
  // RightBack(5,8,2.75,speed,servo_delay);

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

  LeftFront(12,5,2.75,speed,servo_delay);
  RightMid(6.6,6.6,2.75,speed,servo_delay);
  LeftBack(5,12,2.75,speed,servo_delay);
  
  // delay(10);

  // RightFront(11,5,4,speed,servo_delay);
  // LeftMid(7.3,7.3,4,speed,servo_delay);
  // RightBack(5,11,4,speed,servo_delay);

  LeftFront(8,5,2.75,speed,servo_delay);
  RightMid(9.4,9.4,2.75,speed,servo_delay);
  LeftBack(5,8,2.75,speed,servo_delay);

  RightFront(10,5,4,speed,servo_delay);
  LeftMid(8,8,4,speed,servo_delay);
  RightBack(5,10,4,speed,servo_delay);

  // RightFront(9,5,4,speed,servo_delay);
  // LeftMid(8.7,8.7,4,speed,servo_delay);
  // RightBack(5,9,4,speed,servo_delay);

  //2
  // LeftFront(8,5,2.75,speed,servo_delay);
  // RightMid(9.4,9.4,2.75,speed,servo_delay);
  // LeftBack(5,8,2.75,speed,servo_delay);

  RightFront(8,5,4,speed,servo_delay);
  LeftMid(9.4,9.4,4,speed,servo_delay);
  RightBack(5,8,4,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(8,5,4,speed,servo_delay);
  RightMid(9.4,9.4,4,speed,servo_delay);
  LeftBack(5,8,4,speed,servo_delay);

  delay(5);

  RightFront(8,5,2.75,speed,servo_delay);
  LeftMid(9.4,9.4,2.75,speed,servo_delay);
  RightBack(5,8,2.75,speed,servo_delay);
  
  // delay(10);

  // LeftFront(9,5,4,speed,servo_delay);
  // RightMid(8.7,8.7,4,speed,servo_delay);
  // LeftBack(5,9,4,speed,servo_delay);

  RightFront(12,5,2.75,speed,servo_delay);
  LeftMid(6.6,6.6,2.75,speed,servo_delay);
  RightBack(5,12,2.75,speed,servo_delay);

  LeftFront(10,5,4,speed,servo_delay);
  RightMid(8,8,4,speed,servo_delay);
  LeftBack(5,10,4,speed,servo_delay);

  // LeftFront(11,5,4,speed,servo_delay);
  // RightMid(7.3,7.3,4,speed,servo_delay);
  // LeftBack(5,11,4,speed,servo_delay);

  //4
  // RightFront(12,5,2.75,speed,servo_delay);
  // LeftMid(6.6,6.6,2.75,speed,servo_delay);
  // RightBack(5,12,2.75,speed,servo_delay);

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
void crabwalk_right_test0(){
  //1
  RightFront(12,5,6,speed,servo_delay);
  LeftMid(6.6,6.6,6,speed,servo_delay);
  RightBack(5,12,6,speed,servo_delay);
  delay(5);

  LeftFront(12,5,5,speed,servo_delay);
  RightMid(6.6,6.6,5,speed,servo_delay);
  LeftBack(5,12,5,speed,servo_delay);

  LeftFront(8,5,5,speed,servo_delay);
  RightMid(9.4,9.4,5,speed,servo_delay);
  LeftBack(5,8,5,speed,servo_delay);

  RightFront(10,5,6,speed,servo_delay);
  LeftMid(8,8,6,speed,servo_delay);
  RightBack(5,10,6,speed,servo_delay);

  RightFront(8,5,6,speed,servo_delay);
  LeftMid(9.4,9.4,6,speed,servo_delay);
  RightBack(5,8,6,speed,servo_delay);

  //3
  LeftFront(8,5,6,speed,servo_delay);
  RightMid(9.4,9.4,6,speed,servo_delay);
  LeftBack(5,8,6,speed,servo_delay);

  delay(5);

  RightFront(8,5,5,speed,servo_delay);
  LeftMid(9.4,9.4,5,speed,servo_delay);
  RightBack(5,8,5,speed,servo_delay);
  
  RightFront(12,5,5,speed,servo_delay);
  LeftMid(6.6,6.6,5,speed,servo_delay);
  RightBack(5,12,5,speed,servo_delay);

  LeftFront(10,5,6,speed,servo_delay);
  RightMid(8,8,6,speed,servo_delay);
  LeftBack(5,10,6,speed,servo_delay);

  LeftFront(12,5,6,speed,servo_delay);
  RightMid(6.6,6.6,6,speed,servo_delay);
  LeftBack(5,12,6,speed,servo_delay);
}

void crabwalk_right_test1(){
  //1
  RightFront(11,5,5,speed,servo_delay);
  LeftMid(5.88,5.88,5,speed,servo_delay);
  RightBack(5,11,5,speed,servo_delay);
  delay(5);

  LeftFront(11,5,3.5,speed,servo_delay);
  RightMid(5.88,5.88,3.5,speed,servo_delay);
  LeftBack(5,11,3.5,speed,servo_delay);

  LeftFront(5,5,3.5,speed,servo_delay);
  RightMid(10.12,10.12,3.5,speed,servo_delay);
  LeftBack(5,5,3.5,speed,servo_delay);

  RightFront(8,5,5,speed,servo_delay);
  LeftMid(8,8,5,speed,servo_delay);
  RightBack(5,8,5,speed,servo_delay);

  RightFront(5,5,5,speed,servo_delay);
  LeftMid(10.12,10.12,5,speed,servo_delay);
  RightBack(5,5,5,speed,servo_delay);

  //3
  LeftFront(5,5,5,speed,servo_delay);
  RightMid(10.12,10.12,5,speed,servo_delay);
  LeftBack(5,5,5,speed,servo_delay);

  delay(5);

  RightFront(5,5,3.5,speed,servo_delay);
  LeftMid(10.12,10.12,3.5,speed,servo_delay);
  RightBack(5,5,3.5,speed,servo_delay);
  
  RightFront(11,5,3.5,speed,servo_delay);
  LeftMid(5.88,5.88,3.5,speed,servo_delay);
  RightBack(5,11,3.5,speed,servo_delay);

  LeftFront(8,5,5,speed,servo_delay);
  RightMid(8,8,5,speed,servo_delay);
  LeftBack(5,8,5,speed,servo_delay);

  LeftFront(11,5,5,speed,servo_delay);
  RightMid(5.88,5.88,5,speed,servo_delay);
  LeftBack(5,11,5,speed,servo_delay);
}

void crabwalk_right_test2(){
  //1
  RightFront(11,5,5.5,speed,servo_delay);
  LeftMid(5.88,5.88,5.5,speed,servo_delay);
  RightBack(5,11,5.5,speed,servo_delay);
  delay(8);

  LeftFront(11,5,3.5,speed,servo_delay);
  RightMid(5.88,5.88,3.5,speed,servo_delay);
  LeftBack(5,11,3.5,speed,servo_delay);
  delay(5);

  RightFront(8,5,5.5,speed/2,servo_delay);
  LeftMid(8,8,5.5,speed/2,servo_delay);
  RightBack(5,8,5.5,speed/2,servo_delay);
  delay(15);

  LeftFront(5,5,3.5,speed,servo_delay);
  RightMid(10.12,10.12,3.5,speed,servo_delay);
  LeftBack(5,5,3.5,speed,servo_delay);
  delay(5);

  RightFront(5,5,5.5,speed/2,servo_delay);
  LeftMid(10.12,10.12,5.5,speed/2,servo_delay);
  RightBack(5,5,5.5,speed/2,servo_delay);
  delay(15);

  //3
  LeftFront(5,5,5.5,speed,servo_delay);
  RightMid(10.12,10.12,5.5,speed,servo_delay);
  LeftBack(5,5,5.5,speed,servo_delay);
  delay(8);

  RightFront(5,5,3.5,speed,servo_delay);
  LeftMid(10.12,10.12,3.5,speed,servo_delay);
  RightBack(5,5,3.5,speed,servo_delay);
  delay(5);

  LeftFront(8,5,5.5,speed,servo_delay);
  RightMid(8,8,5.5,speed,servo_delay);
  LeftBack(5,8,5.5,speed,servo_delay);
  delay(15);
  
  RightFront(11,5,3.5,speed,servo_delay);
  LeftMid(5.88,5.88,3.5,speed,servo_delay);
  RightBack(5,11,3.5,speed,servo_delay);
  delay(5);

  LeftFront(11,5,5.5,speed,servo_delay);
  RightMid(5.88,5.88,5.5,speed,servo_delay);
  LeftBack(5,11,5.5,speed,servo_delay);
  delay(15);

}

void crabwalk_right_test(){
  //1
  RightFront(12,5,5,speed,servo_delay);
  LeftMid(6.6,6.6,5,speed,servo_delay);
  RightBack(5,12,5,speed,servo_delay);

  delay(25);

  LeftFront(12,5,2.8,speed,servo_delay);
  RightMid(6.6,6.6,1,speed,servo_delay);
  LeftBack(5,12,2.8,speed,servo_delay);

  LeftFront(8,5,2.8,speed,servo_delay);
  RightMid(9.4,9.4,1,speed,servo_delay);
  LeftBack(5,8,2.8,speed,servo_delay);

  RightFront(10,5,5,speed,servo_delay);
  LeftMid(8,8,5,speed,servo_delay);
  RightBack(5,10,5,speed,servo_delay);

  RightFront(8,5,5,speed,servo_delay);
  LeftMid(9.4,9.4,5,speed,servo_delay);
  RightBack(5,8,5,speed,servo_delay);

  //3
  LeftFront(8,5,5,speed,servo_delay);
  RightMid(9.4,9.4,5,speed,servo_delay);
  LeftBack(5,8,5,speed,servo_delay);

  delay(25);

  RightFront(8,5,1,speed,servo_delay);
  LeftMid(9.4,9.4,2.8,speed,servo_delay);
  RightBack(5,8,1,speed,servo_delay);
  
  RightFront(12,5,1,speed,servo_delay);
  LeftMid(6.6,6.6,2.8,speed,servo_delay);
  RightBack(5,12,1,speed,servo_delay);

  LeftFront(10,5,5,speed,servo_delay);
  RightMid(8,8,5,speed,servo_delay);
  LeftBack(5,10,5,speed,servo_delay);

  LeftFront(12,5,5,speed,servo_delay);
  RightMid(6.6,6.6,5,speed,servo_delay);
  LeftBack(5,12,5,speed,servo_delay);
}

void walk_to_victim(){
  //1
  RightFront(7.25,8.75,5,speed,servo_delay);
  LeftMid(7.25,8.75,5,speed,servo_delay);
  RightBack(7.25,8.75,5,speed,servo_delay);

  delay(50);

  LeftFront(8.75,7.25,3.5,speed,servo_delay);
  RightMid(8.75,7.25,3.5,speed,servo_delay);
  LeftBack(8.75,7.25,3.5,speed,servo_delay);

  delay(50);

  //2
  LeftFront(7.25,8.75,3.5,speed,servo_delay);
  RightMid(7.25,8.75,3.5,speed,servo_delay);
  LeftBack(7.25,8.75,3.5,speed,servo_delay);

  RightFront(8.75,7.25,5,speed,servo_delay);
  LeftMid(8.75,7.25,5,speed,servo_delay);
  RightBack(8.75,7.25,5,speed,servo_delay);
  
  delay(100);

  //4
  LeftFront(7.25,8.75,5,speed,servo_delay);
  RightMid(7.25,8.75,5,speed,servo_delay);
  LeftBack(7.25,8.75,5,speed,servo_delay);

  delay(50);

  RightFront(8.75,7.25,3.5,speed,servo_delay);
  LeftMid(8.75,7.25,3.5,speed,servo_delay);
  RightBack(8.75,7.25,3.5,speed,servo_delay);
  
  delay(50);

  //4
  LeftFront(8.75,7.25,5,speed,servo_delay);
  RightMid(8.75,7.25,5,speed,servo_delay);
  LeftBack(8.75,7.25,5,speed,servo_delay);

  RightFront(7.25,8.75,3.5,speed,servo_delay);
  LeftMid(7.25,8.75,3.5,speed,servo_delay);
  RightBack(7.25,8.75,3.5,speed,servo_delay);
  
  delay(100);
}

void pre_ladder(){
  int z_tangga=4.5;
  speed = 400;
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftMid(6,10,4.5,speed,servo_delay);
  RightMid(6,10,4.5,speed,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  delay(50);
  
  speed = 200;
  LeftFront(2.8,8.8,4.5,speed,servo_delay);
  RightFront(2.8,8.8,4.5,speed,servo_delay);
  LeftMid(10,6,4.5,speed/2,servo_delay);
  RightMid(10,6,4.5,speed/2,servo_delay);
  LeftBack(14.3,4.55,4.5,speed,servo_delay);
  RightBack(14.3,4.55,4.5,speed,servo_delay);
  delay(450);
  
  speed = 400;
  LeftFront(2.8,8.8,1.5,speed,servo_delay);
  RightBack(14.3,4.55,1.5,speed,servo_delay);
  delay(30);
  LeftFront(3.15,9.9,1.5,speed,servo_delay);
  delay(20);
  LeftFront(3.5,11,1.5,speed,servo_delay);
  RightBack(11,3.5,1.5,speed,servo_delay);
  delay(30);
  LeftFront(3.85,12.1,1.5,speed,servo_delay);
  delay(20);
  LeftFront(4.2,13.2,1.5,speed,servo_delay);
  RightBack(8.8,2.8,1.5,speed,servo_delay);
  delay(30);
  LeftFront(4.55,14.3,1.5,speed,servo_delay);
  delay(20);
  LeftFront(4.9,15.4,1.5,speed,servo_delay);
  RightBack(8.8,2.8,3.5,speed,servo_delay);
  delay(60);
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  delay(100);
  
  RightFront(2.8,8.8,1.5,speed,servo_delay);
  LeftBack(14.3,4.55,1.5,speed,servo_delay);
  delay(30);
  RightFront(3.15,9.9,1.5,speed,servo_delay);
  delay(20);
  RightFront(3.5,11,1.5,speed,servo_delay);
  LeftBack(11,3.5,1.5,speed,servo_delay);
  delay(30);
  RightFront(3.85,12.1,1.5,speed,servo_delay);
  delay(20);
  RightFront(4.2,13.2,1.5,speed,servo_delay);
  LeftBack(8.8,2.8,1.5,speed,servo_delay);
  delay(30);
  RightFront(4.55,14.3,1.5,speed,servo_delay);
  delay(20);
  RightFront(4.9,15.4,1.5,speed,servo_delay);
  LeftBack(8.8,2.8,3.5,speed,servo_delay);
  delay(60);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  delay(100);
  
  LeftMid(10,6,1.5,speed,servo_delay);
  RightMid(10,6,1.5,speed,servo_delay);
  delay(50);
  LeftMid(6,10,1.5,speed,servo_delay);
  RightMid(6,10,1.5,speed,servo_delay);
  delay(50);
  LeftMid(6,10,4.5,speed,servo_delay);
  RightMid(6,10,4.5,speed,servo_delay);
  delay(25);
}
void pre_ladder_test(int roll_value){
  double z_tangga=5.25, divider=2;
  if(roll_value<=-3 && roll_value>-7){
    z_tangga=5.5;
  }else if(roll_value<=-7 && roll_value>-10){
    z_tangga=5.70;
  }
  else if(roll_value<=-10 && roll_value>-13){
    z_tangga=5.85;
  }
  else if(roll_value<=-13 && roll_value>-16){
    z_tangga=6.05;
  }
  else if(roll_value<=-16 && roll_value>-19){
    z_tangga=5.55;
  }
  else if(roll_value<=-19 && roll_value>-35){
    z_tangga=5.15;
  }
  speed = 650;
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftMid(6,10,z_tangga,speed/divider,servo_delay);
  RightMid(6,10,z_tangga,speed/divider,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  //delay(50);
  
  speed = 250;
  LeftFront(2.8,8.8,4.5,speed,servo_delay);
  RightFront(2.8,8.8,4.5,speed,servo_delay);
  LeftMid(10,6,z_tangga,speed/divider,servo_delay);
  RightMid(10,6,z_tangga,speed/divider,servo_delay);
  LeftBack(14.3,4.55,4.5,speed,servo_delay);
  RightBack(14.3,4.55,4.5,speed,servo_delay);
  delay(350);
  
  speed = 650;
//  LeftFront(2.8,8.8,0.1,speed,servo_delay);
  LeftFront(2.8,8.8,2.5,speed,servo_delay);
  RightBack(14.3,4.55,1.5,speed,servo_delay);
  delay(140);
  LeftFront(3.15,9.9,0,speed,servo_delay);
  delay(18);
  LeftFront(3.5,11,-0.2,speed,servo_delay);
  RightBack(11,3.5,1.5,speed,servo_delay);
  delay(18);
  LeftFront(3.85,12.1,-0.4,speed,servo_delay);
  delay(18);
  LeftFront(4.2,13.2,-0.6,speed,servo_delay);
  RightBack(8.8,2.8,1.5,speed,servo_delay);
  delay(18);
  LeftFront(4.55,14.3,-0.8,speed,servo_delay);
  delay(18);
  LeftFront(4.9,15.4,0.2,speed,servo_delay);
  RightBack(8.8,2.8,2.5,speed,servo_delay);
  delay(18);
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  delay(100);
  
  RightFront(2.8,8.8,0,speed,servo_delay);
  LeftBack(14.3,4.55,1.5,speed,servo_delay);
  delay(140);
  RightFront(3.15,9.9,-0.1,speed,servo_delay);
  delay(18);
  RightFront(3.5,11,-0.3,speed,servo_delay);
  LeftBack(11,3.5,1.5,speed,servo_delay);
  delay(18);
  RightFront(3.85,12.1,-0.5,speed,servo_delay);
  delay(18);
  RightFront(4.2,13.2,-0.7,speed,servo_delay);
  LeftBack(8.8,2.8,1.5,speed,servo_delay);
  delay(18);
  RightFront(4.55,14.3,-0.9,speed,servo_delay);
  delay(18);
  RightFront(4.9,15.4,0.1,speed,servo_delay);
  LeftBack(8.8,2.8,2.5,speed,servo_delay);
  delay(18);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  delay(100);
  
  LeftMid(10,6,z_tangga-3,speed/divider,servo_delay);
  RightMid(10,6,z_tangga-3,speed/divider,servo_delay);
  delay(50);
  LeftMid(6,10,z_tangga-3,speed/divider,servo_delay);
  RightMid(6,10,z_tangga-3,speed/divider,servo_delay);
  delay(50);
  LeftMid(6,10,z_tangga,speed/divider,servo_delay);
  RightMid(6,10,z_tangga,speed/divider,servo_delay);
//  delay(5);
}
void ladder_stand(int roll_value){
  double z_tangga=5.25;
  if(roll_value<=-3 && roll_value>-7){
    z_tangga=5.5;
  }else if(roll_value<=-7 && roll_value>-10){
    z_tangga=5.70;
  }
  else if(roll_value<=-10 && roll_value>-13){
    z_tangga=5.95;
  }
  else if(roll_value<=-13 && roll_value>-16){
    z_tangga=6.15;
  }
  else if(roll_value<=-16 && roll_value>-19){
    z_tangga=5.65;
  }
  else if(roll_value<=-19 && roll_value>-35){
    z_tangga=5.25;
  }
  delay(25);
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftMid(6,10,z_tangga,speed/2,servo_delay);
  RightMid(6,10,z_tangga,speed/2,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  delay(25);
}
void pre_ladder_right(){
  speed = 375;
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftMid(6,10,4.5,speed,servo_delay);
  RightMid(6,10,4.5,speed,servo_delay);
  LeftBack(9.9,3.15,4.5,speed,servo_delay);
  RightBack(9.9,3.15,4.5,speed,servo_delay);
  //delay(25);

  RightFront(4.55,14.3,1.5,speed,servo_delay);
  LeftBack(9.9,3.15,1.5,speed,servo_delay);
  delay(100);
  
  speed = 125;
  LeftFront(6.96,13.29,4.5,speed,servo_delay);
  LeftMid(7.64,8.81,4.5,speed,servo_delay);
  RightMid(4.17,10.89,4.5,speed,servo_delay);
  RightBack(9.2,4.82,4.5,speed,servo_delay);
  delay(50);
  
  speed = 375;
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftBack(9.9,3.15,4.5,speed,servo_delay);
  delay(50);

  LeftFront(6.96,13.29,1.5,speed,servo_delay);
  RightBack(9.2,4.82,1.5,speed,servo_delay);
  delay(25);
  LeftFront(4.55,14.3,1.5,speed,servo_delay);
  RightBack(9.9,3.15,1.5,speed,servo_delay);
  delay(25);
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightBack(9.9,3.15,4.5,speed,servo_delay);
  delay(50);
  
  LeftMid(7.64,8.81,1.5,speed,servo_delay);
  RightMid(4.17,10.89,1.5,speed,servo_delay);
  delay(25);
  LeftMid(6,10,1.5,speed,servo_delay);
  RightMid(6,10,1.5,speed,servo_delay);
  delay(25);
  LeftMid(6,10,4.5,speed,servo_delay);
  RightMid(6,10,4.5,speed,servo_delay);
  delay(50);
}

void pre_ladder_left(){
  speed = 375;
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftMid(6,10,4.5,speed,servo_delay);
  RightMid(6,10,4.5,speed,servo_delay);
  LeftBack(9.9,3.15,4.5,speed,servo_delay);
  RightBack(9.9,3.15,4.5,speed,servo_delay);
  //delay(25);

  LeftFront(4.55,14.3,1.5,speed,servo_delay);
  RightBack(9.9,3.15,1.5,speed,servo_delay);
  delay(100);
  
  speed = 125;
  RightFront(6.96,13.29,4.5,speed,servo_delay);
  RightMid(7.64,8.81,4.5,speed,servo_delay);
  LeftMid(4.17,10.89,4.5,speed,servo_delay);
  LeftBack(9.2,4.82,4.5,speed,servo_delay);
  delay(50);
  
  speed = 375;
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightBack(9.9,3.15,4.5,speed,servo_delay);
  delay(50);

  RightFront(6.96,13.29,1.5,speed,servo_delay);
  LeftBack(9.2,4.82,1.5,speed,servo_delay);
  delay(25);
  RightFront(4.55,14.3,1.5,speed,servo_delay);
  LeftBack(9.9,3.15,1.5,speed,servo_delay);
  delay(25);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftBack(9.9,3.15,4.5,speed,servo_delay);
  delay(50);
  
  RightMid(7.64,8.81,1.5,speed,servo_delay);
  LeftMid(4.17,10.89,1.5,speed,servo_delay);
  delay(25);
  RightMid(6,10,1.5,speed,servo_delay);
  LeftMid(6,10,1.5,speed,servo_delay);
  delay(25);
  RightMid(6,10,4.5,speed,servo_delay);
  LeftMid(6,10,4.5,speed,servo_delay);
  delay(50);
}

void ladder(){
  double z_tangga=5.25;
  
  speed = 650;
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftMid(6,10,z_tangga,speed/2,servo_delay);
  RightMid(6,10,z_tangga,speed/2,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  //delay(50);
  
  speed = 250;
  LeftFront(2.8,8.8,4.5,speed,servo_delay);
  RightFront(2.8,8.8,4.5,speed,servo_delay);
  LeftMid(10,6,z_tangga,speed/2,servo_delay);
  RightMid(10,6,z_tangga,speed/2,servo_delay);
  LeftBack(14.3,4.55,4.5,speed,servo_delay);
  RightBack(14.3,4.55,4.5,speed,servo_delay);
  delay(350);
  
  speed = 650;
  LeftFront(2.8,8.8,0,speed,servo_delay);
  RightBack(14.3,4.55,1.5,speed,servo_delay);
  delay(140);
  LeftFront(3.15,9.9,-0.2,speed,servo_delay);
  delay(18);
  LeftFront(3.5,11,-0.4,speed,servo_delay);
  RightBack(11,3.5,1.5,speed,servo_delay);
  delay(18);
  LeftFront(3.85,12.1,-0.6,speed,servo_delay);
  delay(18);
  LeftFront(4.2,13.2,-0.8,speed,servo_delay);
  RightBack(8.8,2.8,1.5,speed,servo_delay);
  delay(18);
  LeftFront(4.55,14.3,-1,speed,servo_delay);
  delay(18);
  LeftFront(4.9,15.4,0,speed,servo_delay);
  RightBack(8.8,2.8,2.5,speed,servo_delay);
  delay(18);
  LeftFront(4.55,14.3,4.5,speed,servo_delay);
  RightBack(8.8,2.8,4.5,speed,servo_delay);
  delay(100);
  
  RightFront(2.8,8.8,0,speed,servo_delay);
  LeftBack(14.3,4.55,1.5,speed,servo_delay);
  delay(140);
  RightFront(3.15,9.9,-0.1,speed,servo_delay);
  delay(18);
  RightFront(3.5,11,-0.3,speed,servo_delay);
  LeftBack(11,3.5,1.5,speed,servo_delay);
  delay(18);
  RightFront(3.85,12.1,-0.5,speed,servo_delay);
  delay(18);
  RightFront(4.2,13.2,-0.7,speed,servo_delay);
  LeftBack(8.8,2.8,1.5,speed,servo_delay);
  delay(18);
  RightFront(4.55,14.3,-0.9,speed,servo_delay);
  delay(18);
  RightFront(4.9,15.4,0.1,speed,servo_delay);
  LeftBack(8.8,2.8,2.5,speed,servo_delay);
  delay(18);
  RightFront(4.55,14.3,4.5,speed,servo_delay);
  LeftBack(8.8,2.8,4.5,speed,servo_delay);
  delay(100);
  
  LeftMid(10,6,z_tangga-3,speed/2,servo_delay);
  RightMid(10,6,z_tangga-3,speed/2,servo_delay);
  delay(50);
  LeftMid(6,10,z_tangga-3,speed/2,servo_delay);
  RightMid(6,10,z_tangga-3,speed/2,servo_delay);
  delay(50);
  LeftMid(6,10,z_tangga,speed/2,servo_delay);
  RightMid(6,10,z_tangga,speed/2,servo_delay);
}

void ladder_right(){
  speed = 300;
  LeftFront(4.55,14.3,3.25,speed,servo_delay);
  RightFront(4.55,14.3,3.25,speed,servo_delay);
  LeftMid(6,10,5.35,speed,servo_delay);
  RightMid(6,10,5.35,speed,servo_delay);
  LeftBack(9.9,3.15,7.5,speed,servo_delay);
  RightBack(9.9,3.15,7.5,speed,servo_delay);
  //delay(25);

  RightFront(4.55,14.3,0.6,speed,servo_delay);
  LeftBack(9.9,3.15,4.5,speed,servo_delay);
  delay(100);
  
  speed = 100;
  LeftFront(6.96,13.29,3.25,speed,servo_delay);
  LeftMid(7.64,8.81,5.35,speed,servo_delay);
  RightMid(4.17,10.89,5.35,speed,servo_delay);
  RightBack(9.2,4.82,7.5,speed,servo_delay);
  delay(50);
  
  speed = 300;
  RightFront(4.55,14.3,3.25,speed,servo_delay);
  LeftBack(9.9,3.15,7.5,speed,servo_delay);
  delay(50);

  LeftFront(6.96,13.29,0.6,speed,servo_delay);
  RightBack(9.2,4.82,4.5,speed,servo_delay);
  delay(25);
  LeftFront(4.55,14.3,0.6,speed,servo_delay);
  RightBack(9.9,3.15,4.5,speed,servo_delay);
  delay(25);
  LeftFront(4.55,14.3,3.25,speed,servo_delay);
  RightBack(9.9,3.15,7.5,speed,servo_delay);
  delay(50);
  
  LeftMid(7.64,8.81,3.5,speed,servo_delay);
  RightMid(4.17,10.89,3.5,speed,servo_delay);
  delay(25);
  LeftMid(6,10,3.5,speed,servo_delay);
  RightMid(6,10,3.5,speed,servo_delay);
  delay(25);
  LeftMid(6,10,5.35,speed,servo_delay);
  RightMid(6,10,5.35,speed,servo_delay);
  delay(50);
}

void ladder_left(){
  speed = 300;
  LeftFront(4.55,14.3,3.25,speed,servo_delay);
  RightFront(4.55,14.3,3.25,speed,servo_delay);
  LeftMid(6,10,5.35,speed,servo_delay);
  RightMid(6,10,5.35,speed,servo_delay);
  LeftBack(9.9,3.15,7.5,speed,servo_delay);
  RightBack(9.9,3.15,7.5,speed,servo_delay);
  //delay(25);

  LeftFront(4.55,14.3,0.6,speed,servo_delay);
  RightBack(9.9,3.15,4.5,speed,servo_delay);
  delay(100);
  
  speed = 100;
  RightFront(6.96,13.29,3.25,speed,servo_delay);
  RightMid(7.64,8.81,5.35,speed,servo_delay);
  LeftMid(4.17,10.89,5.35,speed,servo_delay);
  LeftBack(9.2,4.82,7.5,speed,servo_delay);
  delay(50);
  
  speed = 300;
  LeftFront(4.55,14.3,3.25,speed,servo_delay);
  RightBack(9.9,3.15,7.5,speed,servo_delay);
  delay(50);

  RightFront(6.96,13.29,0.6,speed,servo_delay);
  LeftBack(9.2,4.82,4.5,speed,servo_delay);
  delay(25);
  RightFront(4.55,14.3,0.6,speed,servo_delay);
  LeftBack(9.9,3.15,4.5,speed,servo_delay);
  delay(25);
  RightFront(4.55,14.3,3.25,speed,servo_delay);
  LeftBack(9.9,3.15,7.5,speed,servo_delay);
  delay(50);
  
  RightMid(7.64,8.81,3.5,speed,servo_delay);
  LeftMid(4.17,10.89,3.5,speed,servo_delay);
  delay(25);
  RightMid(6,10,3.5,speed,servo_delay);
  LeftMid(6,10,3.5,speed,servo_delay);
  delay(25);
  RightMid(6,10,5.35,speed,servo_delay);
  LeftMid(6,10,5.35,speed,servo_delay);
  delay(50);
}

void post_ladder(){
  speed = 650;
  LeftFront(3.85,12.1,8.25,speed,servo_delay);
  RightFront(3.85,12.1,8.25,speed,servo_delay);
  LeftMid(6,10,5.5,speed/2,servo_delay);
  RightMid(6,10,5.5,speed/2,servo_delay);
  LeftBack(8.8,2.8,7.5,speed,servo_delay);
  RightBack(8.8,2.8,7.5,speed,servo_delay);
  // delay(50);
  
  speed = 250;
  LeftFront(2.1,6.6,8.25,speed,servo_delay);
  RightFront(2.1,6.6,8.25,speed,servo_delay);
  LeftMid(10,6,5.5,speed/2,servo_delay);
  RightMid(10,6,5.5,speed/2,servo_delay);
  LeftBack(14.3,4.55,7.5,speed,servo_delay);
  RightBack(14.3,4.55,7.5,speed,servo_delay);
  delay(350);
  
  speed = 650;
  LeftFront(2.1,6.6,5.75,speed,servo_delay);
  RightBack(14.3,4.55,5,speed,servo_delay);
  delay(90);
  LeftFront(2.45,7.7,5.75,speed,servo_delay);
  delay(18);
  LeftFront(2.8,8.8,5.75,speed,servo_delay);
  delay(18);
  LeftFront(3.15,9.9,5.75,speed,servo_delay);
  RightBack(11,3.5,5,speed,servo_delay);
  delay(18);
  LeftFront(3.5,11,5.75,speed,servo_delay);
  delay(18);
  LeftFront(3.85,12.1,5.75,speed,servo_delay);
  delay(18);
  LeftFront(4.2,13.2,5.75,speed,servo_delay);
  RightBack(8.8,2.8,5,speed,servo_delay);
  delay(18);
  LeftFront(3.85,12.1,8.25,speed,servo_delay);
  RightBack(8.8,2.8,7.5,speed,servo_delay);
  delay(100);
  
  RightFront(2.1,6.6,5.75,speed,servo_delay);
  LeftBack(14.3,4.55,5,speed,servo_delay);
  delay(90);
  RightFront(2.45,7.7,5.75,speed,servo_delay);
  delay(18);
  RightFront(2.8,8.8,5.75,speed,servo_delay);
  delay(18);
  RightFront(3.15,9.9,5.75,speed,servo_delay);
  LeftBack(11,3.5,5,speed,servo_delay);
  delay(18);
  RightFront(3.5,11,5.75,speed,servo_delay);
  delay(18);
  RightFront(3.85,12.1,5.75,speed,servo_delay);
  delay(18);
  RightFront(4.2,13.2,5.75,speed,servo_delay);
  LeftBack(8.8,2.8,5,speed,servo_delay);
  delay(18);
  RightFront(3.85,12.1,8.25,speed,servo_delay);
  LeftBack(8.8,2.8,7.5,speed,servo_delay);
  delay(100);
  
  LeftMid(10,6,3.5,speed,servo_delay);
  RightMid(10,6,3.5,speed,servo_delay);
  delay(50);
  LeftMid(6,10,3.5,speed,servo_delay);
  RightMid(6,10,3.5,speed,servo_delay);
  delay(50);
  LeftMid(6,10,5.5,speed,servo_delay);
  RightMid(6,10,5.5,speed,servo_delay);
  // delay(25);
}

void post_ladder_rev(int roll_val){
  float z_front=3.9,z_mid=4.2,z_mid_increment=0.4, scale=0.9;
  if(roll_val>=-5){
    z_front=3.45;
    z_mid=5.5;
  }
  else if(roll_val>=7){
    z_front=3.45;
    z_mid=5.85;
  }
  speed = 350;
  LeftFront(3.85,12.1,z_front,speed,servo_delay);
  RightFront(3.85,12.1,z_front,speed,servo_delay);
  LeftMid(6,10,z_mid,speed/2,servo_delay);
  RightMid(6,10,z_mid,speed/2,servo_delay);
  LeftBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  RightBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  // delay(50);
  
  speed = 125;
  LeftFront(2.1,6.6,z_front,speed,servo_delay);
  RightFront(2.1,6.6,z_front,speed,servo_delay);
  LeftMid(10,6,z_mid,speed/2,servo_delay);
  RightMid(10,6,z_mid,speed/2,servo_delay);
  LeftBack(14.3*scale,4.55*scale,9.5,speed,servo_delay);
  RightBack(14.3*scale,4.55*scale,9.5,speed,servo_delay);
  delay(550);
  
  speed = 350;
  LeftFront(2.1,6.6,z_front-2.5,speed,servo_delay);
  RightBack(14.3*scale,4.55*scale,5,speed,servo_delay);
  delay(175);
  LeftFront(2.45,7.7,z_front-2.5,speed,servo_delay);
  delay(35);
  LeftFront(2.8,8.8,z_front-2.5,speed,servo_delay);
  delay(35);
  LeftFront(3.15,9.9,z_front-2.5,speed,servo_delay);
  LeftMid(10,6,z_mid+z_mid_increment,speed/2,servo_delay);
  RightMid(10,6,z_mid+z_mid_increment,speed/2,servo_delay);
  RightBack(11*scale,3.5*scale,5,speed,servo_delay);
  delay(35);
  LeftFront(3.5,11,z_front-2.5,speed,servo_delay);
  delay(35);
  LeftFront(3.85,12.1,z_front-2.5,speed,servo_delay);
  delay(35);
  LeftFront(4.2,13.2,z_front-2.5,speed,servo_delay);
  RightBack(8.8*scale,2.8*scale,5,speed,servo_delay);
  delay(35);
  LeftFront(3.85,12.1,z_front,speed,servo_delay);
  LeftMid(10,6,z_mid+(z_mid_increment*2),speed/2,servo_delay);
  RightMid(10,6,z_mid+(z_mid_increment*2),speed/2,servo_delay);
  RightBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  delay(175);
  
  RightFront(2.1,6.6,z_front-2.5,speed,servo_delay);
  LeftBack(14.3*scale,4.55*scale,5,speed,servo_delay);
  delay(175);
  RightFront(2.45,7.7,z_front-2.5,speed,servo_delay);
  delay(35);
  RightFront(2.8,8.8,z_front-2.5,speed,servo_delay);
  delay(35);
  RightFront(3.15,9.9,z_front-2.5,speed,servo_delay);
  LeftMid(10,6,z_mid+(z_mid_increment*3),speed/2,servo_delay);
  RightMid(10,6,z_mid+(z_mid_increment*3),speed/2,servo_delay);
  LeftBack(11*scale,3.5*scale,5,speed,servo_delay);
  delay(35);
  RightFront(3.5,11,z_front-2.5,speed,servo_delay);
  delay(35);
  RightFront(3.85,12.1,z_front-2.5,speed,servo_delay);
  delay(35);
  RightFront(4.2,13.2,z_front-2.5,speed,servo_delay);
  LeftBack(8.8*scale,2.8*scale,5,speed,servo_delay);
  delay(35);
  RightFront(3.85,12.1,z_front,speed,servo_delay);
  LeftMid(10,6,z_mid+(z_mid_increment*4),speed/2,servo_delay);
  RightMid(10,6,z_mid+(z_mid_increment*4),speed/2,servo_delay);
  LeftBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  delay(175);
  
  LeftMid(10,6,z_mid-3,speed,servo_delay);
  RightMid(10,6,z_mid-3,speed,servo_delay);
  delay(85);
  LeftMid(6,10,z_mid-3,speed,servo_delay);
  RightMid(6,10,z_mid-3,speed,servo_delay);
  delay(85);
  LeftMid(6,10,z_mid,speed,servo_delay);
  RightMid(6,10,z_mid,speed,servo_delay);
  // delay(25);
}

void post_ladder_test(int roll_val){
  float z_front=3.9,z_mid=4.3,z_mid_increment=0.4, scale=0.9;
  if(roll_val>=-5){
    z_front=3.45;
    z_mid=5.5;
  }
  else if(roll_val>=7){
    z_front=3.45;
    z_mid=5.85;
  }
  speed = 350;
  LeftFront(3.85,12.1,z_front,speed,servo_delay);
  RightFront(3.85,12.1,z_front,speed,servo_delay);
  LeftMid(6,10,z_mid,speed/2,servo_delay);
  RightMid(6,10,z_mid,speed/2,servo_delay);
  LeftBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  RightBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  // delay(50);
  
  speed = 125;
//  LeftFront(2.1,6.6,z_front,speed,servo_delay);
//  RightFront(2.1,6.6,z_front,speed,servo_delay);
  LeftMid(10,6,z_mid,speed/2,servo_delay);
  RightMid(10,6,z_mid,speed/2,servo_delay);
  LeftBack(14.3*scale,4.55*scale,9.5,speed,servo_delay);
  RightBack(14.3*scale,4.55*scale,9.5,speed,servo_delay);
  delay(550);
  
  speed = 350;
//  LeftFront(2.1,6.6,z_front-2.5,speed,servo_delay);
  RightBack(14.3*scale,4.55*scale,5,speed,servo_delay);
  delay(175);
//  LeftFront(2.45,7.7,z_front-2.5,speed,servo_delay);
  delay(35);
//  LeftFront(2.8,8.8,z_front-2.5,speed,servo_delay);
  delay(35);
//  LeftFront(3.15,9.9,z_front-2.5,speed,servo_delay);
  LeftMid(10,6,z_mid+z_mid_increment,speed/2,servo_delay);
  RightMid(10,6,z_mid+z_mid_increment,speed/2,servo_delay);
  RightBack(11*scale,3.5*scale,5,speed,servo_delay);
  delay(35);
//  LeftFront(3.5,11,z_front-2.5,speed,servo_delay);
  delay(35);
//  LeftFront(3.85,12.1,z_front-2.5,speed,servo_delay);
  delay(35);
//  LeftFront(4.2,13.2,z_front-2.5,speed,servo_delay);
  RightBack(8.8*scale,2.8*scale,5,speed,servo_delay);
  delay(35);
//  LeftFront(3.85,12.1,z_front,speed,servo_delay);
  LeftMid(10,6,z_mid+(z_mid_increment*2),speed/2,servo_delay);
  RightMid(10,6,z_mid+(z_mid_increment*2),speed/2,servo_delay);
  RightBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  delay(175);
  
//  RightFront(2.1,6.6,z_front-2.5,speed,servo_delay);
  LeftBack(14.3*scale,4.55*scale,5,speed,servo_delay);
  delay(175);
//  RightFront(2.45,7.7,z_front-2.5,speed,servo_delay);
  delay(35);
//  RightFront(2.8,8.8,z_front-2.5,speed,servo_delay);
  delay(35);
//  RightFront(3.15,9.9,z_front-2.5,speed,servo_delay);
  LeftMid(10,6,z_mid+(z_mid_increment*3),speed/2,servo_delay);
  RightMid(10,6,z_mid+(z_mid_increment*3),speed/2,servo_delay);
  LeftBack(11*scale,3.5*scale,5,speed,servo_delay);
  delay(35);
//  RightFront(3.5,11,z_front-2.5,speed,servo_delay);
  delay(35);
//  RightFront(3.85,12.1,z_front-2.5,speed,servo_delay);
  delay(35);
//  RightFront(4.2,13.2,z_front-2.5,speed,servo_delay);
  LeftBack(8.8*scale,2.8*scale,5,speed,servo_delay);
  delay(35);
//  RightFront(3.85,12.1,z_front,speed,servo_delay);
  LeftMid(10,6,z_mid+(z_mid_increment*4),speed/2,servo_delay);
  RightMid(10,6,z_mid+(z_mid_increment*4),speed/2,servo_delay);
  LeftBack(8.8*scale,2.8*scale,9.5,speed,servo_delay);
  delay(175);
  
  LeftMid(10,6,z_mid-3,speed,servo_delay);
  RightMid(10,6,z_mid-3,speed,servo_delay);
  delay(85);
  LeftMid(6,10,z_mid-3,speed,servo_delay);
  RightMid(6,10,z_mid-3,speed,servo_delay);
  delay(85);
  LeftMid(6,10,z_mid,speed,servo_delay);
  RightMid(6,10,z_mid,speed,servo_delay);
  // delay(25);
}

void lunge(){
  //1
  LeftBack(12,8,5.5,speed,servo_delay);
  RightBack(12,8,5.5,speed,servo_delay);
  LeftMid(10.83,5.17,4.75,speed,servo_delay);
  RightMid(10.83,5.17,4.75,speed,servo_delay);
  LeftFront(8,4,4,speed,servo_delay);
  RightFront(8,4,4,speed,servo_delay); delay(1000);

  default_state(); delay(1000);
}
