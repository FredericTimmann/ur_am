#include <ros/ros.h>
#include "rosbag/bag.h"
#include "control_msgs/FollowJointTrajectoryActionGoal.h"
//#include "trajectory_msgs/JoinTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"
#include <tf/transform_listener.h>
 #include <geometry_msgs/Pose.h>
#include <std_msgs/String.h>
#include <iostream>
#include <sstream>
#include <string>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/Float64MultiArray.h>
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
//#include <Vector3.h>

//trajectory_msgs::JointTrajectoryPoint tr_goal;

void callback_1()
{
ROS_INFO("Subrcribed TOPIC");
}
template <typename T> std::string tostr(const T& t) {
   std::ostringstream os;
   os<<t;
   return os.str();
}

geometry_msgs::Pose get_point_with_id(int id)
{
    rosbag::Bag bag;
   bag.open("Pointbag_test.bag", rosbag::bagmode::Read);
   std::vector<std::string> topics;
   topics.push_back(std::string("Points"));
   //topics.push_back(std::string("Velocity"));
   //std::vector<double> newdata;
   geometry_msgs::Pose nextPose;
   std::vector<geometry_msgs::Pose> tempArray;
   rosbag::View view(bag, rosbag::TopicQuery(topics));
   foreach(rosbag::MessageInstance const m, view)
   {
     geometry_msgs::PoseArray::ConstPtr s = m.instantiate<geometry_msgs::PoseArray>();
       if (s != NULL) nextPose=s->poses[id];
   }
   bag.close();
   return nextPose;
 }
 geometry_msgs::Pose transformPose(geometry_msgs::Pose oldPose)
 {
   geometry_msgs::Pose newPose;
   double translation_x =0.3;
   double translation_y =-0.25;
   double translation_z =0.0796;
   newPose.position.x=(oldPose.position.x/1000)+translation_x;
   newPose.position.y=(oldPose.position.y/1000)+translation_y;
   newPose.position.z=(oldPose.position.z/1000)+translation_z;
   return newPose;
 }
 double calc_distance(geometry_msgs::Pose oldPose,geometry_msgs::Pose newPose)
 {
   double distance;
   double a_x =oldPose.position.x-newPose.position.x;
   double a_y =oldPose.position.y-newPose.position.y;
   double a_z =oldPose.position.z-newPose.position.z;
   distance=std::abs(std::sqrt((a_x*a_x)+(a_y*a_y)+(a_z*a_z)));
   return distance;
 }


int main(int argc, char **argv)
{
// ROS i n i t i a l i z a t i o n
ros::init(argc, argv, "ur_pub");
ros::NodeHandle urs_nh;

//ros::Subscriber sub =  nh_.subscribe("/follow_joint_trajectory/goal", 1000, callback_1);

ros::Publisher urscript_pub = urs_nh.advertise<std_msgs::String>("/ur_driver/URScript", 5);

ROS_INFO("move linear in tool space");
std_msgs::String msg;
urscript_pub.publish(msg);
ROS_INFO("%s",msg.data.c_str());
ROS_INFO("wait for publisher....");
sleep(3);


//Startpoint
geometry_msgs::Pose goalpoint;

goalpoint.position.x=0.3;//
goalpoint.position.y=0.006;//
goalpoint.position.z=0.0796;//
std::string px = tostr(goalpoint.position.x);
std::string py = tostr(goalpoint.position.y);
std::string pz = tostr(goalpoint.position.z);
msg.data="movej(p[" +px+","+py+","+pz+",2.37,-2.4394,2.4807],1.5,0.25,0,0)";
ROS_INFO("%s",msg.data.c_str());
urscript_pub.publish(msg);
ROS_INFO("drive to start pose....");
sleep(5);


//printing parameters
int num_layer=5;          //number of layers
double layer_height=1.0;   //height of layers in mm
double tcp_distance;
double movel_time_x;
double z_offset=1.5;       //offset in mm z dimension for extruder positions
double tool_velocity=0.07; //in m/s
double tool_acc=0.75;       //tool acceleration in m/s²

//converting dynamic tool parameter to strings
std::string tv = tostr(tool_velocity);
std::string ta = tostr(tool_acc);

geometry_msgs::Pose last_pose=goalpoint;


int n=8;
while (n<=100){
  geometry_msgs::Pose next_Pose=get_point_with_id(n);
  //std::cout << "next_Pose " << next_Pose<< '\n';
  next_Pose=transformPose(next_Pose);
  //std::cout << "transformed Pose " << next_Pose << '\n';
  tcp_distance=calc_distance(last_pose,next_Pose);

  std::cout << "Pose distance " << tcp_distance << '\n';
  movel_time_x=(2*tool_velocity/tool_acc)+(((tcp_distance)-(tool_velocity*tool_velocity/tool_acc))/tool_velocity);

  std::cout << "movel_time_x: " << movel_time_x << '\n';

  ros::Rate rate(1/(movel_time_x*1.8));


    std::string px = tostr(next_Pose.position.x);
    std::string py = tostr(next_Pose.position.y);
    std::string pz = tostr(next_Pose.position.z);
    msg.data="movel(p[" +px+","+py+","+pz+",2.37,-2.4394,2.4807],"+ta+","+tv+",0,0)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);

    rate.sleep();
    last_pose=next_Pose;
    n+=1;
  }
  ROS_INFO("ready");
  /*
  std::string pz = tostr(next_Pose.position.z+0.05);
  msg.data="movel(p[" +px+","+py+","+pz+",2.37,-2.4394,2.4807],"+ta+","+tv+",0,0)";
  ROS_INFO("%s",msg.data.c_str());
  urscript_pub.publish(msg);
  */

//ros::spinOnce();
//sleep(1.0);
}
