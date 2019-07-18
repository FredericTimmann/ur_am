; Auto-generated. Do not edit!


(cl:in-package optimation_msgs-msg)


;//! \htmlinclude trajectory_optimation_msg.msg.html

(cl:defclass <trajectory_optimation_msg> (roslisp-msg-protocol:ros-message)
  ((startPose
    :reader startPose
    :initarg :startPose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (goalPose
    :reader goalPose
    :initarg :goalPose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (time
    :reader time
    :initarg :time
    :type std_msgs-msg:Float32
    :initform (cl:make-instance 'std_msgs-msg:Float32)))
)

(cl:defclass trajectory_optimation_msg (<trajectory_optimation_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <trajectory_optimation_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'trajectory_optimation_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name optimation_msgs-msg:<trajectory_optimation_msg> is deprecated: use optimation_msgs-msg:trajectory_optimation_msg instead.")))

(cl:ensure-generic-function 'startPose-val :lambda-list '(m))
(cl:defmethod startPose-val ((m <trajectory_optimation_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:startPose-val is deprecated.  Use optimation_msgs-msg:startPose instead.")
  (startPose m))

(cl:ensure-generic-function 'goalPose-val :lambda-list '(m))
(cl:defmethod goalPose-val ((m <trajectory_optimation_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:goalPose-val is deprecated.  Use optimation_msgs-msg:goalPose instead.")
  (goalPose m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <trajectory_optimation_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:time-val is deprecated.  Use optimation_msgs-msg:time instead.")
  (time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <trajectory_optimation_msg>) ostream)
  "Serializes a message object of type '<trajectory_optimation_msg>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'startPose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalPose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'time) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <trajectory_optimation_msg>) istream)
  "Deserializes a message object of type '<trajectory_optimation_msg>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'startPose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalPose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'time) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<trajectory_optimation_msg>)))
  "Returns string type for a message object of type '<trajectory_optimation_msg>"
  "optimation_msgs/trajectory_optimation_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'trajectory_optimation_msg)))
  "Returns string type for a message object of type 'trajectory_optimation_msg"
  "optimation_msgs/trajectory_optimation_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<trajectory_optimation_msg>)))
  "Returns md5sum for a message object of type '<trajectory_optimation_msg>"
  "85f20d48235c676a951608690ba6db9d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'trajectory_optimation_msg)))
  "Returns md5sum for a message object of type 'trajectory_optimation_msg"
  "85f20d48235c676a951608690ba6db9d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<trajectory_optimation_msg>)))
  "Returns full string definition for message of type '<trajectory_optimation_msg>"
  (cl:format cl:nil "geometry_msgs/Pose startPose~%geometry_msgs/Pose goalPose~%std_msgs/Float32 time~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'trajectory_optimation_msg)))
  "Returns full string definition for message of type 'trajectory_optimation_msg"
  (cl:format cl:nil "geometry_msgs/Pose startPose~%geometry_msgs/Pose goalPose~%std_msgs/Float32 time~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <trajectory_optimation_msg>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'startPose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalPose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'time))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <trajectory_optimation_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'trajectory_optimation_msg
    (cl:cons ':startPose (startPose msg))
    (cl:cons ':goalPose (goalPose msg))
    (cl:cons ':time (time msg))
))
