# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from optimation_msgs/TrajectoryExecutionGoal.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg

class TrajectoryExecutionGoal(genpy.Message):
  _md5sum = "ea451a2ad70ed9c78ee392b0e39f6b47"
  _type = "optimation_msgs/TrajectoryExecutionGoal"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
# Define the goal
float32[] velocityVector
float32 frequenz
float32 time
geometry_msgs/Pose StartPose
geometry_msgs/Pose GoalPose

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
"""
  __slots__ = ['velocityVector','frequenz','time','StartPose','GoalPose']
  _slot_types = ['float32[]','float32','float32','geometry_msgs/Pose','geometry_msgs/Pose']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       velocityVector,frequenz,time,StartPose,GoalPose

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TrajectoryExecutionGoal, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.velocityVector is None:
        self.velocityVector = []
      if self.frequenz is None:
        self.frequenz = 0.
      if self.time is None:
        self.time = 0.
      if self.StartPose is None:
        self.StartPose = geometry_msgs.msg.Pose()
      if self.GoalPose is None:
        self.GoalPose = geometry_msgs.msg.Pose()
    else:
      self.velocityVector = []
      self.frequenz = 0.
      self.time = 0.
      self.StartPose = geometry_msgs.msg.Pose()
      self.GoalPose = geometry_msgs.msg.Pose()

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
      length = len(self.velocityVector)
      buff.write(_struct_I.pack(length))
      pattern = '<%sf'%length
      buff.write(struct.pack(pattern, *self.velocityVector))
      _x = self
      buff.write(_get_struct_2f14d().pack(_x.frequenz, _x.time, _x.StartPose.position.x, _x.StartPose.position.y, _x.StartPose.position.z, _x.StartPose.orientation.x, _x.StartPose.orientation.y, _x.StartPose.orientation.z, _x.StartPose.orientation.w, _x.GoalPose.position.x, _x.GoalPose.position.y, _x.GoalPose.position.z, _x.GoalPose.orientation.x, _x.GoalPose.orientation.y, _x.GoalPose.orientation.z, _x.GoalPose.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.StartPose is None:
        self.StartPose = geometry_msgs.msg.Pose()
      if self.GoalPose is None:
        self.GoalPose = geometry_msgs.msg.Pose()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sf'%length
      start = end
      end += struct.calcsize(pattern)
      self.velocityVector = struct.unpack(pattern, str[start:end])
      _x = self
      start = end
      end += 120
      (_x.frequenz, _x.time, _x.StartPose.position.x, _x.StartPose.position.y, _x.StartPose.position.z, _x.StartPose.orientation.x, _x.StartPose.orientation.y, _x.StartPose.orientation.z, _x.StartPose.orientation.w, _x.GoalPose.position.x, _x.GoalPose.position.y, _x.GoalPose.position.z, _x.GoalPose.orientation.x, _x.GoalPose.orientation.y, _x.GoalPose.orientation.z, _x.GoalPose.orientation.w,) = _get_struct_2f14d().unpack(str[start:end])
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
      length = len(self.velocityVector)
      buff.write(_struct_I.pack(length))
      pattern = '<%sf'%length
      buff.write(self.velocityVector.tostring())
      _x = self
      buff.write(_get_struct_2f14d().pack(_x.frequenz, _x.time, _x.StartPose.position.x, _x.StartPose.position.y, _x.StartPose.position.z, _x.StartPose.orientation.x, _x.StartPose.orientation.y, _x.StartPose.orientation.z, _x.StartPose.orientation.w, _x.GoalPose.position.x, _x.GoalPose.position.y, _x.GoalPose.position.z, _x.GoalPose.orientation.x, _x.GoalPose.orientation.y, _x.GoalPose.orientation.z, _x.GoalPose.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.StartPose is None:
        self.StartPose = geometry_msgs.msg.Pose()
      if self.GoalPose is None:
        self.GoalPose = geometry_msgs.msg.Pose()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sf'%length
      start = end
      end += struct.calcsize(pattern)
      self.velocityVector = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=length)
      _x = self
      start = end
      end += 120
      (_x.frequenz, _x.time, _x.StartPose.position.x, _x.StartPose.position.y, _x.StartPose.position.z, _x.StartPose.orientation.x, _x.StartPose.orientation.y, _x.StartPose.orientation.z, _x.StartPose.orientation.w, _x.GoalPose.position.x, _x.GoalPose.position.y, _x.GoalPose.position.z, _x.GoalPose.orientation.x, _x.GoalPose.orientation.y, _x.GoalPose.orientation.z, _x.GoalPose.orientation.w,) = _get_struct_2f14d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2f14d = None
def _get_struct_2f14d():
    global _struct_2f14d
    if _struct_2f14d is None:
        _struct_2f14d = struct.Struct("<2f14d")
    return _struct_2f14d