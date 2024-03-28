#include <DynamixelSerial.h>

#define ID_coxa 1
#define ID_femur 5
#define ID_tibia 18

float coxa=6.5, femur=5, tibia=7;

float x_limit=11.5, y_limit=11.5, z_limit=3;

float beta_offset=50, alpha_offset=50;

double gamma_cal(double x, double y, double z){
  double gamma=degrees(atan(x/y));
  return gamma;
}

double beta_cal(double x, double y, double z){
  double L1=sqrt(pow(x,2)+pow(y,2));
  double L=sqrt(pow(L1-coxa,2)+pow(z,2));
  double beta=degrees(acos((pow(tibia,2)+pow(femur,2)-pow(L,2))/(2*tibia*femur)));
  return beta;
} 
double alpha_sum(double x, double y, double z){
  double L1=sqrt(pow(x,2)+pow(y,2));
  double L=sqrt(pow(L1-coxa,2)+pow(z,2));
  double alpha1=degrees(acos(z/L));
  double alpha2=degrees(acos((pow(femur,2)+pow(L,2)-pow(tibia,2))/(2*femur*L)));
  double alpha_total= alpha1+alpha2;
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
  Dynamixel.setSerial(&Serial);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  float test_x= 8,
        test_y= 8,
        test_z= 2,
        
        default_x=8,
        default_y=8,
        default_z=4.5;
        
  Serial.println(dynamixelGammaMid(test_x,test_y,test_z,0,0));
  Serial.println(dynamixelAlpha(test_x,test_y,test_z,0,0));
  Serial.println(dynamixelBeta(test_x,test_y,test_z,0,0));
  
  Serial.println(dynamixelGammaMid(default_x,default_y,default_z,0,0));
  Serial.println(dynamixelAlpha(default_x,default_y,default_z,0,0));
  Serial.println(dynamixelBeta(default_x,default_y,default_z,0,0));
  delay(2000);
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

void loop() {
  // put your main code here, to run repeatedly:
  float test_x= 10,
        test_y= 5,
        test_z= 3,
        step_x= 10,
        step_y= 5,
        step_z=5,
        default_x=8,
        default_y=8,
        default_z=4.5;
  int speed=300,Servo_delay=5;
  
  LeftFront(default_x,default_y,default_z,speed,10);
  LeftMid(default_x,default_y,default_z,speed,10);
  LeftBack(default_x,default_y,default_z,speed,10);
  RightFront(default_x,default_y,default_z,speed,10);
  RightMid(default_x,default_y,default_z,speed,10);
  RightBack(default_x,default_y,default_z,speed,10);
  delay(5000);
  /**/
  while(true){
    LeftFront(test_x,test_y,test_z,speed,10);
    LeftBack(test_x,test_y,test_z,speed,10);
    RightMid(test_x,test_y,test_z,speed,10);
    delay(100);
    LeftFront(step_x,step_y,step_z,speed,10);
    LeftBack(step_x,step_y,step_z,speed,10);
    RightMid(step_x,step_y,step_z,speed,10);
    delay(100);
    LeftFront(default_x,default_y,default_z,speed,10);
    LeftMid(test_x,test_y,test_z,speed,10);
    LeftBack(default_x,default_y,default_z,speed,10);
    RightFront(test_x,test_y,test_z,speed,10);
    RightMid(default_x,default_y,default_z,speed,10);
    RightBack(test_x,test_y,test_z,speed,10);
    delay(100);
    
    RightFront(test_x,test_y,test_z,speed,10);
    RightBack(test_x,test_y,test_z,speed,10);
    LeftMid(test_x,test_y,test_z,speed,10);
    delay(100);
    RightFront(step_x,step_y,step_z,speed,10);
    RightBack(step_x,step_y,step_z,speed,10);
    LeftMid(step_x,step_y,step_z,speed,10);
    delay(100);
    RightFront(default_x,default_y,default_z,speed,10);
    RightMid(test_x,test_y,test_z,speed,10);
    RightBack(default_x,default_y,default_z,speed,10);
    LeftFront(test_x,test_y,test_z,speed,10);
    LeftMid(default_x,default_y,default_z,speed,10);
    LeftBack(test_x,test_y,test_z,speed,10);
    delay(100);
  }
  /**/
}


void LeftFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(3, dynamixelGammaMid(x_val,y_val,z_val,0,0),speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(2, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(1, dynamixelBeta(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
}
void LeftMid(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(9, dynamixelGammaMid(x_val,y_val,z_val,0,0),speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(8, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(7, dynamixelBeta(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
}
void LeftBack(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(15, dynamixelGamma(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(14, dynamixelAlpha(x_val,y_val,z_val,0,1), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(13, dynamixelBeta(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
}

void RightFront(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(4, dynamixelGamma(x_val,y_val,z_val,1,0),speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(5, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(6, dynamixelBeta(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
}
void RightMid(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(10, dynamixelGammaMid(x_val,y_val,z_val,1,0),speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(11, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(12, dynamixelBeta(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
}
void RightBack(float x_val, float y_val,float z_val, int speed,int servo_delay){
  Dynamixel.moveSpeed(16, dynamixelGammaMid(x_val,y_val,z_val,1,0),speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(17, dynamixelAlpha(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
  Dynamixel.moveSpeed(18, dynamixelBeta(x_val,y_val,z_val,0,0), speed);
  delay(servo_delay);
}
