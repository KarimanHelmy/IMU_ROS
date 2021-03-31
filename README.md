# IMU_ROS
Create package in catkin workspace src, then put the code in src file.
roscore
rosrun package_name imusubsc.py /dev/tty#yourcom port
 
For rosserial 
just run roscore
then rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=115200 # note change USB0 with whatever port u r using
then rostopic echo imu_data 
enjoy :)

The test was done with arduino mega 
