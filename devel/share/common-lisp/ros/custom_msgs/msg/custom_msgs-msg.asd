
(cl:in-package :asdf)

(defsystem "custom_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "mytest" :depends-on ("_package_mytest"))
    (:file "_package_mytest" :depends-on ("_package"))
  ))