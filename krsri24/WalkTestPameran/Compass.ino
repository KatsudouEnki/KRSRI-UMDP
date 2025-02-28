void compass(){
  /* Get a new sensor event */
  display.clearDisplay();
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  // Serial.print("X: ");
  // Serial.print(event.orientation.x, 4);
  // Serial.print("\tY: ");
  // Serial.print(event.orientation.y, 4);
  // Serial.print("\tZ: ");
  // Serial.print(event.orientation.z, 4);

  /* Optional: Display calibration status */
  displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();

  /* New line for the next sample */
  Serial.println("");

  

  azimuth = event.orientation.x;
  roll    = event.orientation.y;
  pitch   = event.orientation.z;
  Serial.println(azimuth);
  /**/
  display.setCursor(0,0);
  display.print("bearing ");
  display.print(azimuth);

  display.setCursor(0,15);
  display.print("pitch ");
  display.print(pitch,DEC);

  display.setCursor(0,30);
  display.print("Roll ");
  display.print(roll,DEC);
  display.display();
  /**/
  /* Wait the specified delay before requesting new data */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}


void bno_init(){
  if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//        while (1);
    }
    int eeAddress = 0;
    long bnoID;
    bool foundCalib = false;

    EEPROM.get(eeAddress, bnoID);
//    if(digitalRead(10) == HIGH){//////used after adding switch for calibrate compass offset
//      bnoID=255;
//    }

//    if(digitalRead(10) == HIGH){
//      display.clearDisplay();
//      display.print("Please Release The Button");
//      display.display();
//      while(digitalRead(10) == HIGH){
//        delay(100);
//      }
//      delay(10);
//      display.clearDisplay();
//      display.print("Entering Compass Offset Calibration Mode");
//      ///LED///
//      bnoID=255;
//    }
    
    adafruit_bno055_offsets_t calibrationData;
    sensor_t sensor;
    
    /*
    *  Look for the sensor's unique ID at the beginning oF EEPROM.
    *  This isn't foolproof, but it's better than nothing.
    */
    bno.getSensor(&sensor);
    if (bnoID != sensor.sensor_id)
    {
        Serial.println("\nNo Calibration Data for this sensor exists in EEPROM");
        delay(500);
    }
    else
    {
        Serial.println("\nFound Calibration for this sensor in EEPROM.");
        eeAddress += sizeof(long);
        EEPROM.get(eeAddress, calibrationData);

        displaySensorOffsets(calibrationData);

        Serial.println("\n\nRestoring Calibration data to the BNO055...");
        bno.setSensorOffsets(calibrationData);

        Serial.println("\n\nCalibration data loaded into BNO055");
        foundCalib = true;
    }

    delay(1000);

    /* Display some basic information on this sensor */
    displaySensorDetails();

    /* Optional: Display current status */
    displaySensorStatus();

   /* Crystal must be configured AFTER loading calibration data into BNO055. */
    bno.setExtCrystalUse(true);

    sensors_event_t event;
    bno.getEvent(&event);
    /* always recal the mag as It goes out of calibration very often */
    if (foundCalib){
        Serial.println("Move sensor slightly to calibrate magnetometers");
//        while (!bno.isFullyCalibrated())
//        {
//            bno.getEvent(&event);
//            displayCalStatus();
//            delay(BNO055_SAMPLERATE_DELAY_MS);
//        }
    }
    else
    {
      Serial.println("Please Calibrate Sensor: ");
      while (!bno.isFullyCalibrated())
      {
          bno.getEvent(&event);

          Serial.print("X: ");
          Serial.print(event.orientation.x, 4);
          Serial.print("\tY: ");
          Serial.print(event.orientation.y, 4);
          Serial.print("\tZ: ");
          Serial.print(event.orientation.z, 4);

          /* Optional: Display calibration status */
          displayCalStatus();

          /* New line for the next sample */
          Serial.println("");

          /* Wait the specified delay before requesting new data */
          delay(BNO055_SAMPLERATE_DELAY_MS);
      }
      Serial.println("\nFully calibrated!");
      Serial.println("--------------------------------");
      Serial.println("Calibration Results: ");
      adafruit_bno055_offsets_t newCalib;
      bno.getSensorOffsets(newCalib);
      displaySensorOffsets(newCalib);
  
      Serial.println("\n\nStoring calibration data to EEPROM...");
  
      eeAddress = 0;
      bno.getSensor(&sensor);
      bnoID = sensor.sensor_id;
  
      EEPROM.put(eeAddress, bnoID);
  
      eeAddress += sizeof(long);
      EEPROM.put(eeAddress, newCalib);
      Serial.println("Data stored to EEPROM.");
  
      Serial.println("\n--------------------------------\n");
      delay(500);


        while(digitalRead(10)==LOW);
    }

}


void displaySensorDetails(void)
{
    sensor_t sensor;
    bno.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor:       "); Serial.println(sensor.name);
    Serial.print("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
    Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
    Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
    */
/**************************************************************************/
void displaySensorStatus(void)
{
    /* Get the system status values (mostly for debugging purposes) */
    uint8_t system_status, self_test_results, system_error;
    system_status = self_test_results = system_error = 0;
    bno.getSystemStatus(&system_status, &self_test_results, &system_error);

    /* Display the results in the Serial Monitor */
    Serial.println("");
    Serial.print("System Status: 0x");
    Serial.println(system_status, HEX);
    Serial.print("Self Test:     0x");
    Serial.println(self_test_results, HEX);
    Serial.print("System Error:  0x");
    Serial.println(system_error, HEX);
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
    */
/**************************************************************************/
void displayCalStatus(void)
{
    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    /* The data should be ignored until the system calibration is > 0 */
    Serial.print("\t");
    if (!system)
    {
        Serial.print("! ");
    }

    /* Display the individual values */
    Serial.print("Sys:");
    Serial.print(system, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel, DEC);
    Serial.print(" M:");
    Serial.print(mag, DEC);
    display.setCursor(0,45);
    display.print("Sys:");
    display.print(system, DEC);
    display.print(" G:");
    display.print(gyro, DEC);
    display.print(" A:");
    display.print(accel, DEC);
    display.print(" M:");
    display.print(mag, DEC);
}

/**************************************************************************/
/*
    Display the raw calibration offset and radius data
    */
/**************************************************************************/
void displaySensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
    Serial.print("Accelerometer: ");
    Serial.print(calibData.accel_offset_x); Serial.print(" ");
    Serial.print(calibData.accel_offset_y); Serial.print(" ");
    Serial.print(calibData.accel_offset_z); Serial.print(" ");

    Serial.print("\nGyro: ");
    Serial.print(calibData.gyro_offset_x); Serial.print(" ");
    Serial.print(calibData.gyro_offset_y); Serial.print(" ");
    Serial.print(calibData.gyro_offset_z); Serial.print(" ");

    Serial.print("\nMag: ");
    Serial.print(calibData.mag_offset_x); Serial.print(" ");
    Serial.print(calibData.mag_offset_y); Serial.print(" ");
    Serial.print(calibData.mag_offset_z); Serial.print(" ");

    Serial.print("\nAccel Radius: ");
    Serial.print(calibData.accel_radius);

    Serial.print("\nMag Radius: ");
    Serial.print(calibData.mag_radius);
}

//Fungsi untuk menentukan arah putar
int HeadingJustification(int h, int start_point, int range, int space, char arah){
    int f;
    int offset;
    range = range-space;
    if(arah =='p'){
        start_point =start_point+space;
    }
    else{
        start_point =start_point-space;
        start_point = (start_point - range)%360;
        if (start_point<0) start_point=start_point+360;
    }
    if(start_point+range >=360) offset=360-start_point;
    else offset=0;
    
    h=(h+offset)%360;
    start_point=(start_point+offset)%360;
    
    if( (h>= start_point) && h <=start_point +range){ return 1; }
    else{ return 0; }
}

int galatArahHitung(int arahSet, int arahUkur){
  /**
   * menghitung galat arah kompas dan memberikan nilai -179 s/d 180
   * arahSet = set point arah kompas
   * arahUkur = arah kompas terukur oleh sensor
   * jika memberikan nilai 0 berarti arahUkur sama dengan arahSet
   * jika memberikan nilai 1 s/d 180 berarti melewati set point dengan arah clockwise sebesar nilai yang dikembalikan
   * jika memberikan nilai -1 s/d -179 berarti melewati set point dengan arah counterclockwise sebesar nilai yang dikembalikan
   */
    
    int galat;
    galat = arahUkur - arahSet;

    //menghitung modulo 360 deraja
    galat = galat % 360;//sisa pembagian bahasa C, bukan modulo yang sesuai definisi
    galat = (galat < 0) ? (galat + 360) : galat;//menjadikan sisa pembagian di atas menjadi modulo yang sesuai definisi
    
    if (galat <= 180)
        return galat;
    else
        return (galat - 360);
}
