float coxa=7.5, femur=5, tibia=6;

float x_limit=12.5, y_limit=12.5, z_limit=3;

float x_val=10, y_val=10, z_val=8;

float beta_offset=50, alpha_offset=50;

void setup() {
  Serial.begin(9600);
  Serial.print(gamma_cal(x_val,y_val));
  Serial.print(" : ");
  Serial.print(beta_cal(x_val,y_val,z_val));
  Serial.print(" : ");
  Serial.println(alpha_sum(x_val,y_val,z_val));
  
} 

double gamma_cal(double x, double y){
  double gamma=degrees(atan(x/y));
  return gamma;
}

double beta_cal(double x, double y, double z){
  double L1=sqrt(pow(x,2)+pow(y,2));
  double L=sqrt(pow(L1-coxa,2)+pow(z,2));
  double beta=degrees(acos((pow(tibia,2)+pow(femur,2)-pow(L,2))/(2*tibia*femur)));
  return beta;
} 
float alpha_sum(double x, double y, double z){
  double L1=sqrt(pow(x,2)+pow(y,2));
  double L=sqrt(pow(L1-coxa,2)+pow(z,2));
  double alpha1=degrees(acos(z/L));
  double alpha2=degrees(acos((pow(femur,2)+pow(L,2)-pow(tibia,2))/(2*femur*L)));
  double alpha_total= alpha1+alpha2;
  return alpha_total;
  }
void loop() {

}
