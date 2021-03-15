#include <ros.h>
#include <ros/time.h>
#include "MPU9250.h"

#include <geometry_msgs/Vector3.h> 
#include <tf/transform_broadcaster.h> 

#include <Wire.h>

MPU9250 IMU(Wire,0x68);
int status;
float AccX,AccY,AccZ,Tmp,GyX,GyY,GyZ,MagX,MagY,MagZ;
geometry_msgs::TransformStamped t; 
tf::TransformBroadcaster broadcaster;
ros::NodeHandle nh;
geometry_msgs::Vector3 orient;
ros::Publisher imu_pub("imu_data", &orient); 
char frameid[] = "/base_link"; 
char child[] = "/imu_frame";

uint32_t seq;


void read_IMU(){
  IMU.readSensor();
  AccX = IMU.getAccelX_mss();
  AccY = IMU.getAccelY_mss(); 
  AccZ = IMU.getAccelZ_mss();

  
  MagX = IMU.getMagX_uT();
  MagY = IMU.getMagY_uT();
  MagZ = IMU.getMagZ_uT();

  
  GyX = IMU.getGyroX_rads();
  GyY = IMU.getGyroY_rads();
  GyZ = IMU.getGyroZ_rads();
   imu_pub.publish(&orient);

  
}
void setup() {
  Wire.begin(); 
        nh.initNode(); 
        broadcaster.init(nh); 
        nh.advertise(imu_pub); 
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
