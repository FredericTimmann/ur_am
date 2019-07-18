#include <ros/ros.h>
#include "rosbag/bag.h"
#include "control_msgs/FollowJointTrajectoryActionGoal.h"
//#include "trajectory_msgs/JoinTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"
#include <tf/transform_listener.h>
 #include <geometry_msgs/Pose.h>
 #include <sensor_msgs/JointState.h>
 #include <std_msgs/Float64.h>
 #include <std_msgs/Float32.h>
#include <tf/transform_broadcaster.h>
//#include <Vector3.h>
class listener
{
protected:
  ros::Publisher sum_effort_pub;
  ros::Subscriber effort_sub;


public:
ros::NodeHandle nh_;
  std::vector<double> effort;
  float effort_sum;
  std_msgs::Float32 effort_msg;

  listener(){
    effort_sub =  nh_.subscribe<sensor_msgs::JointState>("/joint_states", 1, &listener::effort_subCB, this);

    sum_effort_pub= nh_.advertise<std_msgs::Float32>("/joint_effort_sum", 100);
  }
  ~listener(void)
  {
  }

void setup_subscriber(){
  effort_sub =  nh_.subscribe<sensor_msgs::JointState>("/joint_states", 1, &listener::effort_subCB, this);
}
void effort_subCB(const sensor_msgs::JointStateConstPtr &states ){
  effort=states->effort;
  effort_sum=0;
  for (int i = 0; i < 6; i++) {
    effort_sum+=std::abs(effort[i]);
    }
    //effort_sum=123;
    //this->effort_sum=123;
  }

void publish_effort_(){

  effort_msg.data=effort_sum;
  sum_effort_pub.publish(effort_msg);
  }

//end of class
};

int main(int argc, char **argv)
{
// ROS i n i t i a l i z a t i o n
ros::init(argc, argv, "edits_pub");
//ros::NodeHandle node;

tf::TransformBroadcaster br;
  tf::Transform transform;

listener effort_listener;
ros::Subscriber sub = effort_listener.nh_.subscribe("/joint_states", 100, &listener::effort_subCB, &effort_listener);
//effort_listener.setup_subscriber();
ros::Rate rate(100.0);
  while (ros::ok()){
    effort_listener.publish_effort_();
    transform.setOrigin( tf::Vector3(-0.35, 0.0, 0.0) );
    transform.setRotation( tf::Quaternion(0, 0, 1, 0) );
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "printing_frame"));
    ros::spinOnce();
    rate.sleep();
    }

return 0;
}
