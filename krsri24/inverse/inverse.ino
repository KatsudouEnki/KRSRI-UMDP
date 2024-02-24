float coxa=7.5, femur=5, tibia=6; //panjang tiap ruas kaki

float x_limit=12.5, y_limit=12.5, z_limit=4; //batas koordinat tiap ruas kaki

float x_val=10, y_val=10, z_val=3; //letak koordinat tiap ruas kaki

float beta_offset=50, alpha_offset=50;

double gamma_calc(double x, double y){
  double gamma=degrees(atan(x/y));
  return gamma;
}

double beta_calc(double x, double y, double z){
  double L1=sqrt(pow(x,2)+sq(y));
  double L=sqrt(sq(L1-coxa)+sq(z));
  double beta=degrees(acos((pow(tibia,2)+pow(femur,2)-pow(L,2))/(2*tibia*femur)));
  return beta;
}

double alpha_calc(double x, double y, double z){
  double L1=sqrt(sq(x)+sq(y));
  double L=sqrt(sq(L1-coxa)+sq(z));
  double alpha1=degrees(acos(z/L));
  double alpha2=degrees(acos((sq(femur)+sq(L)-sq(tibia))/(2*femur*L)));
  double alpha_total=alpha1+alpha2;
  return alpha_total;
}

void setup() {
  Serial.begin(9600);
  Serial.println(sq(4));
  Serial.print("Gamma = ");
  Serial.println(gamma_calc(x_val, y_val));
  Serial.print("Beta = ");
  Serial.println(beta_calc(x_val, y_val, z_val));
  Serial.print("Alpha = ");
  Serial.println(alpha_calc(x_val, y_val, z_val));
}

void loop() {
  // put your main code here, to run repeatedly:
}
