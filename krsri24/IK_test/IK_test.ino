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
  float test_x= 8,
        test_y= 8,
        test_z= 3,
        default_x=8,
        default_y=8,
        default_z=4.5;
  int speed=500;

//Kiri Depan*
  Dynamixel.moveSpeed(3, dynamixelGammaMid(test_x,test_y,test_z,0,0),speed);
  Dynamixel.moveSpeed(2, dynamixelAlpha(test_x,test_y,test_z,0,1), speed);
  Dynamixel.moveSpeed(1, dynamixelBeta(test_x,test_y,test_z,0,0), speed);

////Kiri Tengah*
//  Dynamixel.moveSpeed(9, dynamixelGammaMid(test_x,test_y,test_z,0,0),speed);
//  Dynamixel.moveSpeed(8, dynamixelAlpha(test_x,test_y,test_z,0,1), speed);
//  Dynamixel.moveSpeed(7, dynamixelBeta(test_x,test_y,test_z,0,0), speed);
//kiri belakang
  Dynamixel.moveSpeed(15, dynamixelGamma(test_x,test_y,test_z,0,0), speed);
  Dynamixel.moveSpeed(14, dynamixelAlpha(test_x,test_y,test_z,0,1), speed);
  Dynamixel.moveSpeed(13, dynamixelBeta(test_x,test_y,test_z,0,0), speed);
//////Kaki kanan
/////*Kanan Depan*/
//  Dynamixel.moveSpeed(4, dynamixelGamma(test_x,test_y,test_z,1,0),speed);
//  Dynamixel.moveSpeed(5, dynamixelAlpha(test_x,test_y,test_z,0,0), speed);
//  Dynamixel.moveSpeed(6, dynamixelBeta(test_x,test_y,test_z,0,0), speed);
//
///*Kanan Tengah*/
  Dynamixel.moveSpeed(10, dynamixelGammaMid(test_x,test_y,test_z,1,0),speed);
  Dynamixel.moveSpeed(11, dynamixelAlpha(test_x,test_y,test_z,0,0), speed);
  Dynamixel.moveSpeed(12, dynamixelBeta(test_x,test_y,test_z,0,0), speed);
//
/////*Kanan Belakang*/
//  Dynamixel.moveSpeed(16, dynamixelGammaMid(test_x,test_y,test_z,1,0),speed);
//  Dynamixel.moveSpeed(17, dynamixelAlpha(test_x,test_y,test_z,0,0), speed);
//  Dynamixel.moveSpeed(18, dynamixelBeta(test_x,test_y,test_z,0,0), speed);
delay(5000);


//Kiri Depan*
  Dynamixel.moveSpeed(3, dynamixelGammaMid(default_x,default_y,default_z,0,0),speed);
  Dynamixel.moveSpeed(2, dynamixelAlpha(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(1, dynamixelBeta(default_x,default_y,default_z,0,0), speed);

//Kiri Tengah*
  Dynamixel.moveSpeed(9, dynamixelGammaMid(default_x,default_y,default_z,0,0),speed);
  Dynamixel.moveSpeed(8, dynamixelAlpha(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(7, dynamixelBeta(default_x,default_y,default_z,0,0), speed);
//kiri belakang
  Dynamixel.moveSpeed(15, dynamixelGamma(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(14, dynamixelAlpha(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(13, dynamixelBeta(default_x,default_y,default_z,0,0), speed);
//Kaki kanan
/*Kanan Depan*/
  Dynamixel.moveSpeed(4, dynamixelGamma(default_x,default_y,default_z,0,0),speed);
  Dynamixel.moveSpeed(5, dynamixelAlpha(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(6, dynamixelBeta(default_x,default_y,default_z,0,0), speed);
//
///*Kanan Tengah*/
  Dynamixel.moveSpeed(10, dynamixelGammaMid(default_x,default_y,default_z,0,0),speed);
  Dynamixel.moveSpeed(11, dynamixelAlpha(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(12, dynamixelBeta(default_x,default_y,default_z,0,0), speed);
//
///*Kanan Belakang*/
  Dynamixel.moveSpeed(16, dynamixelGammaMid(default_x,default_y,default_z,0,0),speed);
  Dynamixel.moveSpeed(17, dynamixelAlpha(default_x,default_y,default_z,0,0), speed);
  Dynamixel.moveSpeed(18, dynamixelBeta(default_x,default_y,default_z,0,0), speed);

delay(3000);


/////////////////////////////////////////Pin and ID/////////////////////////////////////
/*

//Kaki kiri
/*kiri Depan*
  Dynamixel.moveSpeed(5, 511,speed);
  Dynamixel.moveSpeed(11, 511, speed);
  Dynamixel.moveSpeed(1, 511, speed);

/*Kiri Tengah*
  Dynamixel.moveSpeed(22, 511,speed);
  Dynamixel.moveSpeed(17, 511, speed);////
  Dynamixel.moveSpeed(8, 511, speed);

/*Kiri Belakang*
  Dynamixel.moveSpeed(22, 511,speed);
  Dynamixel.moveSpeed(11, 511, speed);////
  Dynamixel.moveSpeed(9, 511, speed);


//Kaki kanan
/*Kanan Depan*
  Dynamixel.moveSpeed(5, 511,speed);
  Dynamixel.moveSpeed(10, 511, speed);////
  Dynamixel.moveSpeed(15, 511, speed);

/*Kanan Tengah*
  Dynamixel.moveSpeed(10, 511,speed);////
  Dynamixel.moveSpeed(5, 511, speed);
  Dynamixel.moveSpeed(14, 511, speed);

/*Kanan Belakang*
  Dynamixel.moveSpeed(1, 511,speed);
  Dynamixel.moveSpeed(18, 511, speed);////
  Dynamixel.moveSpeed(18, 511, speed);
  
*/
}
