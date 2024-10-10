void distance_detection(){
  left_dis=sonar[2].ping_cm();
  right_dis=sonar[3].ping_cm();
  front_dis=sonar[0].ping_cm();
  back_dis=sonar[1].ping_cm();
  // gripper_dis=sonar[4].ping_cm();
}
