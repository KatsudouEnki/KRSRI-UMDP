#include <DynamixelSerial.h>

#define ID_coxa 1
#define ID_femur 5
#define ID_tibia 18

float coxa=4.5, femur=5, tibia=7;

float x_limit=11.5, y_limit=11.5, z_limit=3;

float beta_offset=50, alpha_offset=50;

int speed=300;
  int servo_delay=3;
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

void setup() {
  Serial.begin(9600);
  Dynamixel.setSerial(&Serial);
  Dynamixel.begin(1000000, 2);
  Serial.println("test");
  float test_x= 8,
        test_y= 8,
        test_z= 3,
        
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

}
void loop(){
  
  walk();
}
void walk(){
  //1
  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(10);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(20);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(10);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(20);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(30);
}

void walk_fast(){
  //1
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  delay(10);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(20);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  
  RightBack(10,5,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(10);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(20);

  //4
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(30);
}

void reverse(){
  //1
  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(10);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(20);

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

  delay(10);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(20);

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
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  delay(10);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(20);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(10);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(20);

  //4
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(30);
}

void turn_left(){
  //1
  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(20);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(40);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(60);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(20);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(40);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(60);
}

void turn_left_fast(){
  //1
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  delay(20);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(40);

  //2
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);
  
  delay(60);

  //3
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  delay(20);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(40);

  //4
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(60);
}

void turn_right(){
  //1
  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(20);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(40);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(60);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(20);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(40);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(60);
}

void turn_right_fast(){
  //1
  LeftFront(10,5,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(10,5,3,speed,servo_delay);

  delay(20);

  RightFront(10,5,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(10,5,4.5,speed,servo_delay);

  delay(40);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(10,5,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(10,5,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);
  
  delay(60);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(10,5,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(20);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(10,5,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(40);

  //4
  LeftFront(10,5,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(10,5,4.5,speed,servo_delay);

  RightFront(10,5,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(10,5,3,speed,servo_delay);
  
  delay(60);
}

void walk_right_front(){
  //1
  LeftFront(8,8,3,speed,servo_delay);
  RightMid(8,8,3,speed,servo_delay);
  LeftBack(8,8,3,speed,servo_delay);

  delay(10);

  RightFront(5,10,4.5,speed,servo_delay);
  LeftMid(5,10,4.5,speed,servo_delay);
  RightBack(5,10,4.5,speed,servo_delay);

  delay(20);

  //2
  LeftFront(5,10,3,speed,servo_delay);
  RightMid(5,10,3,speed,servo_delay);
  LeftBack(5,10,3,speed,servo_delay);

  RightFront(8,8,4.5,speed,servo_delay);
  LeftMid(8,8,4.5,speed,servo_delay);
  RightBack(8,8,4.5,speed,servo_delay);
  
  delay(30);

  //3
  LeftFront(5,10,4.5,speed,servo_delay);
  RightMid(5,10,4.5,speed,servo_delay);
  LeftBack(5,10,4.5,speed,servo_delay);

  delay(10);

  RightFront(8,8,3,speed,servo_delay);
  LeftMid(8,8,3,speed,servo_delay);
  RightBack(8,8,3,speed,servo_delay);
  
  delay(20);

  //4
  LeftFront(8,8,4.5,speed,servo_delay);
  RightMid(8,8,4.5,speed,servo_delay);
  LeftBack(8,8,4.5,speed,servo_delay);

  RightFront(5,10,3,speed,servo_delay);
  LeftMid(5,10,3,speed,servo_delay);
  RightBack(5,10,3,speed,servo_delay);
  
  delay(30);
}
