# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from optimation_msgs/trajectory_optimation_msg.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import std_msgs.msg

class trajectory_optimation_msg(genpy.Message):
  _md5sum = "85f20d48235c676a951608690ba6db9d"
  _type = "optimation_msgs/trajectory_optimation_msg"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """geometry_msgs/Pose startPose
geometry_msgs/Pose goalPose
std_msgs/Float32 time

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of position and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: std_msgs/Float32
float32 data"""
  __slots__ = ['startPose','goalPose','time']
  _slot_types = ['geometry_msgs/Pose','geometry_msgs/Pose','std_msgs/Float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       startPose,goalPose,time

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(trajectory_optimation_msg, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.startPose is None:
        self.startPose = geometry_msgs.msg.Pose()
      if self.goalPose is None:
        self.goalPose = geometry_msgs.msg.Pose()
      if self.time is None:
        self.time = std_msgs.msg.Float32()
    else:
      self.startPose = geometry_msgs.msg.Pose()
      self.goalPose = geometry_msgs.msg.Pose()
      self.time = std_msgs.msg.Float32()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_14df().pack(_x.startPose.position.x, _x.startPose.position.y, _x.startPose.position.z, _x.startPose.orientation.x, _x.startPose.orientation.y, _x.startPose.orientation.z, _x.startPose.orientation.w, _x.goalPose.position.x, _x.goalPose.position.y, _x.goalPose.position.z, _x.goalPose.orientation.x, _x.goalPose.orientation.y, _x.goalPose.orientation.z, _x.goalPose.orientation.w, _x.time.data))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.startPose is None:
        self.startPose = geometry_msgs.msg.Pose()
      if self.goalPose is None:
        self.goalPose = geometry_msgs.msg.Pose()
      if self.time is None:
        self.time = std_msgs.msg.Float32()
      end = 0
      _x = self
      start = end
      end += 116
      (_x.startPose.position.x, _x.startPose.position.y, _x.startPose.position.z, _x.startPose.orientation.x, _x.startPose.orientation.y, _x.startPose.orientation.z, _x.startPose.orientation.w, _x.goalPose.position.x, _x.goalPose.position.y, _x.goalPose.position.z, _x.goalPose.orientation.x, _x.goalPose.orientation.y, _x.goalPose.orientation.z, _x.goalPose.orientation.w, _x.time.data,) = _get_struct_14df().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_14df().pack(_x.startPose.position.x, _x.startPose.position.y, _x.startPose.position.z, _x.startPose.orientation.x, _x.startPose.orientation.y, _x.startPose.orientation.z, _x.startPose.orientation.w, _x.goalPose.position.x, _x.goalPose.position.y, _x.goalPose.position.z, _x.goalPose.orientation.x, _x.goalPose.orientation.y, _x.goalPose.orientation.z, _x.goalPose.orientation.w, _x.time.data))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.startPose is None:
        self.startPose = geometry_msgs.msg.Pose()
      if self.goalPose is None:
        self.goalPose = geometry_msgs.msg.Pose()
      if self.time is None:
        self.time = std_msgs.msg.Float32()
      end = 0
      _x = self
      start = end
      end += 116
      (_x.startPose.position.x, _x.startPose.position.y, _x.startPose.position.z, _x.startPose.orientation.x, _x.startPose.orientation.y, _x.startPose.orientation.z, _x.startPose.orientation.w, _x.goalPose.position.x, _x.goalPose.position.y, _x.goalPose.position.z, _x.goalPose.orientation.x, _x.goalPose.orientation.y, _x.goalPose.orientation.z, _x.goalPose.orientation.w, _x.time.data,) = _get_struct_14df().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_14df = None
def _get_struct_14df():
    global _struct_14df
    if _struct_14df is None:
        _struct_14df = struct.Struct("<14df")
    return _struct_14df
