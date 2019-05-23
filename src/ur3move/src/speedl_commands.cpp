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


//std::stringstream ss;
//ss<<"movel(p[-0.35,-0.500,-0.100,0,3.141592,0.0],0.5,0.25,0,0)"<<count;
std::vector<geometry_msgs::Point> Pointset;
geometry_msgs::Point goalpoint;
//Startpoint
goalpoint.x=0.1;//*(-1)
goalpoint.y=-0.30;//*(-1)
goalpoint.z=0.015;//-0.400+z
std::string px = tostr(goalpoint.x);
std::string py = tostr(goalpoint.y);
std::string pz = tostr(goalpoint.z);
msg.data="movej(p[" +px+","+py+","+pz+",0,3.141592,0.0],1.5,0.25,0,0)";
ROS_INFO("%s",msg.data.c_str());
urscript_pub.publish(msg);
ROS_INFO("drive to start pose....");
sleep(5);
//printing a block
//block parameters
int num_layer=5;          //number of layers
float layer_height=1.0;   //height of layers in mm
float x_dim=100.0;        //x-dimension of block in mm
float y_dim=100.0;        //y-dimension of block in mm
float z_offset=1.5;       //offset in mm z dimension for extruder positions
float tool_velocity=0.06; //in m/s
float tool_acc=0.65;       //tool acceleration in m/s²

//calculate movel_duration_time
float movel_time_x=(2*tool_velocity/tool_acc)+(((x_dim/1000)-(tool_velocity*tool_velocity/tool_acc))/tool_velocity);
float movel_time_y=(2*tool_velocity/tool_acc)+(((y_dim/1000)-(tool_velocity*tool_velocity/tool_acc))/tool_velocity);
float change_layer_time=2*sqrt((4*layer_height/1000/2)/tool_acc);

std::cout << "movel_time_x: " << movel_time_x << '\n';
std::cout << "movel_time_y: " <<movel_time_y << '\n';
std::cout << "change_layer_time: " <<change_layer_time << '\n';

ros::Rate rate(1/(movel_time_x*1.5));

//converting dynamic tool parameter to strings
std::string tv = tostr(tool_velocity);
std::string ta = tostr(tool_acc);

int n=0;
while (n<=num_layer-1){
  int m=0;
  goalpoint.z=goalpoint.z+(n*layer_height/1000)+z_offset/1000;
  std::string pz = tostr(goalpoint.z);
  msg.data="movel(p[" +px+","+py+","+pz+",0,3.141592,0.0],"+ta+","+tv+",0,0)";
  ROS_INFO("%s",msg.data.c_str());
  urscript_pub.publish(msg);
  rate.sleep();

  while (m<=3){
    if (m==1){goalpoint.x=goalpoint.x-x_dim/1000;}
    if (m==0){goalpoint.y=goalpoint.y-y_dim/1000;}
    if (m==3){goalpoint.x=goalpoint.x+x_dim/1000;}
    if (m==2){goalpoint.y=goalpoint.y+y_dim/1000;}
    std::string px = tostr(goalpoint.x);
    std::string py = tostr(goalpoint.y);
    std::string pz = tostr(goalpoint.z);
    msg.data="movel(p[" +px+","+py+","+pz+",0,3.141592,0.0],"+ta+","+tv+",0,0)";
    ROS_INFO("%s",msg.data.c_str());
    urscript_pub.publish(msg);
    m+=1;
    rate.sleep();
    }

  n+=1;
  }

//ros::spinOnce();
//sleep(1.0);
}
