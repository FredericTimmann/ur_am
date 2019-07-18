
(cl:in-package :asdf)

(defsystem "optimation_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :actionlib_msgs-msg
               :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "TrajectoryExecutionAction" :depends-on ("_package_TrajectoryExecutionAction"))
    (:file "_package_TrajectoryExecutionAction" :depends-on ("_package"))
    (:file "TrajectoryExecutionActionFeedback" :depends-on ("_package_TrajectoryExecutionActionFeedback"))
    (:file "_package_TrajectoryExecutionActionFeedback" :depends-on ("_package"))
    (:file "TrajectoryExecutionActionGoal" :depends-on ("_package_TrajectoryExecutionActionGoal"))
    (:file "_package_TrajectoryExecutionActionGoal" :depends-on ("_package"))
    (:file "TrajectoryExecutionActionResult" :depends-on ("_package_TrajectoryExecutionActionResult"))
    (:file "_package_TrajectoryExecutionActionResult" :depends-on ("_package"))
    (:file "TrajectoryExecutionFeedback" :depends-on ("_package_TrajectoryExecutionFeedback"))
    (:file "_package_TrajectoryExecutionFeedback" :depends-on ("_package"))
    (:file "TrajectoryExecutionGoal" :depends-on ("_package_TrajectoryExecutionGoal"))
    (:file "_package_TrajectoryExecutionGoal" :depends-on ("_package"))
    (:file "TrajectoryExecutionResult" :depends-on ("_package_TrajectoryExecutionResult"))
    (:file "_package_TrajectoryExecutionResult" :depends-on ("_package"))
    (:file "trajectory_optimation_msg" :depends-on ("_package_trajectory_optimation_msg"))
    (:file "_package_trajectory_optimation_msg" :depends-on ("_package"))
  ))