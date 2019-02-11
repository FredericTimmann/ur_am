# ! / bin / bash

roslaunch ur_modern_driver ur3_ros_control.launch robot_ip:=127.0.0.1
sleep 5
roslaunch ur3_moveit_config ur3_moveit_planning_execution.launch config:=true limited:=true
sleep 2
roslaunch ur3_moveit_config moveit_rviz.launch config:=true limited:=true
