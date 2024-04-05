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


#define ID_coxa 1
#define ID_femur 5
#define ID_tibia 18

float coxa=6.5, femur=5, tibia=7;
//float coxa=4.5, femur=5, tibia=7;

float x_limit=11.5, y_limit=11.5, z_limit=3;

float beta_offset=50, alpha_offset=50;

double gamma_cal(double x, double y, double z){
  double gamma=degrees(atan(x/y));
  gamma=round(gamma);
  return gamma;
}

double beta_cal(double x, double y, double z){
  double L1=sqrt(pow(x,2)+pow(y,2));
  double L=sqrt(pow(L1-coxa,2)+pow(z,2));
  double beta=degrees(acos((pow(tibia,2)+pow(femur,2)-pow(L,2))/(2*tibia*femur)));
  beta=round(beta);
  return beta;
} 
double alpha_sum(double x, double y, double z){
  double L1=sqrt(pow(x,2)+pow(y,2));
  double L=sqrt(pow(L1-coxa,2)+pow(z,2));
  double alpha1=degrees(acos(z/L)); //L mestinya L1?  
  double alpha2=degrees(acos((pow(femur,2)+pow(L,2)-pow(tibia,2))/(2*femur*L)));//B
  double alpha_total= alpha2+alpha1;
  alpha_total=round(alpha_total);
  return alpha_total;
  }

int AngleCalc(float angle, int mirror)
{
  float angle_calc = (angle/300)*1023;
  if(mirror == 1){
    int mirror_angle = (angle_calc - 511)*-1;
    mirror_angle += 511;
    return mirror_angle;
  }
  else{
    return angle_calc;  
  }
}
int dynamixelGamma(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_gamma = gamma_cal(x_limit,y_limit,z_limit)-gamma_cal(x_val,y_val,z_val);
  if(mirror_inverse == 1){
    return AngleCalc(30+(dynamixel_gamma*-1),mirror_dynamixel);
  }
  else{
    return AngleCalc(30+dynamixel_gamma,mirror_dynamixel);
  }
}
int dynamixelGammaMid(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_gamma = gamma_cal(x_limit,y_limit,z_limit)-gamma_cal(x_val,y_val,z_val);
  if(mirror_inverse == 1){
    return AngleCalc(25+(dynamixel_gamma*-1),mirror_dynamixel);
  }
  else{
    return AngleCalc(25+dynamixel_gamma,mirror_dynamixel);
  }
}
int dynamixelAlpha(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_alpha = alpha_sum(x_limit,y_limit,z_limit) - alpha_sum(x_val,y_val,z_val);
  if(mirror_inverse == 1){
    return AngleCalc(150+(dynamixel_alpha*-1), mirror_dynamixel);
  }
  else{
    return AngleCalc(150+dynamixel_alpha, mirror_dynamixel);
  }
}

int dynamixelBeta(double x_val,double y_val,double z_val,int mirror_inverse,int mirror_dynamixel)
{
  int dynamixel_beta = beta_cal(x_limit,y_limit,z_limit) - beta_cal(x_val,y_val,z_val);
  if(mirror_inverse == 1){
     return AngleCalc(235+(dynamixel_beta*-1), mirror_dynamixel);
  }
  else{
    return AngleCalc(235+dynamixel_beta, mirror_dynamixel);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial3);
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

int speed=700, servo_delay=0;

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
  RightFront(8,5,4,speed,servo_delay);
  LeftMid(9.4,9.4,4,speed,servo_delay);
  RightBack(5,8,4,speed,servo_delay);

  LeftFront(8,5,4.5,speed,servo_delay);
  RightMid(9.4,9.4,4.5,speed,servo_delay);
  LeftBack(5,8,4.5,speed,servo_delay);
  
  // delay(20);
}

void crabwalk_left_fast(){
  //1
  RightFront(8,5,4.5,speed,servo_delay);
  LeftMid(9.4,9.4,4.5,speed,servo_delay);
  RightBack(5,8,4.5,speed,servo_delay);

  delay(5);

  LeftFront(8,5,4,speed,servo_delay);
  RightMid(9.4,9.4,4,speed,servo_delay);
  LeftBack(5,8,4,speed,servo_delay);
  
  // delay(10);

  RightFront(9,5,4.5,speed,servo_delay);
  LeftMid(8.7,8.7,4.5,speed,servo_delay);
  RightBack(5,9,4.5,speed,servo_delay);
  
  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  RightFront(11,5,4.5,speed,servo_delay);
  LeftMid(7.3,7.3,4.5,speed,servo_delay);
  RightBack(5,11,4.5,speed,servo_delay);

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

  LeftFront(11,5,4.5,speed,servo_delay);
  RightMid(7.3,7.3,4.5,speed,servo_delay);
  LeftBack(5,11,4.5,speed,servo_delay);

  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  LeftFront(9,5,4.5,speed,servo_delay);
  RightMid(8.7,8.7,4.5,speed,servo_delay);
  LeftBack(5,9,4.5,speed,servo_delay);

  //4
  RightFront(8,5,4,speed,servo_delay);
  LeftMid(9.4,9.4,4,speed,servo_delay);
  RightBack(5,8,4,speed,servo_delay);

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

void crabwalk_right_fast(){
  //1
  RightFront(12,5,4.5,speed,servo_delay);
  LeftMid(6.6,6.6,4.5,speed,servo_delay);
  RightBack(5,12,4.5,speed,servo_delay);

  delay(5);

  LeftFront(12,5,4,speed,servo_delay);
  RightMid(6.6,6.6,4,speed,servo_delay);
  LeftBack(5,12,4,speed,servo_delay);
  
  // delay(10);

  RightFront(11,5,4.5,speed,servo_delay);
  LeftMid(7.3,7.3,4.5,speed,servo_delay);
  RightBack(5,11,4.5,speed,servo_delay);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  RightFront(9,5,4.5,speed,servo_delay);
  LeftMid(8.7,8.7,4.5,speed,servo_delay);
  RightBack(5,9,4.5,speed,servo_delay);
  
  //2
  LeftFront(8,5,4,speed,servo_delay);
  RightMid(9.4,9.4,4,speed,servo_delay);
  LeftBack(5,8,4,speed,servo_delay);

  RightFront(8,5,4.5,speed,servo_delay);
  LeftMid(9.4,9.4,4.5,speed,servo_delay);
  RightBack(5,8,4.5,speed,servo_delay);

  // delay(20);

  //3
  LeftFront(8,5,4.5,speed,servo_delay);
  RightMid(9.4,9.4,4.5,speed,servo_delay);
  LeftBack(5,8,4.5,speed,servo_delay);

  delay(5);

  RightFront(8,5,4,speed,servo_delay);
  LeftMid(9.4,9.4,4,speed,servo_delay);
  RightBack(5,8,4,speed,servo_delay);
  
  // delay(10);

  LeftFront(9,5,4.5,speed,servo_delay);
  RightMid(8.7,8.7,4.5,speed,servo_delay);
  LeftBack(5,9,4.5,speed,servo_delay);

  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  LeftFront(11,5,4.5,speed,servo_delay);
  RightMid(7.3,7.3,4.5,speed,servo_delay);
  LeftBack(5,11,4.5,speed,servo_delay);

  //4
  RightFront(12,5,4,speed,servo_delay);
  LeftMid(6.6,6.6,4,speed,servo_delay);
  RightBack(5,12,4,speed,servo_delay);

  LeftFront(12,5,4.5,speed,servo_delay);
  RightMid(6.6,6.6,4.5,speed,servo_delay);
  LeftBack(5,12,4.5,speed,servo_delay);
  
  // delay(20);
}

/* COMMANDS LIST
1. default_state()
2. walk()
3. walk_fast()
4. walk_fast_obstacle()
5. walk_fast_balls()
6. reverse()
7. reverse_fast()
8. turn_left_obstacle()
9. turn_left_fast()
10. turn_right_obstacle()
11. turn_right_fast()
12. crabwalk_left()
13. crabwalk_left_fast()
14. crabwalk_right()
15. crabwalk_right_fast()
*/