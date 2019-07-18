// Generated by gencpp from file optimation_msgs/trajectory_optimation_serviceResponse.msg
// DO NOT EDIT!


#ifndef OPTIMATION_MSGS_MESSAGE_TRAJECTORY_OPTIMATION_SERVICERESPONSE_H
#define OPTIMATION_MSGS_MESSAGE_TRAJECTORY_OPTIMATION_SERVICERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/String.h>

namespace optimation_msgs
{
template <class ContainerAllocator>
struct trajectory_optimation_serviceResponse_
{
  typedef trajectory_optimation_serviceResponse_<ContainerAllocator> Type;

  trajectory_optimation_serviceResponse_()
    : serverstate()  {
    }
  trajectory_optimation_serviceResponse_(const ContainerAllocator& _alloc)
    : serverstate(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::String_<ContainerAllocator>  _serverstate_type;
  _serverstate_type serverstate;





  typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> const> ConstPtr;

}; // struct trajectory_optimation_serviceResponse_

typedef ::optimation_msgs::trajectory_optimation_serviceResponse_<std::allocator<void> > trajectory_optimation_serviceResponse;

typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceResponse > trajectory_optimation_serviceResponsePtr;
typedef boost::shared_ptr< ::optimation_msgs::trajectory_optimation_serviceResponse const> trajectory_optimation_serviceResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace optimation_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'optimation_msgs': ['/home/frederic/ur_am/src/optimation_msgs/msg', '/home/frederic/ur_am/devel/share/optimation_msgs/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'actionlib_msgs': ['/opt/ros/kinetic/share/actionlib_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4a016c0e523ccb8d38a68660d0e1664d";
  }

  static const char* value(const ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4a016c0e523ccb8dULL;
  static const uint64_t static_value2 = 0x38a68660d0e1664dULL;
};

template<class ContainerAllocator>
struct DataType< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "optimation_msgs/trajectory_optimation_serviceResponse";
  }

  static const char* value(const ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/String serverstate\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/String\n\
string data\n\
";
  }

  static const char* value(const ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.serverstate);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct trajectory_optimation_serviceResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::optimation_msgs::trajectory_optimation_serviceResponse_<ContainerAllocator>& v)
  {
    s << indent << "serverstate: ";
    s << std::endl;
    Printer< ::std_msgs::String_<ContainerAllocator> >::stream(s, indent + "  ", v.serverstate);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OPTIMATION_MSGS_MESSAGE_TRAJECTORY_OPTIMATION_SERVICERESPONSE_H