
#include "MPU9250.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;
int16_t  AccX,AccY,AccZ,Tmp,GyX,GyY,GyZ,MagX,MagY,MagZ;

#include <ros.h>
#include <ros/time.h>
#include <tiny_msgs/tinyVector.h>
#include <tiny_msgs/tinyIMU.h>
ros::NodeHandle  nh;

tiny_msgs::tinyIMU imu_msg;
ros::Publisher imu_pub("tinyImu", &imu_msg);

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

  
}
void setup()
{
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
  #endif
  nh.initNode();
  nh.advertise(imu_pub);
  seq = 0;
}

void loop()
{
  seq++;
  read_IMU();

  imu_msg.header.stamp = nh.now();
  imu_msg.header.frame_id = 0;
  imu_msg.header.seq = seq;

  imu_msg.accel.x = ax;
  imu_msg.accel.y = ay;
  imu_msg.accel.z = az;
  imu_msg.gyro.x = gx;
  imu_msg.gyro.y = gy;
  imu_msg.gyro.z = gz;

  imu_pub.publish( &imu_msg );
  nh.spinOnce();
}
