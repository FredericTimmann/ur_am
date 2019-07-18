// Generated by gencpp from file optimation_msgs/TrajectoryExecutionActionGoal.msg
// DO NOT EDIT!


#ifndef OPTIMATION_MSGS_MESSAGE_TRAJECTORYEXECUTIONACTIONGOAL_H
#define OPTIMATION_MSGS_MESSAGE_TRAJECTORYEXECUTIONACTIONGOAL_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <actionlib_msgs/GoalID.h>
#include <optimation_msgs/TrajectoryExecutionGoal.h>

namespace optimation_msgs
{
template <class ContainerAllocator>
struct TrajectoryExecutionActionGoal_
{
  typedef TrajectoryExecutionActionGoal_<ContainerAllocator> Type;

  TrajectoryExecutionActionGoal_()
    : header()
    , goal_id()
    , goal()  {
    }
  TrajectoryExecutionActionGoal_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , goal_id(_alloc)
    , goal(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::actionlib_msgs::GoalID_<ContainerAllocator>  _goal_id_type;
  _goal_id_type goal_id;

   typedef  ::optimation_msgs::TrajectoryExecutionGoal_<ContainerAllocator>  _goal_type;
  _goal_type goal;





  typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> const> ConstPtr;

}; // struct TrajectoryExecutionActionGoal_

typedef ::optimation_msgs::TrajectoryExecutionActionGoal_<std::allocator<void> > TrajectoryExecutionActionGoal;

typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionActionGoal > TrajectoryExecutionActionGoalPtr;
typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionActionGoal const> TrajectoryExecutionActionGoalConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace optimation_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'optimation_msgs': ['/home/frederic/ur_am/src/optimation_msgs/msg', '/home/frederic/ur_am/devel/share/optimation_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f7f81dd7752d603b74ca2dd5885eec99";
  }

  static const char* value(const ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf7f81dd7752d603bULL;
  static const uint64_t static_value2 = 0x74ca2dd5885eec99ULL;
};

template<class ContainerAllocator>
struct DataType< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "optimation_msgs/TrajectoryExecutionActionGoal";
  }

  static const char* value(const ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
\n\
Header header\n\
actionlib_msgs/GoalID goal_id\n\
TrajectoryExecutionGoal goal\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: actionlib_msgs/GoalID\n\
# The stamp should store the time at which this goal was requested.\n\
# It is used by an action server when it tries to preempt all\n\
# goals that were requested before a certain time\n\
time stamp\n\
\n\
# The id provides a way to associate feedback and\n\
# result message with specific goal requests. The id\n\
# specified must be unique.\n\
string id\n\
\n\
\n\
================================================================================\n\
MSG: optimation_msgs/TrajectoryExecutionGoal\n\
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define the goal\n\
float32[] velocityVector\n\
float32 frequenz\n\
float32 time\n\
geometry_msgs/Pose StartPose\n\
geometry_msgs/Pose GoalPose\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.goal_id);
      stream.next(m.goal);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TrajectoryExecutionActionGoal_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::optimation_msgs::TrajectoryExecutionActionGoal_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "goal_id: ";
    s << std::endl;
    Printer< ::actionlib_msgs::GoalID_<ContainerAllocator> >::stream(s, indent + "  ", v.goal_id);
    s << indent << "goal: ";
    s << std::endl;
    Printer< ::optimation_msgs::TrajectoryExecutionGoal_<ContainerAllocator> >::stream(s, indent + "  ", v.goal);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OPTIMATION_MSGS_MESSAGE_TRAJECTORYEXECUTIONACTIONGOAL_H
