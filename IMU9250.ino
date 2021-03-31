#include <ros.h>
#include <ros/time.h>
#include "MPU9250.h"

#include <sensor_msgs/Imu.h> // need this for generating imu messages in ros

#include <Wire.h>

MPU9250 IMU(Wire,0x68);
double accX, accY, accZ, gyrX, gyrY, gyrz;

ros::NodeHandle nh;
sensor_msgs::Imu imu_msg;
ros::Publisher imu_data("/imu_data", &imu_msg);

uint32_t seq;
int status;


void read_IMU(){
  imu_msg.header.frame_id= "/imu";
  IMU.readSensor();
  accX= IMU.getAccelX_mss();
  accY = IMU.getAccelY_mss(); 
  accZ= IMU.getAccelZ_mss();
  imu_msg.linear_acceleration.x= accX;
  imu_msg.linear_acceleration.y = accY; 
  imu_msg.linear_acceleration.z = accZ;
 
  imu_msg.angular_velocity.x=IMU.getGyroX_rads();
  imu_msg.angular_velocity.y=IMU.getGyroY_rads();
  imu_msg.angular_velocity.z=IMU.getGyroZ_rads();

  Serial.println(imu_msg.angular_velocity.z);


  imu_data.publish(&imu_msg);
  
}
void setup() {
  nh.initNode();
  Wire.begin(); 
  Serial.begin(115200);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU init/8ialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
    
  }
  else{
    nh.advertise(imu_data);
    read_IMU();
  }
 
  
}

  // put your setup code here, to run once:


void loop() {
  // put your main code here, to run repeatedly:
  read_IMU();
  nh.spinOnce(); 
    delay(200); 

}
