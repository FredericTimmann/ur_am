;; Auto-generated. Do not edit!


(when (boundp 'optimation_msgs::trajectory_optimation_service)
  (if (not (find-package "OPTIMATION_MSGS"))
    (make-package "OPTIMATION_MSGS"))
  (shadow 'trajectory_optimation_service (find-package "OPTIMATION_MSGS")))
(unless (find-package "OPTIMATION_MSGS::TRAJECTORY_OPTIMATION_SERVICE")
  (make-package "OPTIMATION_MSGS::TRAJECTORY_OPTIMATION_SERVICE"))
(unless (find-package "OPTIMATION_MSGS::TRAJECTORY_OPTIMATION_SERVICEREQUEST")
  (make-package "OPTIMATION_MSGS::TRAJECTORY_OPTIMATION_SERVICEREQUEST"))
(unless (find-package "OPTIMATION_MSGS::TRAJECTORY_OPTIMATION_SERVICERESPONSE")
  (make-package "OPTIMATION_MSGS::TRAJECTORY_OPTIMATION_SERVICERESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass optimation_msgs::trajectory_optimation_serviceRequest
  :super ros::object
  :slots (_startPose _goalPose _time ))

(defmethod optimation_msgs::trajectory_optimation_serviceRequest
  (:init
   (&key
    ((:startPose __startPose) (instance geometry_msgs::Pose :init))
    ((:goalPose __goalPose) (instance geometry_msgs::Pose :init))
    ((:time __time) (instance std_msgs::Float32 :init))
    )
   (send-super :init)
   (setq _startPose __startPose)
   (setq _goalPose __goalPose)
   (setq _time __time)
   self)
  (:startPose
   (&rest __startPose)
   (if (keywordp (car __startPose))
       (send* _startPose __startPose)
     (progn
       (if __startPose (setq _startPose (car __startPose)))
       _startPose)))
  (:goalPose
   (&rest __goalPose)
   (if (keywordp (car __goalPose))
       (send* _goalPose __goalPose)
     (progn
       (if __goalPose (setq _goalPose (car __goalPose)))
       _goalPose)))
  (:time
   (&rest __time)
   (if (keywordp (car __time))
       (send* _time __time)
     (progn
       (if __time (setq _time (car __time)))
       _time)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Pose _startPose
    (send _startPose :serialization-length)
    ;; geometry_msgs/Pose _goalPose
    (send _goalPose :serialization-length)
    ;; std_msgs/Float32 _time
    (send _time :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Pose _startPose
       (send _startPose :serialize s)
     ;; geometry_msgs/Pose _goalPose
       (send _goalPose :serialize s)
     ;; std_msgs/Float32 _time
       (send _time :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Pose _startPose
     (send _startPose :deserialize buf ptr-) (incf ptr- (send _startPose :serialization-length))
   ;; geometry_msgs/Pose _goalPose
     (send _goalPose :deserialize buf ptr-) (incf ptr- (send _goalPose :serialization-length))
   ;; std_msgs/Float32 _time
     (send _time :deserialize buf ptr-) (incf ptr- (send _time :serialization-length))
   ;;
   self)
  )

(defclass optimation_msgs::trajectory_optimation_serviceResponse
  :super ros::object
  :slots (_serverstate ))

(defmethod optimation_msgs::trajectory_optimation_serviceResponse
  (:init
   (&key
    ((:serverstate __serverstate) (instance std_msgs::String :init))
    )
   (send-super :init)
   (setq _serverstate __serverstate)
   self)
  (:serverstate
   (&rest __serverstate)
   (if (keywordp (car __serverstate))
       (send* _serverstate __serverstate)
     (progn
       (if __serverstate (setq _serverstate (car __serverstate)))
       _serverstate)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/String _serverstate
    (send _serverstate :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/String _serverstate
       (send _serverstate :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/String _serverstate
     (send _serverstate :deserialize buf ptr-) (incf ptr- (send _serverstate :serialization-length))
   ;;
   self)
  )

(defclass optimation_msgs::trajectory_optimation_service
  :super ros::object
  :slots ())

(setf (get optimation_msgs::trajectory_optimation_service :md5sum-) "a9d240ca40c09613e772aa0873f359d6")
(setf (get optimation_msgs::trajectory_optimation_service :datatype-) "optimation_msgs/trajectory_optimation_service")
(setf (get optimation_msgs::trajectory_optimation_service :request) optimation_msgs::trajectory_optimation_serviceRequest)
(setf (get optimation_msgs::trajectory_optimation_service :response) optimation_msgs::trajectory_optimation_serviceResponse)

(defmethod optimation_msgs::trajectory_optimation_serviceRequest
  (:response () (instance optimation_msgs::trajectory_optimation_serviceResponse :init)))

(setf (get optimation_msgs::trajectory_optimation_serviceRequest :md5sum-) "a9d240ca40c09613e772aa0873f359d6")
(setf (get optimation_msgs::trajectory_optimation_serviceRequest :datatype-) "optimation_msgs/trajectory_optimation_serviceRequest")
(setf (get optimation_msgs::trajectory_optimation_serviceRequest :definition-)
      "geometry_msgs/Pose startPose
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
---
std_msgs/String serverstate


================================================================================
MSG: std_msgs/String
string data
")

(setf (get optimation_msgs::trajectory_optimation_serviceResponse :md5sum-) "a9d240ca40c09613e772aa0873f359d6")
(setf (get optimation_msgs::trajectory_optimation_serviceResponse :datatype-) "optimation_msgs/trajectory_optimation_serviceResponse")
(setf (get optimation_msgs::trajectory_optimation_serviceResponse :definition-)
      "geometry_msgs/Pose startPose
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
---
std_msgs/String serverstate


================================================================================
MSG: std_msgs/String
string data
")



(provide :optimation_msgs/trajectory_optimation_service "a9d240ca40c09613e772aa0873f359d6")


