// Auto-generated. Do not edit!

// (in-package optimation_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class trajectory_optimation_serviceRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.startPose = null;
      this.goalPose = null;
      this.time = null;
    }
    else {
      if (initObj.hasOwnProperty('startPose')) {
        this.startPose = initObj.startPose
      }
      else {
        this.startPose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('goalPose')) {
        this.goalPose = initObj.goalPose
      }
      else {
        this.goalPose = new geometry_msgs.msg.Pose();
      }
      if (initObj.hasOwnProperty('time')) {
        this.time = initObj.time
      }
      else {
        this.time = new std_msgs.msg.Float32();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type trajectory_optimation_serviceRequest
    // Serialize message field [startPose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.startPose, buffer, bufferOffset);
    // Serialize message field [goalPose]
    bufferOffset = geometry_msgs.msg.Pose.serialize(obj.goalPose, buffer, bufferOffset);
    // Serialize message field [time]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.time, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type trajectory_optimation_serviceRequest
    let len;
    let data = new trajectory_optimation_serviceRequest(null);
    // Deserialize message field [startPose]
    data.startPose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [goalPose]
    data.goalPose = geometry_msgs.msg.Pose.deserialize(buffer, bufferOffset);
    // Deserialize message field [time]
    data.time = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 116;
  }

  static datatype() {
    // Returns string type for a service object
    return 'optimation_msgs/trajectory_optimation_serviceRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '85f20d48235c676a951608690ba6db9d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Pose startPose
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
    float32 data
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new trajectory_optimation_serviceRequest(null);
    if (msg.startPose !== undefined) {
      resolved.startPose = geometry_msgs.msg.Pose.Resolve(msg.startPose)
    }
    else {
      resolved.startPose = new geometry_msgs.msg.Pose()
    }

    if (msg.goalPose !== undefined) {
      resolved.goalPose = geometry_msgs.msg.Pose.Resolve(msg.goalPose)
    }
    else {
      resolved.goalPose = new geometry_msgs.msg.Pose()
    }

    if (msg.time !== undefined) {
      resolved.time = std_msgs.msg.Float32.Resolve(msg.time)
    }
    else {
      resolved.time = new std_msgs.msg.Float32()
    }

    return resolved;
    }
};

class trajectory_optimation_serviceResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.serverstate = null;
    }
    else {
      if (initObj.hasOwnProperty('serverstate')) {
        this.serverstate = initObj.serverstate
      }
      else {
        this.serverstate = new std_msgs.msg.String();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type trajectory_optimation_serviceResponse
    // Serialize message field [serverstate]
    bufferOffset = std_msgs.msg.String.serialize(obj.serverstate, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type trajectory_optimation_serviceResponse
    let len;
    let data = new trajectory_optimation_serviceResponse(null);
    // Deserialize message field [serverstate]
    data.serverstate = std_msgs.msg.String.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.String.getMessageSize(object.serverstate);
    return length;
  }

  static datatype() {
    // Returns string type for a service object
    return 'optimation_msgs/trajectory_optimation_serviceResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4a016c0e523ccb8d38a68660d0e1664d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/String serverstate
    
    
    ================================================================================
    MSG: std_msgs/String
    string data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new trajectory_optimation_serviceResponse(null);
    if (msg.serverstate !== undefined) {
      resolved.serverstate = std_msgs.msg.String.Resolve(msg.serverstate)
    }
    else {
      resolved.serverstate = new std_msgs.msg.String()
    }

    return resolved;
    }
};

module.exports = {
  Request: trajectory_optimation_serviceRequest,
  Response: trajectory_optimation_serviceResponse,
  md5sum() { return 'a9d240ca40c09613e772aa0873f359d6'; },
  datatype() { return 'optimation_msgs/trajectory_optimation_service'; }
};
