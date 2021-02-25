#include <ros.h>




#include "MPU9250.h"
#include <std_msgs/String.h>
#include <Wire.h>

MPU9250 IMU(Wire,0x68);
int status;
float AccX,AccY,AccZ,Tmp,GyX,GyY,GyZ,MagX,MagY,MagZ;
std_msgs::String imu_msg;
ros::Publisher imu("imu", &imu_msg);
ros::NodeHandle nh;

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

  String AccX = String(AccX);
  String AccX = String(AccY);
  String AccX= String(AccZ);
  String GyX = String(GyX);
  String GyY = String(GyY);
  String GyZ = String(GyZ);
  String MagX = String(MagX);
  String MagY = String(MagY);
  String MagZ = String(MagZ);
  
  String data = "A" + AccX + "B"+ AccY + "C" + AccZ + "D" + GyX + "E" + GyY + "F" + GyZ + "G" + MagX + "H" + MagY + "I" + MagZ + "J" ;
  Serial.println(data);
  int length = data.indexOf("J") +2;
  char data_final[length+1];
  data.toCharArray(data_final, length+1);
  
}
void setup() {
  nh.initNode();
  nh.advertise(imu);
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

}

void loop() {
  // put your main code here, to run repeatedly:
  
  read_IMU();
  if (millis() > publisher_timer) {
    // step 1: request reading from sensor
    imu_msg.data = data_final;
    imu.publish(&imu_msg);
    publisher_timer = millis() + 100; //publish ten times a second
    nh.spinOnce();
  

}
