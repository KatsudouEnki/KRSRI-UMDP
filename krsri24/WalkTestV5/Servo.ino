void servo_movement(String name, int state){
  /*
   * 
   * buka 
   *  state
     *  0 = tutup
     *  1 = buka
   * angkat
   *  state
     *  0 = angkat
     *  1 = turun (scan)
     *  2 = turun (ambil)
   * putar
   *  state
     *  0 = tengah
     *  1 = kanan (scan)
     *  2 = kanan (sz)
     *  3 = kiri (scan)
     *  4 = kiri (sz)
   */
  if(name=="buka"){
    if(state==0){
      servoBuka.write(0);
    }
    else if(state==1){
      servoBuka.write(90);
    }
    else{
      int val=servoBuka.read();
      servoBuka.write(val);
    }
  }
  else if(name == "angkat"){
    if(state==0){
      servoAngkat.write(0);
    }
    else if(state==1){
      servoAngkat.write(90);
    }
    else if(state==2){
      servoAngkat.write(120);
    }
    else{
      int val=servoAngkat.read();
      servoAngkat.write(val);
    }
  }
  else if(name == "putar"){
    if(state==0){
      myservo.write(120);
    }
    else if(state==1){
      myservo.write(150);
    }
    else if(state==2){
      myservo.write(170);
    }
    else if(state==3){
      myservo.write(90);
    }
    else if(state==4){
      myservo.write(60);
    }
    else{
      int val=myservo.read();
      myservo.write(val);
    }
  }
}
