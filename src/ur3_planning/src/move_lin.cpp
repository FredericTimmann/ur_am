
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include "rosbag/bag.h"
#include <std_msgs/Int32.h>
#include <moveit/planning_interface/planning_interface.h>
#include <moveit/kinematic_constraints/utils.h>
#include <geometry_msgs/PoseStamped.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <pluginlib/class_loader.h>
#include <ros/ros.h>
//#include <moveit/moveit_core.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_model/robot_model.h>


void chatterCallback(const sensor_msgs::JointState::ConstPtr& msg)
{
  //ROS_INFO("callback triggered");
  rosbag::Bag bag;
  bag.open("testmove.bag", rosbag::bagmode::Write);
  bag.write("joint_states", ros::Time::now(),msg);
  bag.close();

}

int main(int argc, char** argv)
{
// ROS i n i t i a l i z a t i o n
ros::init(argc, argv, "motion_planning");
ros::AsyncSpinner spinner(1);
spinner.start();
ros::NodeHandle node_handle;

// Setup
//The MoveGroup c l a s s can be s e t u p using j u s t t h e name o f t h e group
// t h a t t h e u s e r s would l i k e t o c o n t r o l and plan f o r .

moveit::planning_interface::MoveGroupInterface group("manipulator");
moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
// C r e a t e a p u b l i s h e r f o r v i s u a l i z i n g p l a n s in RViz .
ros::Publisher display_publisher =node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path",1,true);
moveit_msgs::DisplayTrajectory display_trajectory;

// Getting Basic Information
group.setPoseReferenceFrame("/dummy");
group.setEndEffectorLink("ee_link");
// P r i n t t h e name o f t h e r e f e r e n c e frame f o r t h i s r o b o t .
ROS_INFO("Reference frame : %s " , group.getPlanningFrame().c_str());
// P r i n t t h e name o f t h e end − e f f e c t o r l i n k f o r t h i s group .
ROS_INFO("Reference frame : %s " ,group.getEndEffectorLink().c_str());


//StartPosition
geometry_msgs::PoseStamped start_pose;
start_pose.header.frame_id = "dummy";
start_pose.pose.position.x = 0.2;
start_pose.pose.position.y = 0.2;
start_pose.pose.position.z = 0.0;
start_pose.pose.orientation.x = -0.5;
start_pose.pose.orientation.y = 0.5;
start_pose.pose.orientation.z = 0.50;
start_pose.pose.orientation.w = 0.50;


group.setPoseTarget(start_pose);
ROS_INFO_STREAM("Planning to move " <<
                group.getEndEffectorLink() << " to a target pose expressed in " <<
                 group.getPlanningFrame());
group.setStartStateToCurrentState();
group.setMaxVelocityScalingFactor(1.0);
moveit::planning_interface::MoveGroupInterface::Plan my_plan;
//set maximum time to find a plan
group.setPlanningTime(5.0);
moveit::planning_interface::MoveItErrorCode success;
success = group.plan(my_plan);
if ( !success ) throw std::runtime_error("No plan found");
else ROS_INFO_STREAM("Plan found in " << my_plan.planning_time_ << " seconds");
group.setGoalPositionTolerance(0.00001);
ros::Time start = ros::Time::now();
group.execute(my_plan);
ROS_INFO_STREAM("Motion duration: " << (ros::Time::now() - start).toSec());

// Plan C a r t e s i a n p a t h s
// Plan C a r t e s i a n p a t h s by s p e c i f y i n g a l i s t o f w a y p o i n t s f o r t h e end − e f f e c t o r t o go through .

std::vector<geometry_msgs::Pose>waypoints;
geometry_msgs::Pose target_pose=group.getCurrentPose().pose ;
waypoints.push_back(target_pose);

target_pose.position.x=0.2;
target_pose.position.y=0.3;
target_pose.position.z=0.0;
waypoints.push_back(target_pose);
/*
target_pose.position.x=0.2;
target_pose.position.y=0.25;
target_pose.position.z=0.0;
waypoints.push_back(target_pose);
target_pose.position.x=0.2;
target_pose.position.y=0.275;
target_pose.position.z=0.0;
waypoints.push_back(target_pose);
target_pose.position.x=0.2;
target_pose.position.y=0.300;
target_pose.position.z=0.0;
waypoints.push_back(target_pose);
*/
moveit_msgs::OrientationConstraint ocm;
ocm.link_name = "ee_link";
ocm.header.frame_id = "/dummy";
ocm.orientation.w = 1.0;
ocm.absolute_x_axis_tolerance = 0.1;
ocm.absolute_y_axis_tolerance = 0.1;
ocm.absolute_z_axis_tolerance = 0.1;
ocm.weight = 1.0;

moveit_msgs::PositionConstraint pcm;
pcm.link_name = "ee_link";
pcm.header.frame_id = "/dummy";
pcm.target_point_offset.x = 0.0001;
pcm.target_point_offset.y = 0.0001;
pcm.target_point_offset.z = 0.01;
pcm.weight = 1.0;

moveit_msgs::Constraints test_constraints;
test_constraints.orientation_constraints.push_back(ocm);
test_constraints.position_constraints.push_back(pcm);
group.setPathConstraints(test_constraints);
group.setGoalPositionTolerance(0.001);

moveit_msgs::RobotTrajectory trajectory;
group.setPlanningTime(10.0);
group.setMaxAccelerationScalingFactor(0.25);
group.setMaxVelocityScalingFactor(1.0);
// S p e c i f y 0 . 0 1 a s t h e max s t e p in c a r t e s i a n t r a n s l a t i o n
// which e n a b l e s t h e c a r t e s i a n path t o be i n t e r p o l a t e d
// a t a r e s o l u t i o n o f 1 cm . S p e c i f y t h e jump t h r e s h o l d
// a s 0 . 0 t o a v o i d j o i n t − s t a t e jumps .
const double jump_threshold =0.0;
const double eef_step=0.001;
double fraction=group.computeCartesianPath(waypoints,eef_step,jump_threshold , trajectory,true);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (cartesian path) (%.2f%% acheived)", fraction * 100.0);
// Plan t h e C a r t e s i a n t r a j e c t o r y and e x e c u t e t h e plan .
ROS_INFO_STREAM ( "cartesian path .....");
moveit::planning_interface::MoveGroupInterface::Plan my_cartesian_plan;
my_cartesian_plan.trajectory_=trajectory;
group.execute(my_cartesian_plan);

ros::Subscriber sub =  node_handle.subscribe("/joint_states", 1000, chatterCallback);
ros::Duration(0.1).sleep();
// S l e e p t o g i v e R v i z time t o v i s u a l i z e t h e plan .
sleep(0.5);

//JointGoal
/*
moveit::planning_interface::MoveGroupInterface::Plan my_joint_plan;
std::vector<double> group_variable_values;
group.getCurrentState()->copyJointGroupPositions(group.getCurrentState()->getRobotModel()->getJointModelGroup(group.getName()), group_variable_values);
group_variable_values={-1.8419836203204554, -2.151076618825094, -1.9421408812152308, -0.6199949423419397, 1.5710140466690063, -0.27041370073427373};
group.setJointValueTarget(group_variable_values);
group.plan(my_joint_plan);
group.execute(my_joint_plan);
ROS_INFO("executing jointgoalplan");
*/
// Wait f o r t h e u s e r t o h i t CTRL − C
sleep(0.5);
ros::shutdown();
return 0;
}
