// Generated by gencpp from file optimation_msgs/TrajectoryExecutionFeedback.msg
// DO NOT EDIT!


#ifndef OPTIMATION_MSGS_MESSAGE_TRAJECTORYEXECUTIONFEEDBACK_H
#define OPTIMATION_MSGS_MESSAGE_TRAJECTORYEXECUTIONFEEDBACK_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace optimation_msgs
{
template <class ContainerAllocator>
struct TrajectoryExecutionFeedback_
{
  typedef TrajectoryExecutionFeedback_<ContainerAllocator> Type;

  TrajectoryExecutionFeedback_()
    : percent_complete(0.0)  {
    }
  TrajectoryExecutionFeedback_(const ContainerAllocator& _alloc)
    : percent_complete(0.0)  {
  (void)_alloc;
    }



   typedef float _percent_complete_type;
  _percent_complete_type percent_complete;





  typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> const> ConstPtr;

}; // struct TrajectoryExecutionFeedback_

typedef ::optimation_msgs::TrajectoryExecutionFeedback_<std::allocator<void> > TrajectoryExecutionFeedback;

typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionFeedback > TrajectoryExecutionFeedbackPtr;
typedef boost::shared_ptr< ::optimation_msgs::TrajectoryExecutionFeedback const> TrajectoryExecutionFeedbackConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d342375c60a5a58d3bc32664070a1368";
  }

  static const char* value(const ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd342375c60a5a58dULL;
  static const uint64_t static_value2 = 0x3bc32664070a1368ULL;
};

template<class ContainerAllocator>
struct DataType< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "optimation_msgs/TrajectoryExecutionFeedback";
  }

  static const char* value(const ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======\n\
# Define a feedback message\n\
float32 percent_complete\n\
\n\
";
  }

  static const char* value(const ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.percent_complete);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TrajectoryExecutionFeedback_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::optimation_msgs::TrajectoryExecutionFeedback_<ContainerAllocator>& v)
  {
    s << indent << "percent_complete: ";
    Printer<float>::stream(s, indent + "  ", v.percent_complete);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OPTIMATION_MSGS_MESSAGE_TRAJECTORYEXECUTIONFEEDBACK_H