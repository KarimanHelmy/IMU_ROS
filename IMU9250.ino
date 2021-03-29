#include <ros.h>
#include <ros/time.h>
#include "MPU9250.h"

#include <sensor_msgs/Imu.h> // need this for generating imu messages in ros

#include <Wire.h>

MPU9250 imu(Wire,0x68);

ros::NodeHandle nh;
sensor_msgs::Imu imu_msg;
ros::Publisher imu_data("/imu_data", &imu_msg);

uint32_t seq;


void read_IMU(){
  imu_msg.header.frame_id= "/imu";
  imu.readSensor();
  imu_msg.linear_acceleration.x= imu.getAccelX_mss();
  imu_msg.linear_acceleration.y = imu.getAccelY_mss(); 
  imu_msg.linear_acceleration.z = imu.getAccelZ_mss();
  Serial.print(imu_msg.linear_acceleration.x);

  imu_data.publish(&imu_msg);
  
}
void setup() {
  nh.initNode();
  Wire.begin(); 
  Serial.begin(115200);

      nh.advertise(imu_data);

    read_IMU();
  
}

  // put your setup code here, to run once:


void loop() {
  // put your main code here, to run repeatedly:
  read_IMU();
  nh.spinOnce(); 
    delay(200); 

}
