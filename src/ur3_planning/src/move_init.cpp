/**********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Sachin Chitta, Michael Lautman */
#include <pluginlib/class_loader.h>
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <moveit_msgs/MoveItErrorCodes.h>
// MoveIt!
#include <moveit_msgs/PlanningScene.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/GetStateValidity.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/ApplyPlanningScene.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit/move_group_interface/move_group_interface.h>

#include <moveit/planning_interface/planning_interface.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/kinematic_constraints/utils.h>

#include <boost/scoped_ptr.hpp>

// BEGIN_SUB_TUTORIAL stateFeasibilityTestExample
//
// User defined constraints can also be specified to the PlanningScene
// class. This is done by specifying a callback using the
// setStateFeasibilityPredicate function. Here's a simple example of a
// user-defined callback that checks whether the "panda_joint1" of
// the Panda robot is at a positive or negative angle:
/*bool stateFeasibilityTestExample(const robot_state::RobotState& kinematic_state, bool verbose)
{
  const double* joint_values = kinematic_state.getJointPositions("panda_joint1");
  return (joint_values[0] > 0.0);
}
// END_SUB_TUTORIAL
*/
int main(int argc, char** argv)
{
  ros::init(argc, argv, "motion_planning");
  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::NodeHandle node_handle;

//ADD table to world
  ros::Publisher planning_scene_diff_publisher = node_handle.advertise<moveit_msgs::PlanningScene>("planning_scene", 1);
  ros::WallDuration sleep_t(0.5);

  const std::string PLANNING_GROUP = "manipulator";
  robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
  robot_model::RobotModelPtr robot_model = robot_model_loader.getModel();
  planning_scene::PlanningScene planning_scene(robot_model);
  /* Create a RobotState and JointModelGroup to keep track of the current robot pose and planning group*/
  robot_state::RobotStatePtr robot_state(new robot_state::RobotState(robot_model));
  const robot_state::JointModelGroup* joint_model_group = robot_state->getJointModelGroup(PLANNING_GROUP);


  moveit_msgs::AttachedCollisionObject attached_object;
  attached_object.link_name = "base_link";
  /* The header must contain a valid TF frame*/
  attached_object.object.header.frame_id = "base_link";
  /* The id of the object */
  attached_object.object.id = "ground";

  /* A default pose */
  geometry_msgs::Pose ground_pose;
  ground_pose.position.z = -0.10;
  ground_pose.orientation.w = 1.0;

  /* Define a box to be attached */
  shape_msgs::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  primitive.dimensions[0] = 1;
  primitive.dimensions[1] = 1;
  primitive.dimensions[2] = 0.1;

  attached_object.object.primitives.push_back(primitive);
  attached_object.object.primitive_poses.push_back(ground_pose);

  // Add an object into the environment
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  // Add the object into the environment by adding it to
  // the set of collision objects in the "world" part of the
  // planning scene. Note that we are using only the "object"
  // field of the attached_object message here.
  ROS_INFO("Adding the object into the world ");
  moveit_msgs::PlanningScene ur3_planning_scene;
  ur3_planning_scene.world.collision_objects.push_back(attached_object.object);
  ur3_planning_scene.is_diff = true;
  planning_scene_diff_publisher.publish(ur3_planning_scene);


  collision_detection::CollisionRequest collision_request;
  collision_detection::CollisionResult collision_result;
  planning_scene.checkSelfCollision(collision_request, collision_result);
  ROS_INFO_STREAM("Test 1: Current state is " << (collision_result.collision ? "in" : "not in") << " self collision");



/*****************************************/
//Motion planning
// Note that we are using the ROS pluginlib library here.
/*boost::scoped_ptr<pluginlib::ClassLoader<planning_interface::PlannerManager>> planner_plugin_loader;
planning_interface::PlannerManagerPtr planner_instance;
std::string planner_plugin_name;
// We will get the name of planning plugin we want to load
// from the ROS parameter server, and then load the planner
// making sure to catch all exceptions.
if (!node_handle.getParam("planning_plugin", planner_plugin_name))
  ROS_FATAL_STREAM("Could not find planner plugin name");
try
{
  planner_plugin_loader.reset(new pluginlib::ClassLoader<planning_interface::PlannerManager>(
      "moveit_core", "planning_interface::PlannerManager"));
}
catch (pluginlib::PluginlibException& ex)
{
  ROS_FATAL_STREAM("Exception while creating planning plugin loader " << ex.what());
}
try
{
  planner_instance.reset(planner_plugin_loader->createUnmanagedInstance(planner_plugin_name));
  if (!planner_instance->initialize(robot_model, node_handle.getNamespace()))
    ROS_FATAL_STREAM("Could not initialize planner instance");
  ROS_INFO_STREAM("Using planning interface '" << planner_instance->getDescription() << "'");
}
catch (pluginlib::PluginlibException& ex)
{
  const std::vector<std::string>& classes = planner_plugin_loader->getDeclaredClasses();
  std::stringstream ss;
  for (std::size_t i = 0; i < classes.size(); ++i)
    ss << classes[i] << " ";
  ROS_ERROR_STREAM("Exception while loading planner '" << planner_plugin_name << "': " << ex.what() << std::endl
                                                       << "Available plugins: " << ss.str());
}

// Pose Goal
// ^^^^^^^^^
// We will now create a motion plan request for the arm of the Panda
// specifying the desired pose of the end-effector as input.
planning_interface::MotionPlanRequest req;
planning_interface::MotionPlanResponse res;
geometry_msgs::PoseStamped pose;
pose.header.frame_id = "base_link";
pose.pose.position.x = 0.3;
pose.pose.position.y = 0.2;
pose.pose.position.z = 0.1;
pose.pose.orientation.w = 1.0;

// A tolerance of 0.01 m is specified in position
// and 0.01 radians in orientation
std::vector<double> tolerance_pose(3, 0.01);
std::vector<double> tolerance_angle(3, 0.01);
  // .. _kinematic_constraints:
req.group_name = "manipulator";
moveit_msgs::Constraints pose_goal =
    kinematic_constraints::constructGoalConstraints("wrist_3_joint", pose, tolerance_pose, tolerance_angle);
req.goal_constraints.push_back(pose_goal);

// We now construct a planning context that encapsulate the scene,
// the request and the response. We call the planner using this
// planning context

planning_interface::PlanningContextPtr context;
context =  planner_instance->getPlanningContext(planning_scene, req, res.error_code_) const = 0;
context->solve(res);
if (res.error_code_.val != res.error_code_.SUCCESS)
{
  ROS_ERROR("Could not compute plan successfully");
  return 0;
}
// Visualize the result
// ^^^^^^^^^^^^^^^^^^^^
ros::Publisher display_publisher =
    node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
moveit_msgs::DisplayTrajectory display_trajectory;

/* Visualize the trajectory
ROS_INFO("Visualizing the trajectory");
moveit_msgs::MotionPlanResponse response;
res.getMessage(response);

display_trajectory.trajectory_start = response.trajectory_start;
display_trajectory.trajectory.push_back(response.trajectory);
display_publisher.publish(display_trajectory);

*/
  ros::shutdown();
  return 0;
}
