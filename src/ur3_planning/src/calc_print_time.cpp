#include <ros/ros.h>
#include "rosbag/bag.h"
#include "control_msgs/FollowJointTrajectoryActionGoal.h"
//#include "trajectory_msgs/JoinTrajectoryPoint.h"
#include <actionlib/client/simple_action_client.h>
//#include <pr2_controllers_msgs/JointTrajectoryAction.h>
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
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/Int16.h>
#include "nav_msgs/Path.h"
//#include <nav_msgs/Path.msg>
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <math.h>
#include <boost/assign/list_of.hpp>


#define foreach BOOST_FOREACH
//#include <Vector3.h>
double start_x=0.35;
double start_y=0.0;
double start_z=0.02;
double translation_x =start_x+0.06;
double translation_y =start_y-0.25;
double translation_z =0.00019;
double transform_rot_x=0;
double transform_rot_y=-0.005;
double transform_rot_z=0;
double RX_rot=0;
double RY_rot=0;
double RZ_rot=0;
double tcp_acc=0.75;
double tcp_distance=0;;
double move_time=0;
double z_offset=1.5;       //offset in mm z dimension for extruder positions
double default_tool_velocity=0.07; //in m/s
bool temp_reached;
double current_temp;
double total_print_time=0;

//ROS Param
nav_msgs::Path ppath;



class printing_scene {
private:
  //TrajClient* traj_client_;

public:
  double p_current_temp;
  //const std_msgs::Float32::ConstPtr myMessagePtr;
  int id;
  double l_extrdr;
  double next_extrdr_pos;
  double last_extrdr_pos;
  double v_tcp;
  geometry_msgs::Pose next_Point;
  geometry_msgs::Pose last_Point;

  //void tempCallback(const std_msgs::Float32::ConstPtr& msg );

  void temp_cb(const std_msgs::Float32::ConstPtr& t_val);


  double calc_distance()
  {
    double distance;
    double a_x =last_Point.position.x-next_Point.position.x;
    double a_y =last_Point.position.y-next_Point.position.y;
    double a_z =last_Point.position.z-next_Point.position.z;
    distance=std::abs(std::sqrt((a_x*a_x)+(a_y*a_y)+(a_z*a_z)));


    return distance;
  }

  void set_next_Point(geometry_msgs::Pose p){
    last_Point=next_Point;
    next_Point=p;
  }
  void add_offset_z_next_Point(double z){
    if (z<=100){
      next_Point.position.z=next_Point.position.z+(z/1000);
    }
    //next_Point.position.x=(next_Point.position.x/1000)+(x/1000);
    //next_Point.position.y=(next_Point.position.y/1000)+(y/1000);
  }

};
void printing_scene::temp_cb(const std_msgs::Float32::ConstPtr& t_val)
{
  double t=t_val->data;
//this->p_current_temp=t_val->data;
p_current_temp=t;
//p_current_temp=155;
//ROS_INFO("cure temp: %f",p_current_temp);
}
void temp_CB(const std_msgs::Float32::ConstPtr& t_val)
{
  double t=t_val->data;
//this->p_current_temp=t_val->data;
current_temp=t;
//p_current_temp=155;
//ROS_INFO("cure temp: %f",p_current_temp);
}
//static void wrapper_tempCallback(void* pt2Object, const std_msgs::Float32::ConstPtr& msg);

/*void printing_scene::tempCallback(const std_msgs::Float32::ConstPtr& msg )
{

    this->p_current_temp = msg->data;
    //this->myMessagePtr = msg;


}
static void wrapper_imageCallback(void* pt2Object, const std_msgs::Float32::ConstPtr& msg)
   {
       printing_scene* mySelf = (printing_scene*) pt2Object; // explicitly cast to a pointer to class myImages
       mySelf->tempCallback(msg );          // call member
   }*/

template <typename T> std::string tostr(const T& t) {
   std::ostringstream os;
   os<<t;
   return os.str();
}
int get_next_process_step(int id){
  int ps=-1;
  rosbag::Bag bag;
 bag.open("Pointbag_test.bag", rosbag::bagmode::Read);
 std::vector<std::string> topics;
 topics.push_back(std::string("Process_step"));
 rosbag::View view(bag, rosbag::TopicQuery(topics));
 foreach(rosbag::MessageInstance const m, view)
 {
   std_msgs::Int16MultiArray::ConstPtr s = m.instantiate<std_msgs::Int16MultiArray >();
     if (s != NULL) ps=s->data[id];
 }
 //ROS_INFO("Step: %d",ps);
 bag.close();
 return ps;
}
std::vector<double> homogenous_transform(double pos [3],double rx,double ry,double rz,double trans_x,double trans_y,double trans_z){
  double hom_mat [4][4] ;
  std::vector<double> npos(4);
  //double npos [3];
  hom_mat [0][0]=cos(ry);
  hom_mat [0][1]=0;
  hom_mat [0][2]=sin(ry);
  hom_mat [0][3]=trans_x;
  hom_mat [1][0]=0;
  hom_mat [1][1]=1;
  hom_mat [1][2]=0;
  hom_mat [1][3]=trans_y;
  hom_mat [2][0]=-sin(ry);
  hom_mat [2][1]=0;
  hom_mat [2][2]=cos(ry);
  hom_mat [2][3]=trans_z;
  hom_mat [3][0]=0;
  hom_mat [3][1]=0;
  hom_mat [3][2]=0;
  hom_mat [3][3]=1;

  for(int i=0;i<4;i++)
   {
     for(int j=0;j<4;j++)
     {
       npos[i]=npos[i]+(pos[j]*hom_mat[i][j]);
     }
   }
 //std::cout<<npos<<"\n";
 return npos;
}

void get_next_Parameter_ext(printing_scene& scn){
  scn.last_extrdr_pos=scn.next_extrdr_pos;
  scn.last_Point=scn.next_Point;
    rosbag::Bag bag;
   bag.open("Pointbag_test.bag", rosbag::bagmode::Read);
   std::vector<std::string> topics;
   topics.push_back(std::string("Points"));
   topics.push_back(std::string("Velocity"));
   topics.push_back(std::string("Extruderlength"));
   rosbag::View view(bag, rosbag::TopicQuery(topics));
   foreach(rosbag::MessageInstance const m, view)
   {
     geometry_msgs::PoseArray::ConstPtr s = m.instantiate<geometry_msgs::PoseArray>();
       if (s != NULL) scn.next_Point=s->poses[scn.id];
    std_msgs::Float64MultiArray::ConstPtr i = m.instantiate<std_msgs::Float64MultiArray>();
        if (i != NULL) scn.v_tcp=i->data[scn.id];
    std_msgs::Float32MultiArray::ConstPtr e = m.instantiate<std_msgs::Float32MultiArray>();
          if (e!= NULL) scn.next_extrdr_pos=e->data[scn.id];
   }
   bag.close();
   //set extruder velocity;

     scn.l_extrdr=scn.next_extrdr_pos-scn.last_extrdr_pos;


   //ROS_INFO("extruderlength: %f",scn.l_extrdr);

   //transform POSITION to Roboterframe;
   scn.v_tcp=scn.v_tcp/60/1000;
   double homogen_pos  [3];
   std::vector<double> t_homogen_pos (3);

   homogen_pos[0]=(scn.next_Point.position.x/1000);
   homogen_pos[1]=(scn.next_Point.position.y/1000);
   homogen_pos[2]=(scn.next_Point.position.z/1000);
   homogen_pos[3]=1;
   t_homogen_pos=homogenous_transform(homogen_pos,transform_rot_x,transform_rot_y,transform_rot_z,translation_x,translation_y,translation_z);
   scn.next_Point.position.x=t_homogen_pos[0];
   scn.next_Point.position.y=t_homogen_pos[1];
   scn.next_Point.position.z=t_homogen_pos[2];



   return;
 }



 void get_next_Parameter_move(printing_scene& scn){
    scn.last_Point=scn.next_Point;
    rosbag::Bag bag;
    bag.open("Pointbag_test.bag", rosbag::bagmode::Read);
    std::vector<std::string> topics;
    topics.push_back(std::string("Points"));
    topics.push_back(std::string("Velocity"));
    rosbag::View view(bag, rosbag::TopicQuery(topics));
    foreach(rosbag::MessageInstance const m, view)
    {
      geometry_msgs::PoseArray::ConstPtr s = m.instantiate<geometry_msgs::PoseArray>();
        if (s != NULL) scn.next_Point=s->poses[scn.id];
     std_msgs::Float64MultiArray::ConstPtr i = m.instantiate<std_msgs::Float64MultiArray>();
         if (i != NULL) scn.v_tcp=i->data[scn.id];
    }
    bag.close();
    //transform POSITION to Roboterframe;
    scn.v_tcp=scn.v_tcp/60/1000;
    double homogen_pos  [3];
    std::vector<double> t_homogen_pos (3);

    homogen_pos[0]=(scn.next_Point.position.x/1000);
    homogen_pos[1]=(scn.next_Point.position.y/1000);
    homogen_pos[2]=(scn.next_Point.position.z/1000);
    homogen_pos[3]=1;
    t_homogen_pos=homogenous_transform(homogen_pos,transform_rot_x,transform_rot_y,transform_rot_z,translation_x,translation_y,translation_z);
    scn.next_Point.position.x=t_homogen_pos[0];
    scn.next_Point.position.y=t_homogen_pos[1];
    scn.next_Point.position.z=t_homogen_pos[2];
    return;
  }


 double calc_move_time(double d,double v,double a){
   double time;
   double v_max=sqrt(d/a);
   if (v_max<=v){time=2*sqrt(d/a);}
   else {time=(2*v/a)+(((d)-(v*v/a))/v); }
 //time=0.4;
 return time;
 }

 double calc_extruder_speed(double l,double t){
   double ex_vel;
   if (t<=0){ex_vel=0;}
   else{ex_vel=l/t*1.3;}
   //ROS_INFO("extruderspeed: %f",ex_vel);
   return ex_vel;
 }

 double get_hotend_temp(int id){
   double temp=0;
   rosbag::Bag bag;
  bag.open("Pointbag_test.bag", rosbag::bagmode::Read);
  std::vector<std::string> topics;
  topics.push_back(std::string("HotendTemp"));
  rosbag::View view(bag, rosbag::TopicQuery(topics));
  foreach(rosbag::MessageInstance const m, view)
  {
    std_msgs::Float64MultiArray::ConstPtr s = m.instantiate<std_msgs::Float64MultiArray>();
      if (s != NULL) temp=s->data[id];
  }
  bag.close();
   return temp;
 }



int main(int argc, char **argv)
{
  printing_scene myscene;
  //float current_temp=0;
  //callback boundtempCallback = boost::bind(&printing_scene::tempCallback, &myscene/*&images*/, _1);

// ROS i n i t i a l i z a t i o n
ros::init(argc, argv, "ur_pub");
ros::NodeHandle urs_nh;
//ros::Subscriber subLeft = urs_nh.subscribe<std_msgs::Float32> ("/temp/hotend", 10,boost::bind(&printing_scene::temp_CB, _1, &myscene) );

std_msgs::String msg;
std_msgs::Int16 temp_msg;
std_msgs::Float32 extr_msg;


//Startpoint
myscene.next_Point.position.x=start_x;//
myscene.next_Point.position.y=start_y;//
myscene.next_Point.position.z=start_z;//
std::string px = tostr(myscene.next_Point.position.x);
std::string py = tostr(myscene.next_Point.position.y);
std::string pz = tostr(myscene.next_Point.position.z);
std::string rx = tostr(RX_rot);
std::string ry = tostr(RY_rot);
std::string rz = tostr(RZ_rot);

//printing parameters
double extruder_length=0;
double extruder_speed=0;
double num_movements=0;

bool processOK=true;
int n=0;
//while (processOK==true){
while (processOK){
  if (!ros::ok()){processOK=false;}
  myscene.id=n;
int prstp=get_next_process_step(n);
//std::cout << prstp<<'\n';
  if (prstp==1) {
    num_movements=num_movements+1;
    //ROS_INFO("MOVE AND EXTRUDE");
    get_next_Parameter_ext(myscene);
    //ROS_INFO("have params");
    tcp_distance=myscene.calc_distance();
    if (tcp_distance==0){
      move_time=std::abs(myscene.l_extrdr)/(myscene.v_tcp*1000);
      }
    else{
    move_time=calc_move_time(tcp_distance,myscene.v_tcp,tcp_acc);
    //publisher: extruder_speed
    }
  }
  else if (prstp==0){
    num_movements=num_movements+1;

    //ROS_INFO("MOVE");
    get_next_Parameter_move(myscene);
    tcp_distance=myscene.calc_distance();
    move_time=calc_move_time(tcp_distance,myscene.v_tcp,tcp_acc);

  }
  else if (prstp==84){
    processOK=false;
    }
  else {
    move_time=0;
    }

    n+=1;
    if ( std::isinf(move_time)){
      move_time=0;
    }
    if (move_time>200){
      processOK=false;
    }
    total_print_time=total_print_time+move_time;
    //ssssssstd::cout << "move_time:  " <<move_time<< '\n';

  }
  std::cout << "total_print_time:  " <<total_print_time<< '\n';
  std::cout << "num_movements:  " <<num_movements<< '\n';

}

//TODO temp aus und Robi wegfahren in safe position
