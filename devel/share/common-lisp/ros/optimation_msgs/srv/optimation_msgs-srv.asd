
(cl:in-package :asdf)

(defsystem "optimation_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "AddTwoInts" :depends-on ("_package_AddTwoInts"))
    (:file "_package_AddTwoInts" :depends-on ("_package"))
    (:file "trajectory_optimation_service" :depends-on ("_package_trajectory_optimation_service"))
    (:file "_package_trajectory_optimation_service" :depends-on ("_package"))
  ))