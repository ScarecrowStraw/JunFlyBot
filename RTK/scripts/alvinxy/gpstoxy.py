#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from data_collection.msg import rtk
from geometry_msgs.msg import Point
import alvinxy
reload(alvinxy)

# Specify an origin
origin = [21.0454563, 105.7859686]

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + 'I heard %s %s %s', str(data.latitude), str(data.longitude), str(data.altitude))
    xx,yy = alvinxy.ll2xy(data.latitude,data.longitude,origin[0],origin[1])
    pub = rospy.Publisher('gps_to_point/', Point, queue_size=10)
    msg = Point()
    msg.x = xx
    msg.y = yy
    msg.z = data.altitude
    pub.publish(msg)


def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('converter', anonymous=True)

    rospy.Subscriber('ublox_rtk', rtk, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()