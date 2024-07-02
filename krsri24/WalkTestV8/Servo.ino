void servo_movement(String name, int state){
  /*
   * 
   * buka 
     *  state
       *  0 = tutup
       *  1 = buka
       *  2 = grip korban
       *  3 = release
   * angkat
     *  state
       *  0 = angkat
       *  1 = turun (scan)
       *  2 = turun (ambil)
       *  3 = angkat sedikit setelah ambil
       *  4 = Tangga
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
      servoBuka.write(100);
    }
    else if(state==1){
      servoBuka.write(55);
    }
    else if(state==2){
      servoBuka.write(110);
    }
    else if(state==3){
      servoBuka.write(40);
    }
   else if(state==4){
     servoBuka.write(70);
   }
    else{
      int val=servoBuka.read();
      servoBuka.write(val);
    }
  }
  else if(name == "angkat"){
    if(state==0){
      //servoAngkat.write(20);
      servoAngkat.write(130);
      Dynamixel.moveSpeed(19,825, 500);
    }
    else if(state==1){
      servoAngkat.write(140);
      Dynamixel.moveSpeed(19,200, 300);
    }
    else if(state==2){
//      servoAngkat.write(130);
      Dynamixel.moveSpeed(19,300, 150);
      delay(1000);
//      for(int i=170; i>=130; i++){
        servoAngkat.write(100);
//        delay(10);
//      }
    }
    else if(state==3){
      servoAngkat.write(80);
      Dynamixel.moveSpeed(19,200, 300);
    }
    else if(state==4){
      servoAngkat.write(80);
      Dynamixel.moveSpeed(19,400, 300);
    }
    else if(state==5){
      servoAngkat.write(100);
      Dynamixel.moveSpeed(19,275, 300);
    }
    else if(state==6){
      servoAngkat.write(170);
      Dynamixel.moveSpeed(19,400, 300);
    }
    else if(state==7){
      servoAngkat.write(100);
      Dynamixel.moveSpeed(19,350, 150);
      for(int i =100; i > 60; i--){
        servoAngkat.write(i);
        delay(8);
      }
    }
    else{
      int val=servoAngkat.read();
      servoAngkat.write(val);
    }
  }
  else if(name == "putar"){
    int posisi_awal=102;
    if(state==0){
      myservo.write(posisi_awal);
    }
    else if(state==1){
      myservo.write(posisi_awal+20);
    }
    else if(state==2){
      myservo.write(posisi_awal+35);
    }
    else if(state==3){
      myservo.write(posisi_awal-20);
    }
    else if(state==4){
      myservo.write(posisi_awal-35);
    }
    else{
      int val=myservo.read();
      myservo.write(val);
    }
  }
}
