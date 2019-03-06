
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include "rosbag/bag.h"
#include <std_msgs/Int32.h>


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
// P r i n t t h e name o f t h e r e f e r e n c e frame f o r t h i s r o b o t .
ROS_INFO("Reference frame : %s " , group.getPlanningFrame().c_str());
// P r i n t t h e name o f t h e end − e f f e c t o r l i n k f o r t h i s group .
ROS_INFO("Reference frame : %s " ,group.getEndEffectorLink().c_str());

// Plan C a r t e s i a n p a t h s
// Plan C a r t e s i a n p a t h s by s p e c i f y i n g a l i s t o f w a y p o i n t s f o r t h e end − e f f e c t o r t o go through .

std::vector<geometry_msgs::Pose>waypoints;
geometry_msgs::Pose target_pose=group.getCurrentPose().pose ;

target_pose.position.x+=0.2;
waypoints.push_back(target_pose);

target_pose.position.z-=0.2;
waypoints.push_back(target_pose);
/*
target_pose.position.x+=0.1;
waypoints.push_back(target_pose);

target_pose.position.y+=0.1;
waypoints.push_back(target_pose);
*/

moveit_msgs::RobotTrajectory trajectory;
group.setPlanningTime(10.0);
group.setMaxAccelerationScalingFactor(0.7);
group.setMaxVelocityScalingFactor(0.1);
// S p e c i f y 0 . 0 1 a s t h e max s t e p in c a r t e s i a n t r a n s l a t i o n
// which e n a b l e s t h e c a r t e s i a n path t o be i n t e r p o l a t e d
// a t a r e s o l u t i o n o f 1 cm . S p e c i f y t h e jump t h r e s h o l d
// a s 0 . 0 t o a v o i d j o i n t − s t a t e jumps .
const double jump_threshold =0.0;
const double eef_step=0.01;
double fraction=group.computeCartesianPath(waypoints,eef_step,jump_threshold , trajectory,true);
//ROS_INFO("Visualizing plan 3 (cartesian path) ",fraction*100);
// Plan t h e C a r t e s i a n t r a j e c t o r y and e x e c u t e t h e plan .
ROS_INFO_STREAM ( "cartesian path .....");
moveit::planning_interface::MoveGroupInterface::Plan my_plan;
my_plan.trajectory_=trajectory;
group.execute(my_plan);
rosbag::Bag bag("test.bag", rosbag::bagmode::Write);
std_msgs::Int32 i;
i.data = 42;
bag.write("numbers", ros::Time::now(), i);
bag.close();
// S l e e p t o g i v e R v i z time t o v i s u a l i z e t h e plan .
sleep(0.5);
// Wait f o r t h e u s e r t o h i t CTRL − C
ros::shutdown();
return 0;
}
