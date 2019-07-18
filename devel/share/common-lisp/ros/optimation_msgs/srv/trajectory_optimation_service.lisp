; Auto-generated. Do not edit!


(cl:in-package optimation_msgs-srv)


;//! \htmlinclude trajectory_optimation_service-request.msg.html

(cl:defclass <trajectory_optimation_service-request> (roslisp-msg-protocol:ros-message)
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

(cl:defclass trajectory_optimation_service-request (<trajectory_optimation_service-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <trajectory_optimation_service-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'trajectory_optimation_service-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name optimation_msgs-srv:<trajectory_optimation_service-request> is deprecated: use optimation_msgs-srv:trajectory_optimation_service-request instead.")))

(cl:ensure-generic-function 'startPose-val :lambda-list '(m))
(cl:defmethod startPose-val ((m <trajectory_optimation_service-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-srv:startPose-val is deprecated.  Use optimation_msgs-srv:startPose instead.")
  (startPose m))

(cl:ensure-generic-function 'goalPose-val :lambda-list '(m))
(cl:defmethod goalPose-val ((m <trajectory_optimation_service-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-srv:goalPose-val is deprecated.  Use optimation_msgs-srv:goalPose instead.")
  (goalPose m))

(cl:ensure-generic-function 'time-val :lambda-list '(m))
(cl:defmethod time-val ((m <trajectory_optimation_service-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-srv:time-val is deprecated.  Use optimation_msgs-srv:time instead.")
  (time m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <trajectory_optimation_service-request>) ostream)
  "Serializes a message object of type '<trajectory_optimation_service-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'startPose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goalPose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'time) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <trajectory_optimation_service-request>) istream)
  "Deserializes a message object of type '<trajectory_optimation_service-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'startPose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goalPose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'time) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<trajectory_optimation_service-request>)))
  "Returns string type for a service object of type '<trajectory_optimation_service-request>"
  "optimation_msgs/trajectory_optimation_serviceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'trajectory_optimation_service-request)))
  "Returns string type for a service object of type 'trajectory_optimation_service-request"
  "optimation_msgs/trajectory_optimation_serviceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<trajectory_optimation_service-request>)))
  "Returns md5sum for a message object of type '<trajectory_optimation_service-request>"
  "a9d240ca40c09613e772aa0873f359d6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'trajectory_optimation_service-request)))
  "Returns md5sum for a message object of type 'trajectory_optimation_service-request"
  "a9d240ca40c09613e772aa0873f359d6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<trajectory_optimation_service-request>)))
  "Returns full string definition for message of type '<trajectory_optimation_service-request>"
  (cl:format cl:nil "geometry_msgs/Pose startPose~%geometry_msgs/Pose goalPose~%std_msgs/Float32 time~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'trajectory_optimation_service-request)))
  "Returns full string definition for message of type 'trajectory_optimation_service-request"
  (cl:format cl:nil "geometry_msgs/Pose startPose~%geometry_msgs/Pose goalPose~%std_msgs/Float32 time~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: std_msgs/Float32~%float32 data~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <trajectory_optimation_service-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'startPose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goalPose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'time))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <trajectory_optimation_service-request>))
  "Converts a ROS message object to a list"
  (cl:list 'trajectory_optimation_service-request
    (cl:cons ':startPose (startPose msg))
    (cl:cons ':goalPose (goalPose msg))
    (cl:cons ':time (time msg))
))
;//! \htmlinclude trajectory_optimation_service-response.msg.html

(cl:defclass <trajectory_optimation_service-response> (roslisp-msg-protocol:ros-message)
  ((serverstate
    :reader serverstate
    :initarg :serverstate
    :type std_msgs-msg:String
    :initform (cl:make-instance 'std_msgs-msg:String)))
)

(cl:defclass trajectory_optimation_service-response (<trajectory_optimation_service-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <trajectory_optimation_service-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'trajectory_optimation_service-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name optimation_msgs-srv:<trajectory_optimation_service-response> is deprecated: use optimation_msgs-srv:trajectory_optimation_service-response instead.")))

(cl:ensure-generic-function 'serverstate-val :lambda-list '(m))
(cl:defmethod serverstate-val ((m <trajectory_optimation_service-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader optimation_msgs-srv:serverstate-val is deprecated.  Use optimation_msgs-srv:serverstate instead.")
  (serverstate m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <trajectory_optimation_service-response>) ostream)
  "Serializes a message object of type '<trajectory_optimation_service-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'serverstate) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <trajectory_optimation_service-response>) istream)
  "Deserializes a message object of type '<trajectory_optimation_service-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'serverstate) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<trajectory_optimation_service-response>)))
  "Returns string type for a service object of type '<trajectory_optimation_service-response>"
  "optimation_msgs/trajectory_optimation_serviceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'trajectory_optimation_service-response)))
  "Returns string type for a service object of type 'trajectory_optimation_service-response"
  "optimation_msgs/trajectory_optimation_serviceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<trajectory_optimation_service-response>)))
  "Returns md5sum for a message object of type '<trajectory_optimation_service-response>"
  "a9d240ca40c09613e772aa0873f359d6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'trajectory_optimation_service-response)))
  "Returns md5sum for a message object of type 'trajectory_optimation_service-response"
  "a9d240ca40c09613e772aa0873f359d6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<trajectory_optimation_service-response>)))
  "Returns full string definition for message of type '<trajectory_optimation_service-response>"
  (cl:format cl:nil "std_msgs/String serverstate~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'trajectory_optimation_service-response)))
  "Returns full string definition for message of type 'trajectory_optimation_service-response"
  (cl:format cl:nil "std_msgs/String serverstate~%~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <trajectory_optimation_service-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'serverstate))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <trajectory_optimation_service-response>))
  "Converts a ROS message object to a list"
  (cl:list 'trajectory_optimation_service-response
    (cl:cons ':serverstate (serverstate msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'trajectory_optimation_service)))
  'trajectory_optimation_service-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'trajectory_optimation_service)))
  'trajectory_optimation_service-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'trajectory_optimation_service)))
  "Returns string type for a service object of type '<trajectory_optimation_service>"
  "optimation_msgs/trajectory_optimation_service")