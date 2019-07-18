#include <ros/ros.h>
#include "rosbag/bag.h"
#include "control_msgs/FollowJointTrajectoryActionGoal.h"
//#include "trajectory_msgs/JoinTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"
#include <tf/transform_listener.h>
 #include <geometry_msgs/Pose.h>
 #include <sensor_msgs/JointState.h>
 #include <std_msgs/Float64.h>
//#include <Vector3.h>

//trajectory_msgs::JointTrajectoryPoint tr_goal;
control_msgs::FollowJointTrajectoryActionGoal   tr_goal;
ros::Publisher goal_pub;
ros::Publisher effort_pub;

void callback_1(const control_msgs::FollowJointTrajectoryActionGoal& msg)
{
//tr_goal=msg.goal.trajectory.points[1];
tr_goal=msg;
goal_pub.publish(tr_goal);
ROS_INFO("Subrcribed TOPIC");
}
void callback_2(const sensor_msgs::JointState& msg)
{
  std_msgs::Float64 r_e;
//tr_goal=msg.goal.trajectory.points[1];
for (int i = 0; i < 6; i++) {
  r_e.data+=msg.effort[i];
}
effort_pub.publish(r_e);
//std::cout << "robot effort: " << r_e << '\n';
//ROS_INFO("Subrcribed TOPIC");
}


int main(int argc, char **argv)
{
// ROS i n i t i a l i z a t i o n
ros::init(argc, argv, "edits_pub");
ros::NodeHandle nh_;


ros::Subscriber sub =  nh_.subscribe("/follow_joint_trajectory/goal", 1000, callback_1);
goal_pub = nh_.advertise<control_msgs::FollowJointTrajectoryActionGoal>("/trajectory/goal", 1000);
ros::Subscriber effort_sub =  nh_.subscribe("/joint_states", 1000, callback_2);
effort_pub = nh_.advertise<std_msgs::Float64>("/effort_robot", 1000);
ros::Publisher eef_pub = nh_.advertise<geometry_msgs::Pose >("/tool_positionXXX", 1000);
//ros::Publisher goal_pub = nh_.advertise<trajectory_msgs::JointTrajectoryPoint>("/trajectory/goal", 1000);

//ROS_INFO("pos: %f", tr_goal.positions[1]);
tf::TransformListener listener;
tf::StampedTransform transform;
geometry_msgs::Pose transPUB;
transPUB.position.x=transform.getOrigin().x()*1000;//tcp_position in mm
transPUB.position.y=transform.getOrigin().y()*1000;//tcp_position in mm
transPUB.position.z=transform.getOrigin().z()*1000;//tcp_position in mm
eef_pub.publish(transPUB);
  ros::spin();

  ROS_INFO("start");
std::cout << "G92: exl:"<< '\n';
ros::Rate rate(10.0);
  while (ros::ok()){
    try{
      listener.lookupTransform("/Base", "/tool0_controller",
                               ros::Time(0), transform);
    }


    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    ROS_INFO("pub");
    transPUB.position.x=transform.getOrigin().x()*1000;//tcp_position in mm
    transPUB.position.y=transform.getOrigin().y()*1000;//tcp_position in mm
    transPUB.position.z=transform.getOrigin().z()*1000;//tcp_position in mm
    eef_pub.publish(transPUB);



    rate.sleep();

}

return 0;
}
