#include <ros/ros.h>
#include <optimation_msgs/TrajectoryExecutionAction.h>  // Note: "Action" is appended
#include <actionlib/server/simple_action_server.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <iostream>
#include <vector>
#include <tf/transform_listener.h>
#include <sensor_msgs/JointState.h>
// MoveIt!
//#include <moveit/robot_model_loader/robot_model_loader.h>
//#include <moveit/robot_model/robot_model.h>
//#include <moveit/robot_state/robot_state.h>
template <typename T> std::string tostr(const T& t) {
   std::ostringstream os;
   os<<t;
   return os.str();
 }

class Trajectory_Execution_Action
{
protected:
  ros::Publisher urscript_pub;
  ros::Publisher des_vel_pub;
  ros::Subscriber effort_sub;
  ros::Subscriber tool_vel_sub;

  ros::Publisher des_pos_pub;
  ros::Publisher des_vel2_pub;
  ros::Publisher engergy_pub;

  ros::Publisher real_pos_pub;
  ros::NodeHandle nh_;
  std::string action_name_;
  // create messages that are used to published feedback/result
  optimation_msgs::TrajectoryExecutionResult result_;
  optimation_msgs::TrajectoryExecutionFeedback feedback_;

public:
  actionlib::SimpleActionServer<optimation_msgs::TrajectoryExecutionAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.

  std::vector<double> effort;
  std::vector<double> l_effort;
  double tool_speed_y;
  double effort_sum;

  Trajectory_Execution_Action(std::string name) :
    as_(nh_, name, boost::bind(&Trajectory_Execution_Action::executeCB, this, _1), false),
    action_name_(name)
  {
    effort_sub = nh_.subscribe<sensor_msgs::JointState> ("/joint_states", 5, &Trajectory_Execution_Action::effort_subCB, this);
    tool_vel_sub =  nh_.subscribe<geometry_msgs::TwistStamped>("/tool_velocity", 5,&Trajectory_Execution_Action::tool_vel_subCB,this);

    as_.start();
  }

  ~Trajectory_Execution_Action(void)
  {
  }

void effort_subCB(const sensor_msgs::JointStateConstPtr &states ){
  l_effort=effort;
  effort=states->effort;
}
void tool_vel_subCB(const geometry_msgs::TwistStampedConstPtr &msg ){
  tool_speed_y=msg->twist.linear.y;
}
  void executeCB(const optimation_msgs::TrajectoryExecutionGoalConstPtr &goal)
  {
    ros::Rate r(1);
    bool success = true;
    if (as_.isPreemptRequested() || !ros::ok())
      {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success = false;
        }
    urscript_pub = nh_.advertise<std_msgs::String>("/ur_driver/URScript", 1000);
    des_vel_pub = nh_.advertise<std_msgs::Float32>("/designed_toolvelocity/y", 100);
    engergy_pub= nh_.advertise<std_msgs::Float32>("/sum_energy", 100);
    //des_vel2_pub = nh_.advertise<std_msgs::Float32>("/designed_toolvelocity/y", 1);

    des_pos_pub = nh_.advertise<std_msgs::Empty>("/matlab_srv/show_pos", 100);
    real_pos_pub = nh_.advertise<std_msgs::Float32>("/tool_position/y", 100);
    // helper variables

    r.sleep();

    //feedback_.sequence.push_back(0);
    //as_.setPreempted();
    success=set_start_pose(goal->StartPose);
    if (success) {ROS_INFO("startposition reached");}
    ros::Rate(1).sleep();
    success=drive_to_goal_pose(goal);
    if(success)
    {
      result_.energy=effort_sum;
      //result_.sequence = feedback_.sequence;
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);
    }
    else {
      as_.setAborted(result_);
    }
  }
  std::vector<double> calc_correction_vel(double goal, double speed ,double pos,double freq) {
    std::vector<double> correct (5);
    correct[1]=2*((goal-(1000*pos))-(speed*(1/freq)))/((1/freq)*(1/freq));
    correct[0]=(correct[1]*(1/freq))+speed;
    return correct;
  }

  std::string movej_URSstring(geometry_msgs::Pose pose){
    std::string px = tostr(pose.position.x);
    std::string py = tostr(pose.position.y);
    std::string pz = tostr(pose.position.z);
    std::string rx = tostr(pose.orientation.x);
    std::string ry = tostr(pose.orientation.y);
    std::string rz = tostr(pose.orientation.z);
    std::string msg;
    msg="movej(p[" +px+ "," +py+ ","+pz+","+rx+","+ry+","+rz+"],";
    return msg;}

  std::string movel_URSstring(geometry_msgs::Pose pose){
    std::string px = tostr(pose.position.x);
    std::string py = tostr(pose.position.y);
    std::string pz = tostr(pose.position.z);
    std::string rx = tostr(pose.orientation.x);
    std::string ry = tostr(pose.orientation.y);
    std::string rz = tostr(pose.orientation.z);
    std::string msg;
    msg="movel(p[" +px+ "," +py+ ","+pz+","+rx+","+ry+","+rz+"],";
    return msg;
  }
  std::string movep_URSstring(geometry_msgs::Pose pose){
    std::string px = tostr(pose.position.x);
    std::string py = tostr(pose.position.y);
    std::string pz = tostr(pose.position.z);
    std::string rx = tostr(pose.orientation.x);
    std::string ry = tostr(pose.orientation.y);
    std::string rz = tostr(pose.orientation.z);
    std::string msg;
    msg="movep(p[" +px+ "," +py+ ","+pz+","+rx+","+ry+","+rz+"],";
    return msg;
  }

  bool drive_to_goal_pose(const optimation_msgs::TrajectoryExecutionGoalConstPtr &goal){
    ROS_INFO("drive to goal pose");
    std_msgs::String movej_msg;
    std_msgs::Float32 des_vel_msg;
    std_msgs::Float32 real_pos_msg;
    geometry_msgs::Pose goal_pose = goal->GoalPose;
    std::vector<float> vel=goal->velocityVector;

    effort_sum=0;

    double freq=goal->frequenz;
    ROS_INFO("set rate: %f",freq);
    ROS_INFO("size vel_Vector: %ld",vel.size());

    ros::Rate rate(freq);
    float diff_x;
    float diff_y;
    float diff_z;
    tf::TransformListener tf;
    tf::StampedTransform transform;
    geometry_msgs::Pose current_pose;
    geometry_msgs::PoseStamped stamp_pose;
    bool is_reached=false;
    bool succes=false;
    int cur_move_time;
    ros::Duration cur_diff;
    ros::Duration cur_hz_diff;
    ros::Time cur_time;
    std::string p_str=movep_URSstring(goal_pose);
    std::string l_str=movel_URSstring(goal_pose);
    ros::Time hz_dur;
    std::string vel_str ;
    std::string acc_str ;
    double blend_rad;
    double joint_sum;

    ROS_INFO("starting publisching");
    int m=0;
    while (m<20){
      m=m+1;
      rate.sleep();
    }
    std::vector<double> y_goal (5);
    hz_dur=ros::Time::now();
    std_msgs::Empty emptyMsg;
    std_msgs::Float32 energy_msg;
    des_pos_pub.publish(emptyMsg);
    ros::Rate(100).sleep();
    int i=0;
    ROS_INFO("set ros time");
    ros::Time start_time=ros::Time::now();
    while (is_reached==false){
      if (!ros::ok()){
        is_reached=true;
      }
      //ROS_INFO(ros::Time::now();)
      //ROS_INFO("delta time; %6.4f", ros::Time::now());
      //effort_sum=effort_sum+effort[0]+effort[1]+effort[2]+effort[3]+effort[4]+effort[5];


      try{
          tf.waitForTransform("/base", "/tool0_controller", ros::Time(0), ros::Duration(1/freq));
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
      diff_x=std::abs((current_pose.position.x)-(goal_pose.position.x));
      diff_y=std::abs((current_pose.position.y)-(goal_pose.position.y));
      diff_z=std::abs((goal_pose.position.z)-(current_pose.position.z));
      real_pos_msg.data=current_pose.position.y;
      real_pos_pub.publish(real_pos_msg);


      cur_time=ros::Time::now();
      cur_diff=cur_time-start_time;
      cur_move_time=cur_diff.toSec();
      cur_hz_diff=cur_time-hz_dur;
      //if (cur_move_time-cur_hz_diff.toSec()>=1/freq){

          if (i==vel.size()-2){
            vel_str = tostr(vel[i-1]);
            is_reached=true;
            succes=true;
            ros::Time end_time=ros::Time::now();
            ROS_INFO("is reached");
            ros::Duration diff=end_time-start_time;
            ROS_INFO("time to move");
            std::cout<<diff;
            std::cout<<"\n"<<"energy: "<<effort_sum<<"\n";
            //movej_msg.data=p_str+"1.8,"+vel_str+",0)";
            movej_msg.data="stopl(0.05)";
            urscript_pub.publish(movej_msg);
            i=i+1;
            }
          else if (i<vel.size()-2){
/*
            joint_sum=0;
            for (int j = 0; j < 6; j++) {
              joint_sum=joint_sum+(std::abs(effort[j]-l_effort[j])*48*1/freq);
              }
            effort_sum=effort_sum+joint_sum;
            energy_msg.data=effort_sum;
            engergy_pub.publish(energy_msg);
*/
            //for position spnlie
            /*
            //position
            y_goal[0]=vel[i];
            //velocity
            y_goal[1]=(vel[i+1]-vel[i])*freq;
            //acceleration
            y_goal[2]=((((vel[i+1]-vel[i])*freq)-((vel[i+2]-vel[i+1])*freq))*freq);
            //heading position
            y_goal[3]=y_goal[0]+(y_goal[1]/freq);
            //blend_radius
            y_goal[4]=(vel[i+1]-vel[i]);
            if (std::abs(y_goal[1])<=0){y_goal[1]=0.00001;}
            if (std::abs(y_goal[2]<=0)){y_goal[2]=0.00001;}
            //if (std::abs(y_goal[4]<=0.00000001)){y_goal[4]=0;}

            //y_goal[1]=0.85;
            //y_goal[4]=0.003;
            if(i>=vel.size()-10){y_goal[4]=0.000;}
            acc_str = tostr(std::abs(y_goal[2])+0.21);
            vel_str = tostr(std::abs(y_goal[1]*1.2));
            //movej_msg.data="movel(p[ 0.5," +tostr(y_goal[0])+ ",0.05,1.1282,1.1320,1.3],"+acc_str+","+vel_str+","+tostr((1/freq)*10)+","+tostr(std::abs(y_goal[4]))+")";

            movej_msg.data="movep(p[ 0.5," +tostr(y_goal[3])+ ",0.05,1.1282,1.1320,1.3],"+acc_str+","+vel_str+","+tostr(std::abs(y_goal[4]))+")";
            //
            */

            //for velocity spline/*

            y_goal=calc_correction_vel(vel[i],tool_speed_y,current_pose.position.y,freq);
            vel_str = tostr(y_goal[i]);
            acc_str = tostr(std::abs(y_goal[1]);

            movej_msg.data="speedl([0,"+vel_str+",0,0,0,0],"+acc_str+","+tostr((1/freq)*5)+")";
            //*/
            //}
            //des_vel_msg.data=-vel[i];
            //des_vel_pub.publish(des_vel_msg);

            urscript_pub.publish(movej_msg);
            i=i+1;
            //hz_dur=ros::Time::now();
            //ROS_INFO("number i: %d",i);
            }
        //}
        /*
      if ((diff_x<=0.0001)&& (diff_y<=0.0001)&& (diff_z<=0.0001)){
        is_reached=true;
        succes=true;
        ros::Time end_time=ros::Time::now();
        ROS_INFO("is reached");
        ros::Duration diff=end_time-start_time;
        ROS_INFO("time to move");
        std::cout<<diff;
      }*/
      if(cur_move_time>((goal->time)*1.5)) {
        is_reached=true;
        ROS_INFO("Time overlap");
        //as_.setAborted(result_);
        std::cout<<cur_move_time;
      }

    rate.sleep();
    //if (i<=vel.size()){
    //}

    }
    return succes;
  }

  bool set_start_pose(geometry_msgs::Pose goal_pose){
    std_msgs::String movej_msg;
    movej_msg.data=movel_URSstring(goal_pose);
    movej_msg.data=movej_msg.data+"3,1.5,0,0)";
    urscript_pub.publish(movej_msg);
    std_msgs::Float32 energy_msg;
    double freq=25;
    double joint_sum;
    ros::Rate rate(freq);
    float diff_x;
    float diff_y;
    float diff_z;
    tf::TransformListener tf;
    tf::StampedTransform transform;
    geometry_msgs::Pose current_pose;
    geometry_msgs::PoseStamped stamp_pose;
    bool is_reached=false;
    bool succes=false;
    int cur_move_time;
    ros::Time cur_time;
    ros::Time start_time=ros::Time::now();
    effort_sum=0;
    while (is_reached==false){
      joint_sum=0;
      for (int j = 0; j < 6; j++) {
        joint_sum=joint_sum+(std::abs(effort[j]-l_effort[j])*48*1/freq);
      }
      effort_sum=effort_sum+joint_sum;
       energy_msg.data=effort_sum;
      engergy_pub.publish(energy_msg);
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
      diff_x=std::abs((current_pose.position.x)-(goal_pose.position.x));
      diff_y=std::abs((current_pose.position.y)-(goal_pose.position.y));
      diff_z=std::abs((goal_pose.position.z)-(current_pose.position.z));

  ros::Time cur_time=ros::Time::now();
  ros::Duration cur_diff=cur_time-start_time;
  cur_move_time=cur_diff.toSec();

      if ((diff_x<=0.0001)&& (diff_y<=0.0001)&& (diff_z<=0.0001)){
        is_reached=true;
        succes=true;
        ros::Time end_time=ros::Time::now();
        ROS_INFO("is reached");
        ros::Duration diff=end_time-start_time;
        ROS_INFO("time to move");
        std::cout<<diff;

        std::cout<<"\n"<<"energy: "<<effort_sum<<"\n";

      }
      if(cur_move_time>60){
        is_reached=true;
        ROS_INFO("Time overlap");
        std::cout<<"energy: "<<effort_sum;
        std::cout<<cur_move_time;
      }
      if (!ros::ok()){
        is_reached=true;
      }
    rate.sleep();
  }
    return succes;
  }


};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "trajectory_execution");

  Trajectory_Execution_Action trajectory_execution("trajectory_execution");
   //ros::Subscriber sub = n.subscribe("/joint_states", 1000, &trajectory_execution::effort_subCB, &trajectory_execution);
  ros::spin();

  return 0;
}
