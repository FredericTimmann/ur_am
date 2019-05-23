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
double RX_rot=2.37;
double RX_rot=-2.4394;
double RX_rot=2.4807;
double tcp_acc=0.75;

//trajectory_msgs::JointTrajectoryPoint tr_goal;
void move();
void prepare_to_print();

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
   double translation_x =0.3;
   double translation_y =-0.25;
   double translation_z =0.0796;
   nextPose.position.x=(nextPose.position.x/1000)+translation_x;
   nextPose.position.y=(nextPose.position.y/1000)+translation_y;
   nextPose.position.z=(nextPose.position.z/1000)+translation_z;
   return nextPose;
 }

 bool URScript_movel(geometry_msgs::Pose pose,double time,double tcp_speed)
 {
   ros::Rate rate(1/(time*1.8))
   std::string px = tostr(pose.position.x);
   std::string py = tostr(pose.position.y);
   std::string pz = tostr(pose.position.z);
   std::string rx = tostr(RX_rot);
   std::string ry = tostr(RY_rot);
   std::string rz = tostr(RZ_rot);
   std::string vel=tostr(speed);
   std::string acc=tostr(tcp_acc);

   msg.data="movel(p[" +px+","+py+","+pz+","+rx+","+ry+","+rz+"],"+acc+","+vel+",0,0)";
   ROS_INFO("%s",msg.data.c_str());
   urscript_pub.publish(msg);

   rate.sleep();
   return true;
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

 double calc_move_time(d,v,a){
   double time;
   time=(2*v/a)+(((d)-(v*v/a))/v);
 return time;
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

goalpoint.position.x=0.1;//*(-1)
goalpoint.position.y=-0.30;//*(-1)
goalpoint.position.z=0.015;//-0.400+z
std::string px = tostr(goalpoint.position.x);
std::string py = tostr(goalpoint.position.y);
std::string pz = tostr(goalpoint.position.z);
msg.data="movej(p[" +px+","+py+","+pz+","+rx+","+ry+","+rz+"],1.5,0.25,0,0)";
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
double tool_velocity=0.06; //in m/s
double tool_acc=0.65;       //tool acceleration in m/s²

//converting dynamic tool parameter to strings
std::string tv = tostr(tool_velocity);
std::string ta = tostr(tool_acc);

geometry_msgs::Pose last_pose=goalpoint;

bool processOK=true;
int n=0;
while (processOK==true){
  switch (get_next_process_step(n)) {
    case 1:
    next_Pose=get_point_with_id(n);
    tcp_speed=get_tool_speed(n);
    extruder_length=get_extruder_length(n);
    tcp_distance=calc_distance(last_pose,next_Pose);
    move_time=calc_move_time(tcp_distance,tcp_speed,tcp_acc);
    extruder_speed=calc_extruder_speed(extruder_length,tcp_distance,move_time);
    //publisher: extruder_speed
    if(!URScript_movel(next_Pose){
      processOK=false;
      ros::shutdown;
      ROS_INFO("ERROR! ROS shutdown/URSCript");
    }
    //publisher: extruder_speed=0;
    break;

    case 0:
    next_Pose=get_point_with_id(n);
    tcp_speed=get_tool_speed(n);
    tcp_distance=calc_distance(last_pose,next_Pose);
    move_time=calc_move_time(tcp_distance,tcp_speed,tcp_acc);
    if(!URScript_movel(next_Pose,move_time){
      processOK=false;
      ros::shutdown;
      ROS_INFO("ERROR! ROS shutdown/URSCript");
    }

    case 104:
    hotend_temp=get_hotend_temp(n);
    //publisher Temperatur hotend_temp;
    break;

    case 109:
    hotend_temp=get_hotend_temp(n);
    bool temp_reached=false;
    while(!temp_reached){
      //live_temp=service Temperatur current_hotend_temp;
      if(live_temp>=hotend_temp){
        temp_reached=true;
        sleep(1);}
      }
    break;

    case 84:
    //publisher: extruder_speed=0;
    next_Pose=get_point_with_id(n-4);
    next_Pose=add_offset(next_Pose,0,0,50);
    tcp_speed=get_tool_speed(n-4);
    tcp_distance=calc_distance(last_pose,next_Pose);
    move_time=calc_move_time(tcp_distance,tcp_speed,tcp_acc);
    if(!URScript_movel(next_Pose,move_time,tcp_speed){
      processOK=false;
      ros::shutdown;
      ROS_INFO("ERROR! ROS shutdown/URSCript");
    }
    processOK=false;
  }
    n+=1;
    last_pose=next_Pose;
  }

  }

  geometry_msgs::Pose next_Pose=get_point_with_id(n);
  //std::cout << "next_Pose " << next_Pose<< '\n';
  next_Pose=transformPose(next_Pose);
  //std::cout << "transformed Pose " << next_Pose << '\n';
  tcp_distance=calc_distance(last_pose,next_Pose);




  std::cout << "Pose distance " << tcp_distance << '\n';
  movel_time_x=(2*tool_velocity/tool_acc)+(((tcp_distance)-(tool_velocity*tool_velocity/tool_acc))/tool_velocity);

  std::cout << "movel_time_x: " << movel_time_x << '\n';


    last_pose=next_Pose;

  }
