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
