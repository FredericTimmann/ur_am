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
    ROS_INFO("Current ID: %i",id);
    ROS_INFO("distance: %f",distance);

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
 ROS_INFO("Step: %d",ps);
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


   ROS_INFO("extruderlength: %f",scn.l_extrdr);

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




 bool URScript_movel(bool extr,geometry_msgs::Pose pose,double time,double tcp_speed,ros::Publisher urscript_pub,ros::Publisher goalpub,ros::Publisher pathpub);

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
   ROS_INFO("extruderspeed: %f",ex_vel);
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
ros::Subscriber tempsub =  urs_nh.subscribe("/temp/hotend", 1,  &printing_scene::temp_cb, &myscene);
ros::Publisher urscript_pub = urs_nh.advertise<std_msgs::String>("/ur_driver/URScript", 1);
ros::Publisher extruder_temp_pub = urs_nh.advertise<std_msgs::Int16>("/temp_val", 1);
ros::Publisher extruder_speed_pub = urs_nh.advertise<std_msgs::Float32>("/extruder_vel", 1);
ros::Publisher goalpub = urs_nh.advertise<geometry_msgs::Pose>("/printing_scene/goalpoint", 1);
ros::Publisher pathpub = urs_nh.advertise<nav_msgs::Path>("/printing_scene/printed_path", 5);



ROS_INFO("move linear in tool space");
std_msgs::String msg;
std_msgs::Int16 temp_msg;
std_msgs::Float32 extr_msg;
extruder_temp_pub.publish(temp_msg);
extruder_speed_pub.publish(extr_msg);
urscript_pub.publish(msg);
ROS_INFO("%s",msg.data.c_str());
ROS_INFO("wait for publisher....");
sleep(3);


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
msg.data="movej(p[" +px+","+py+","+pz+","+rx+","+ry+","+rz+"],1.5,0.25,0,0)";
ROS_INFO("%s",msg.data.c_str());
urscript_pub.publish(msg);
ROS_INFO("drive to start pose....");
sleep(5);
ROS_INFO("Beginn Printing process....");


//printing parameters
double extruder_length=0;
double extruder_speed=0;
double hotend_temp=0;


bool processOK=true;
int n=0;
//while (processOK==true){
while (processOK){
  if (!ros::ok()){processOK=false;}
  myscene.id=n;
int prstp=get_next_process_step(n);
std::cout << prstp<<'\n';
  switch (prstp) {
    case 1:
    ROS_INFO("MOVE AND EXTRUDE");
    get_next_Parameter_ext(myscene);
    //ROS_INFO("have params");
    tcp_distance=myscene.calc_distance();
    if (tcp_distance==0){
      move_time=std::abs(myscene.l_extrdr)/(myscene.v_tcp*1000);
      ROS_INFO("t extrude %f",move_time);
      ROS_INFO("length extrude %f",myscene.l_extrdr);
      ROS_INFO("speed extrude %f",myscene.v_tcp*1000);

      if (move_time==0){
          move_time=0.001;
        }
      //ros::Rate rate(1/(move_time));
      extr_msg.data=myscene.l_extrdr/move_time;
      ROS_INFO("extruder pressure_vel: %f",extr_msg.data);
      ROS_INFO("time for extrude %f",move_time);
      extruder_speed_pub.publish(extr_msg);
      //rate.sleep()
      bool time_reached=false;
      ros::Time start_time=ros::Time::now();
      ros::Time cur_time=ros::Time::now();
      double cur_move_time=0;
      while (!time_reached){
        cur_time=ros::Time::now();
        ros::Duration cur_diff=cur_time-start_time;
        cur_move_time=cur_diff.toSec();
        if (cur_move_time>=move_time*1.9){
          ROS_INFO("passed Time during extrusion %f",cur_move_time);

          time_reached=true;
        }
        if (!ros::ok()){
          time_reached=true;
        }
      }

      //sleep(move_time);
    }
    else{
      ROS_INFO("nextpoint X: %f",myscene.next_Point.position.x);
      ROS_INFO("nextpoint Y: %f",myscene.next_Point.position.y);
      ROS_INFO("nextpoint Z: %f",myscene.next_Point.position.z);
    move_time=calc_move_time(tcp_distance,myscene.v_tcp,tcp_acc);
    extruder_speed=calc_extruder_speed(myscene.l_extrdr,move_time);
    extr_msg.data=extruder_speed;
    extruder_speed_pub.publish(extr_msg);
    //publisher: extruder_speed
    if(!URScript_movel(true,myscene.next_Point,move_time,myscene.v_tcp,urscript_pub,goalpub,pathpub))
    {
      processOK=false;
      ros::shutdown;
      ROS_INFO("ERROR! ROS shutdown/URSCript");
    }}
    extr_msg.data=0;
    extruder_speed_pub.publish(extr_msg);
    break;

    case 0:
    ROS_INFO("MOVE");
    get_next_Parameter_move(myscene);
    ROS_INFO("first done..!");
    ROS_INFO("nextpoint X: %f",myscene.next_Point.position.x);
    ROS_INFO("nextpoint Y: %f",myscene.next_Point.position.y);
    ROS_INFO("nextpoint Z: %f",myscene.next_Point.position.z);
    tcp_distance=myscene.calc_distance();
    move_time=calc_move_time(tcp_distance,myscene.v_tcp,tcp_acc);
    //move_time=0.5;
    ROS_INFO("sending URSCRipt");

    if(!URScript_movel(false,myscene.next_Point,move_time,myscene.v_tcp,urscript_pub,goalpub,pathpub))
    {
      processOK=false;
      ros::shutdown;
      ROS_INFO("ERROR! ROS shutdown/URSCript");
    }
    break;
    case 104:
    ROS_INFO("SET HOTEND TEMPERATURE");
    temp_msg.data=int(get_hotend_temp(n));
    extruder_temp_pub.publish(temp_msg);

    //int set_temp= (int)hotend_temp;
    //extruder_temp_pub.publish(set_temp);
    //publisher Temperatur hotend_temp;
    break;

    case 109:
    hotend_temp=get_hotend_temp(n);
    ROS_INFO("Wait for Temperatur: %f",hotend_temp);
    hotend_temp=get_hotend_temp(n);
    temp_reached=false;
/*
    while(!temp_reached){
      ROS_INFO("Current temperatur: %f",myscene.p_current_temp);
      sleep(1);
      //live_temp=service Temperatur current_hotend_temp;
      if(myscene.p_current_temp>=hotend_temp){
        temp_reached=true;
        sleep(1);}
        if(!ros::ok()){temp_reached=true;}
      ros::spinOnce();
    }*/
    break;

    case 92:
    ROS_INFO("restore Extruderlength");
    get_next_Parameter_ext(myscene);
    break;

    case 84:
    ROS_INFO("printing succsecfull");

    extr_msg.data=0;
    extruder_speed_pub.publish(extr_msg);
    temp_msg.data=0;
    extruder_temp_pub.publish(temp_msg);
    get_next_Parameter_move(myscene);
    //next_Pose=add_offset(next_Pose,0,0,50);
    tcp_distance=myscene.calc_distance();
    move_time=calc_move_time(tcp_distance,myscene.v_tcp,tcp_acc);
    if(!URScript_movel(false,myscene.next_Point,move_time,myscene.v_tcp,urscript_pub,goalpub,pathpub))
    {
      processOK=false;
      ros::shutdown;
      ROS_INFO("ERROR! ROS shutdown/URSCript");
    }
    processOK=false;
  }
    ros::spinOnce();
    n+=1;
    /*if (n==100){
      processOK=false;
    }*/
    //last_pose=next_Pose;
  }
  temp_msg.data=0;
  extruder_temp_pub.publish(temp_msg);
  extr_msg.data=0;
  extruder_speed_pub.publish(extr_msg);
  myscene.add_offset_z_next_Point(50);
  tcp_distance=myscene.calc_distance();
  move_time=calc_move_time(tcp_distance,myscene.v_tcp,tcp_acc);
  URScript_movel(false,myscene.next_Point,move_time,myscene.v_tcp,urscript_pub,goalpub,pathpub);
  sleep(1);
//TODO temp aus und Robi wegfahren in safe position

}

  bool URScript_movel(bool extr, geometry_msgs::Pose goal_pose,double time,double tcp_speed,ros::Publisher urscript_pub,ros::Publisher goalpub,ros::Publisher pathpub)
  {
    if (tcp_speed<=0){tcp_speed=default_tool_velocity;}
    if (time<=0){time=0.1;}

    double freq=25;
    ros::Rate rate(freq);
    double x1;
    double y1;
    float x2;
    float y2;
    float z1;
    float z2;
    float diff_x;
    float diff_y;
    float diff_z;
    std::string px = tostr(goal_pose.position.x);
    std::string py = tostr(goal_pose.position.y);
    std::string pz = tostr(goal_pose.position.z);
    std::string rx = tostr(RX_rot);
    std::string ry = tostr(RY_rot);
    std::string rz = tostr(RZ_rot);
    std::string vel=tostr(tcp_speed);
    std::string acc=tostr(tcp_acc);
    std_msgs::String msg;
    double cur_move_time=0;
    ros::Time start_time=ros::Time::now();
    ros::Time cur_time=ros::Time::now();
//movep(pose, a=1.2, v=0.25, r=0)
    //ROS_INFO("rate: %f",rate);
    ROS_INFO("movel_time: %f",time);
    msg.data="movep(p[" +px+","+py+","+pz+","+rx+","+ry+","+rz+"],"+acc+","+vel+",0.00)";
    ROS_INFO("%s",msg.data.c_str());
    goalpub.publish(goal_pose);
    tf::TransformListener tf;
    tf::StampedTransform transform;
    geometry_msgs::Pose current_pose;
    geometry_msgs::PoseStamped stamp_pose;
    bool is_reached=false;
    while (is_reached==false){
      urscript_pub.publish(msg);
      try{
          tf.waitForTransform("/base", "/tool0_controller", ros::Time(0), ros::Duration(1.0));
          tf.lookupTransform("/base", "/tool0_controller", ros::Time(0), transform);
          //std::cout << "transform exist\n";
        }
      catch (tf::TransformException ex){
             ROS_ERROR("%s",ex.what());
             ros::Duration(1.0).sleep();}
      //ROS_INFO("write_poses");
      current_pose.position.x=transform.getOrigin().x();//tcp_position in mm
      current_pose.position.y=transform.getOrigin().y();//tcp_position in mm
      current_pose.position.z=transform.getOrigin().z();//tcp_position in mm
      stamp_pose.pose=current_pose;
      ppath.header.stamp = ros::Time::now();
      ppath.header.frame_id = "/base";
      //ROS_INFO("pub path");
      ///if(extr==true){ppath.poses.push_back(stamp_pose);}
      //pathpub.publish(ppath);
      //ROS_INFO("goalPoseX %f",pose.position.x);
      //ROS_INFO("curPoseX %f",current_pose.position.x);
x1=((goal_pose.position.x));
y1=((goal_pose.position.y));
x2=((current_pose.position.x));
y2=((current_pose.position.y));
z1=((current_pose.position.z));
z2=((goal_pose.position.z));
//ROS_INFO("X1: %f",x1);
//ROS_INFO("X2: %f",x2);
diff_x=std::abs(x2-x1);
diff_y=std::abs(y2-y1);
diff_z=std::abs(z2-z1);

//ROS_INFO("abs_diff_X: %f",std::abs(diff_y));
//ROS_INFO("abs_diff_Y: %f",std::abs(diff_x));
  cur_time=ros::Time::now();
  ros::Duration cur_diff=cur_time-start_time;
  cur_move_time=cur_diff.toSec();
  if(cur_move_time>time+1){
    is_reached=true;
    ROS_INFO("Time overlap");
    std::cout<<cur_move_time;
  }
      if ((diff_x<=0.0003)&& (diff_y<=0.0003)&& (diff_z<=0.0003)){
        is_reached=true;
        ros::Time end_time=ros::Time::now();
        ROS_INFO("is reached");
        ros::Duration diff=end_time-start_time;
        ROS_INFO("time to move");
        std::cout<<diff;
      }
      if (!ros::ok()){
        is_reached=true;
      }
    rate.sleep();}
    return true;
  }
