#!/usr/bin/env python
import rospy
import sensor_msgs.msg

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)

def listener():
    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("imu_pub", sensor_msg, callback)
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
