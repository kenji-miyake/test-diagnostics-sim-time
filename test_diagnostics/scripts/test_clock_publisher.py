#!/usr/bin/python3

import time

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy
from rclpy.time import Time
from rosgraph_msgs.msg import Clock

clock_qos = QoSProfile(depth=1, reliability=ReliabilityPolicy.BEST_EFFORT)
sec2nanosec = 10 ** 9

if __name__ == "__main__":
    rclpy.init()
    node = Node("test_clock_publisher_py")
    pub = node.create_publisher(Clock, "/clock", clock_qos)

    sec = 0
    while rclpy.ok():
        msg = Clock()
        msg.clock = Time(nanoseconds=sec * sec2nanosec).to_msg()
        pub.publish(msg)
        time.sleep(0.1)
        sec += 0.1
