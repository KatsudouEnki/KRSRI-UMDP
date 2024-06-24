void default_state1() {
  LeftFront(8, 8, 4.5, speed, servo_delay);
  LeftMid(8, 8, 4.5, speed, servo_delay);
  LeftBack(8, 8, 4.5, speed, servo_delay);

  RightFront(8, 8, 4.5, speed, servo_delay);
  RightMid(8, 8, 4.5, speed, servo_delay);
  RightBack(8, 8, 4.5, speed, servo_delay);
}

void abc() {
  //1
  RightFront(5, 6, 4.5, speed, servo_delay);
  RightMid(5, 6, 4.5, speed, servo_delay);
  RightBack(5, 6, 4.5, speed, servo_delay);
  LeftFront(5, 6, 4.5, speed, servo_delay); 
  LeftMid(5, 6, 4.5, speed, servo_delay); LeftBack(5, 6, 4.5, speed, servo_delay);

  delay(700);

  RightFront(5, 10, 4.5, speed, servo_delay);
  RightMid(5, 10, 4.5, speed, servo_delay);
  RightBack(5, 10, 4.5, speed, servo_delay);
  LeftFront(5, 10, 4.5, speed, servo_delay);
  LeftMid(5, 10, 4.5, speed, servo_delay);
  LeftBack(5, 10, 4.5, speed, servo_delay);

  delay(700);

  //2
  RightFront(5, 6, 4.5, speed, servo_delay);
  RightMid(5, 6, 4.5, speed, servo_delay);
  RightBack(5, 6, 4.5, speed, servo_delay);
  LeftFront(5, 6, 4.5, speed, servo_delay);
  LeftMid(5, 6, 4.5, speed, servo_delay);
  LeftBack(5, 6, 4.5, speed, servo_delay);

  delay(700);

  RightFront(5, 10, 4.5, speed, servo_delay);
  RightMid(5, 10, 4.5, speed, servo_delay);
  RightBack(5, 10, 4.5, speed, servo_delay);
  LeftFront(5, 10, 4.5, speed, servo_delay);
  LeftMid(5, 10, 4.5, speed, servo_delay);
  LeftBack(5, 10, 4.5, speed, servo_delay);


  delay(700);

  //3
  RightFront(5, 6, 4.5, speed, servo_delay);
  RightMid(5, 6, 4.5, speed, servo_delay);
  RightBack(5, 6, 4.5, speed, servo_delay);
  LeftFront(5, 6, 4.5, speed, servo_delay);
  LeftMid(5, 6, 4.5, speed, servo_delay);
  LeftBack(5, 6, 4.5, speed, servo_delay);

  delay(700);

  RightFront(5, 10, 4.5, speed, servo_delay);
  RightMid(5, 10, 4.5, speed, servo_delay);
  RightBack(5, 10, 4.5, speed, servo_delay);
  LeftFront(5, 10, 4.5, speed, servo_delay);
  LeftMid(5, 10, 4.5, speed, servo_delay);
  LeftBack(5, 10, 4.5, speed, servo_delay);


  delay(700);

  //4
  RightFront(5, 6, 4.5, speed, servo_delay);
  RightMid(5, 6, 4.5, speed, servo_delay);
  RightBack(5, 6, 4.5, speed, servo_delay);
  LeftFront(5, 6, 4.5, speed, servo_delay);
  LeftMid(5, 6, 4.5, speed, servo_delay);
  LeftBack(5, 6, 4.5, speed, servo_delay);

  delay(700);

  RightFront(5, 10, 4.5, speed, servo_delay);
  RightMid(5, 10, 4.5, speed, servo_delay);
  RightBack(5, 10, 4.5, speed, servo_delay);
  LeftFront(5, 10, 4.5, speed, servo_delay);
  LeftMid(5, 10, 4.5, speed, servo_delay);
  LeftBack(5, 10, 4.5, speed, servo_delay);

  delay(700);
}

void low_walk() {
  //1
  RightFront(6.5, 8, 4.5, speed, servo_delay);
  LeftMid(6.5, 8, 4.5, speed, servo_delay);
  RightBack(6.5, 8, 4.5, speed, servo_delay);

  delay(5);

  LeftFront(8.5, 6, 3, speed, servo_delay);
  RightMid(8.5, 6, 3, speed, servo_delay);
  LeftBack(8.5, 6, 3, speed, servo_delay);

  // delay(25);

  //2
  LeftFront(6.5, 8, 3, speed, servo_delay);
  RightMid(6.5, 8, 3, speed, servo_delay);
  LeftBack(6.5, 8, 3, speed, servo_delay);

  RightFront(8.5, 6, 4.5, speed, servo_delay);
  LeftMid(8.5, 6, 4.5, speed, servo_delay);
  RightBack(8.5, 6, 4.5, speed, servo_delay);

  // delay(30);

  //3
  LeftFront(6.5, 8, 4.5, speed, servo_delay);
  RightMid(6.5, 8, 4.5, speed, servo_delay);
  LeftBack(6.5, 8, 4.5, speed, servo_delay);

  delay(5);

  RightFront(8.5, 6, 3, speed, servo_delay);
  LeftMid(8.5, 6, 3, speed, servo_delay);
  RightBack(8.5, 6, 3, speed, servo_delay);

  // delay(25);

  //4
  LeftFront(8.5, 6, 4.5, speed, servo_delay);
  RightMid(8.5, 6, 4.5, speed, servo_delay);
  LeftBack(8.5, 6, 4.5, speed, servo_delay);

  RightFront(6.5, 8, 3, speed, servo_delay);
  LeftMid(6.5, 8, 3, speed, servo_delay);
  RightBack(6.5, 8, 3, speed, servo_delay);

  // delay(30);
}
void walk_fast_new() {
  //1
  RightFront(8, 8, 4, speed, servo_delay);
  LeftMid(8, 8, 4, speed, servo_delay);
  RightBack(8, 8, 4, speed, servo_delay);

  delay(10);

  LeftFront(10, 5, 3, speed, servo_delay);
  RightMid(10, 5, 3, speed, servo_delay);
  LeftBack(10, 5, 3, speed, servo_delay);

  // delay(25);

  //2
  LeftFront(8, 8, 3, speed, servo_delay);
  RightMid(8, 8, 3, speed, servo_delay);
  LeftBack(8, 8, 3, speed, servo_delay);

  RightFront(10, 5, 4, speed, servo_delay);
  LeftMid(10, 5, 4, speed, servo_delay);
  RightBack(10, 5, 4, speed, servo_delay);

  // delay(30);

  //3
  LeftFront(8, 8, 4, speed, servo_delay);
  RightMid(8, 8, 4, speed, servo_delay);
  LeftBack(8, 8, 4, speed, servo_delay);

  delay(10);

  RightFront(10, 5, 3, speed, servo_delay);
  LeftMid(10, 5, 3, speed, servo_delay);
  RightBack(10, 5, 3, speed, servo_delay);

  // delay(25);

  //4
  LeftFront(10, 5, 4, speed, servo_delay);
  RightMid(10, 5, 4, speed, servo_delay);
  LeftBack(10, 5, 4, speed, servo_delay);

  RightFront(8, 8, 3, speed, servo_delay);
  LeftMid(8, 8, 3, speed, servo_delay);
  RightBack(8, 8, 3, speed, servo_delay);

  // delay(30);
}
