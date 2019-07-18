// Generated by gencpp from file optimation_msgs/trajectory_optimation_serviceRequest.msg
// DO NOT EDIT!


#ifndef OPTIMATION_MSGS_MESSAGE_TRAJECTORY_OPTIMATION_SERVICEREQUEST_H
#define OPTIMATION_MSGS_MESSAGE_TRAJECTORY_OPTIMATION_SERVICEREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Float32.h>

namespace optimation_msgs
{
template <class ContainerAllocator>
struct trajectory_optimation_serviceRequest_
{
  typedef trajectory_optimation_serviceRequest_<ContainerAllocator> Type;

  trajectory_optimation_serviceRequest_()
    : startPose()
    , goalPose()
    , time()  {
    }
  trajectory_optimation_serviceRequest_(const ContainerAllocator& _alloc)
    : startPose(_alloc)
    , goalPose(_alloc)
    , time(_alloc)  {
  (void)_alloc;
    }



   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _startPose_type;
  _startPose_type startPose;

   typedef  ::geometry_msgs::Pose_<ContainerAllocator>  _goalPose_type;
  _goalPose_type goalPose;

   typedef  ::std_msgs::Float32_<ContainerAllocator>  _time_type;
  _time_type time;





  typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> const> ConstPtr;

}; // struct trajectory_optimation_serviceRequest_

typedef ::optimation_msgs::trajectory_optimation_serviceRequest_<std::allocator<void> > trajectory_optimation_serviceRequest;

typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceRequest > trajectory_optimation_serviceRequestPtr;
typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceRequest const> trajectory_optimation_serviceRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace optimation_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'optimation_msgs': ['/home/frederic/ur_am/src/optimation_msgs/msg', '/home/frederic/ur_am/devel/share/optimation_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "85f20d48235c676a951608690ba6db9d";
  }

  static const char* value(const ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x85f20d48235c676aULL;
  static const uint64_t static_value2 = 0x951608690ba6db9dULL;
};

template<class ContainerAllocator>
struct DataType< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "optimation_msgs/trajectory_optimation_serviceRequest";
  }

  static const char* value(const ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "geometry_msgs/Pose startPose\n\
geometry_msgs/Pose goalPose\n\
std_msgs/Float32 time\n\
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
\n\
================================================================================\n\
MSG: std_msgs/Float32\n\
float32 data\n\
";
  }

  static const char* value(const ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.startPose);
      stream.next(m.goalPose);
      stream.next(m.time);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct trajectory_optimation_serviceRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::optimation_msgs::trajectory_optimation_serviceRequest_<ContainerAllocator>& v)
  {
    s << indent << "startPose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.startPose);
    s << indent << "goalPose: ";
    s << std::endl;
    Printer< ::geometry_msgs::Pose_<ContainerAllocator> >::stream(s, indent + "  ", v.goalPose);
    s << indent << "time: ";
    s << std::endl;
    Printer< ::std_msgs::Float32_<ContainerAllocator> >::stream(s, indent + "  ", v.time);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OPTIMATION_MSGS_MESSAGE_TRAJECTORY_OPTIMATION_SERVICEREQUEST_H
