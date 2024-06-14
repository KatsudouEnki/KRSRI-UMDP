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
      servoBuka.write(107);//117
    }
    else if(state==1){
      servoBuka.write(70);
    }
    else if(state==2){
      servoBuka.write(125);//117
    }
    else if(state==3){
      servoBuka.write(40);
    }
    else if(state==4){
      servoBuka.write(55);
    }
    else{
      int val=servoBuka.read();
      servoBuka.write(val);
    }
  }
  else if(name == "angkat"){
    if(state==0){
      //servoAngkat.write(20);
      servoAngkat.write(10);
    }
    else if(state==1){
      servoAngkat.write(90);
    }
    else if(state==2){
      servoAngkat.write(120);
    }
    else if(state==3){
      servoAngkat.write(95);
    }
    else if(state==4){
      servoAngkat.write(70);
    }
    else if(state==5){
      servoAngkat.write(115);
    }
    else if(state==6){
      servoAngkat.write(90);
    }
    else if(state==7){
      servoAngkat.write(110);
    }
    else{
      int val=servoAngkat.read();
      servoAngkat.write(val);
    }
  }
  else if(name == "putar"){
    int posisi_awal=100;
    if(state==0){
      myservo.write(posisi_awal);
    }
    else if(state==1){
      myservo.write(posisi_awal+40);
    }
    else if(state==2){
      myservo.write(posisi_awal+50);
    }
    else if(state==3){
      myservo.write(posisi_awal-40);
    }
    else if(state==4){
      myservo.write(posisi_awal-50);
    }
    else{
      int val=myservo.read();
      myservo.write(val);
    }
  }
}
