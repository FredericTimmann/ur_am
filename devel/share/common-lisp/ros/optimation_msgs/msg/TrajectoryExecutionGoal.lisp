; Auto-generated. Do not edit!


(cl:in-package optimation_msgs-msg)


;//! \htmlinclude TrajectoryExecutionGoal.msg.html

(cl:defclass <TrajectoryExecutionGoal> (roslisp-msg-protocol:ros-message)
  ((velocityVector
    :reader velocityVector
    :initarg :velocityVector
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (frequenz
    :reader frequenz
    :initarg :frequenz
    :type cl:float
    :initform 0.0)
   (time
    :reader time
    :initarg :time
    :type cl:float
    :initform 0.0)
   (StartPose
    :reader StartPose
    :initarg :StartPose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (GoalPose
    :reader GoalPose
    :initarg :GoalPose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass TrajectoryExecutionGoal (<TrajectoryExecutionGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TrajectoryExecutionGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TrajectoryExecutionGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name optimation_msgs-msg:<TrajectoryExecutionGoal> is deprecated: use optimation_msgs-msg:TrajectoryExecutionGoal instead.")))

(cl:ensure-generic-function 'velocityVector-val :lambda-list '(m))
(cl:defmethod velocityVector-val ((m <TrajectoryExecutionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:velocityVector-val is deprecated.  Use optimation_msgs-msg:velocityVector instead.")
  (velocityVector m))

(cl:ensure-generic-function 'frequenz-val :lambda-list '(m))
(cl:defmethod frequenz-val ((m <TrajectoryExecutionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:frequenz-val is deprecated.  Use optimation_msgs-msg:frequenz instead.")
  (frequenz m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <TrajectoryExecutionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:time-val is deprecated.  Use optimation_msgs-msg:time instead.")
  (time m))

(cl:ensure-generic-function 'StartPose-val :lambda-list '(m))
(cl:defmethod StartPose-val ((m <TrajectoryExecutionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:StartPose-val is deprecated.  Use optimation_msgs-msg:StartPose instead.")
  (StartPose m))

(cl:ensure-generic-function 'GoalPose-val :lambda-list '(m))
(cl:defmethod GoalPose-val ((m <TrajectoryExecutionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-msg:GoalPose-val is deprecated.  Use optimation_msgs-msg:GoalPose instead.")
  (GoalPose m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TrajectoryExecutionGoal>) ostream)
  "Serializes a message object of type '<TrajectoryExecutionGoal>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'velocityVector))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'velocityVector))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'frequenz))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'StartPose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'GoalPose) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TrajectoryExecutionGoal>) istream)
  "Deserializes a message object of type '<TrajectoryExecutionGoal>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'velocityVector) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'velocityVector)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'frequenz) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'time) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'StartPose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'GoalPose) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TrajectoryExecutionGoal>)))
  "Returns string type for a message object of type '<TrajectoryExecutionGoal>"
  "optimation_msgs/TrajectoryExecutionGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TrajectoryExecutionGoal)))
  "Returns string type for a message object of type 'TrajectoryExecutionGoal"
  "optimation_msgs/TrajectoryExecutionGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TrajectoryExecutionGoal>)))
  "Returns md5sum for a message object of type '<TrajectoryExecutionGoal>"
  "ea451a2ad70ed9c78ee392b0e39f6b47")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TrajectoryExecutionGoal)))
  "Returns md5sum for a message object of type 'TrajectoryExecutionGoal"
  "ea451a2ad70ed9c78ee392b0e39f6b47")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TrajectoryExecutionGoal>)))
  "Returns full string definition for message of type '<TrajectoryExecutionGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32[] velocityVector~%float32 frequenz~%float32 time~%geometry_msgs/Pose StartPose~%geometry_msgs/Pose GoalPose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TrajectoryExecutionGoal)))
  "Returns full string definition for message of type 'TrajectoryExecutionGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%# Define the goal~%float32[] velocityVector~%float32 frequenz~%float32 time~%geometry_msgs/Pose StartPose~%geometry_msgs/Pose GoalPose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TrajectoryExecutionGoal>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'velocityVector) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'StartPose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'GoalPose))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TrajectoryExecutionGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'TrajectoryExecutionGoal
    (cl:cons ':velocityVector (velocityVector msg))
    (cl:cons ':frequenz (frequenz msg))
    (cl:cons ':time (time msg))
    (cl:cons ':StartPose (StartPose msg))
    (cl:cons ':GoalPose (GoalPose msg))
))
