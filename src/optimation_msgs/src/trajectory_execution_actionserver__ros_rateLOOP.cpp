#include <ros/ros.h>
#include <optimation_msgs/TrajectoryExecutionAction.h>  // Note: "Action" is appended
#include <actionlib/server/simple_action_server.h>
// MoveIt!
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

typedef actionlib::SimpleActionServer<optimation_msgs::TrajectoryExecutionAction> Server;
optimation_msgs::TrajectoryExecutionResult result_;
optimation_msgs::TrajectoryExecutionFeedback feedback_;

template <typename T> std::string tostr(const T& t) {
   std::ostringstream os;
   os<<t;
   return os.str();
 }

std::string movej_URSstring(geometry_msgs::Pose pose);
bool set_start_pose(geometry_msgs::Pose start_pose,ros::Publisher ur_pub);
void execute(const optimation_msgs::TrajectoryExecutionGoalConstPtr& goal, Server* as)  // Note: "Action" is not appended to DoDishes here
{
  std::string  start_pose=Pose_to_URSstring(goal->StartPose);

  // Do lots of awesome groundbreaking robot stuff here
  //as_.publishFeedback(feedback_);
  std::vector<float>  g=goal->velocityVector;
  float angle=goal->StartPose.orientation.x;
  result_.energy=angle;
  as->setSucceeded(result_);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "trajectory_execution_actionserver");
  ros::NodeHandle n;
  Server server(n, "trajectory_execution", boost::bind(&execute, _1, &server), false);
  server.start();
  ros::Publisher urscript_pub = urs_nh.advertise<std_msgs::String>("/ur_driver/URScript", 1);
  ros::spin();
  /*// .. _RobotModelLoader: http://docs.ros.org/indigo/api/moveit_ros_planning/html/classrobot__model__loader_1_1RobotModelLoader.html
 robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
 robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
 robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));
 kinematic_state->setToDefaultValues();
 const robot_state::JointModelGroup* joint_model_group = kinematic_model->getJointModelGroup("manipulator");
 const std::vector<std::string> &joint_names = joint_model_group->getJointModelNames();
 */
  return 0;
}
bool set_start_pose(geometry_msgs::Pose start_pose,ros::Publisher ur_pub){
  std::string movej_msg=movej_URSstring(start_pose);
  movej_msg=movej_msg+"0.8,0.7,0)";
  ur_pub.publish(movej_msg);
  double freq=50;
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
  while (is_reached==false){
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

cur_time=ros::Time::now();
ros::Duration cur_diff=cur_time-start_time;
cur_move_time=cur_diff.toSec();

    if ((diff_x<=0.00005)&& (diff_y<=0.00005)&& (diff_z<=0.00005)){
      is_reached=true;
      succes=true;
      ros::Time end_time=ros::Time::now();
      ROS_INFO("is reached");
      ros::Duration diff=end_time-start_time;
      ROS_INFO("time to move");
      std::cout<<diff;
    }
    if(cur_move_time>30){
      is_reached=true;
      ROS_INFO("Time overlap");
      std::cout<<cur_move_time;
    }
    if (!ros::ok()){
      is_reached=true;
    }
  rate.sleep();
  }
  return succes;
}
std::string movej_URSstring(geometry_msgs::Pose pose){
  std::string px = tostr(pose.position.x);
  std::string py = tostr(pose.position.y);
  std::string pz = tostr(pose.position.z);
  std::string rx = tostr(pose.orientation.x);
  std::string ry = tostr(pose.orientation.y);
  std::string rz = tostr(pose.orientation.z);
  std::string msg;
  msg="movej(p[" +px+","+py+","+pz+","+rx+","+ry+","+rz+"],";
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
  msg="movep(p[" +px+","+py+","+pz+","+rx+","+ry+","+rz+"],";
  return msg;
}
