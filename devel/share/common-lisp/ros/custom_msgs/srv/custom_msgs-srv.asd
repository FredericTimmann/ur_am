
(cl:in-package :asdf)

(defsystem "custom_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "AddInts" :depends-on ("_package_AddInts"))
    (:file "_package_AddInts" :depends-on ("_package"))
  ))