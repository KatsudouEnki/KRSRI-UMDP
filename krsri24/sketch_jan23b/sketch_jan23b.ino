#include <FlexiTimer2.h>
#include <NewPing.h>

#define SONAR_NUM 4      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

long now[SONAR_NUM];
long lastMeasure[SONAR_NUM] = {0,0,0};
int sensor[SONAR_NUM];

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(10, 10, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(11, 11, MAX_DISTANCE),
  NewPing(12, 12, MAX_DISTANCE),
  NewPing(13, 13, MAX_DISTANCE)
};

//int callUs(int pin)
//{
//  return sonar[pin].ping_cm();  
//}

void tasks()
{
  for (int i = 0; i < SONAR_NUM; i++){
    now[i] = millis();
    if (now[i] - lastMeasure[i] > 35+(2*i)) {
      lastMeasure[i] = now[i];
      sensor[i] = sonar[i].ping_cm();
    }
  }
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  
  tasks();
  Serial.print(sensor[0]);
  Serial.print("\t");
  Serial.print(sensor[1]);
  Serial.print("\t");
  Serial.print(sensor[2]);
  Serial.print("\t");
  Serial.println(sensor[3]);
  delay(60);  
}
