#include <ros/ros.h>
#include "rosbag/bag.h"
#include "control_msgs/FollowJointTrajectoryActionGoal.h"
//#include "trajectory_msgs/JoinTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"
#include <tf/transform_listener.h>
 #include <geometry_msgs/Pose.h>
#include <std_msgs/String.h>
//#include <Vector3.h>

//trajectory_msgs::JointTrajectoryPoint tr_goal;

void callback_1()
{
ROS_INFO("Subrcribed TOPIC");
}

int main(int argc, char **argv)
{
// ROS i n i t i a l i z a t i o n
ros::init(argc, argv, "ur_pub");
ros::NodeHandle urs_nh;

ros::Rate rate(10.0);
//ros::Subscriber sub =  nh_.subscribe("/follow_joint_trajectory/goal", 1000, callback_1);

ros::Publisher urscript_pub = urs_nh.advertise<std_msgs::String>("/ur_driver/URScript", 5);

ROS_INFO("move linear in tool space");
std_msgs::String msg;
//std::stringstream ss;
//ss<<"movel(p[-0.35,-0.500,-0.100,0,3.141592,0.0],0.5,0.25,0,0)"<<count;
msg.data="movel(p[-0.35,-0.500,-0.100,0,3.141592,0.0],1.5,0.25,0,0)";
//ROS_INFO("%s",msg.data.c_str());
//urscript_pub.publish(msg);
int n=0;
while (n<=19){
  if (n==11) {
    msg.data="speedl([0.25,0,0,0,0,0],0.35,1)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);}
  if (n==12) {
    msg.data="speedl([0.25,0,0,0,0,0],0.7,1)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);}
  if ((n>=13) && (n<19)) {
    msg.data="speedl([0.25,0,0,0,0,0],1.2,1)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);}
  if (n==27) {
    msg.data="stopl(1.5)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);}
  if (n==19) {
    msg.data="movep(p[0.0,-0.500,-0.100,0,3.141592,0.0],1.2,0.25,0)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);}
  rate.sleep();
  n+=1;
    //ros::spinOnce();
  }

//ros::spinOnce();
//sleep(1.0);
}
