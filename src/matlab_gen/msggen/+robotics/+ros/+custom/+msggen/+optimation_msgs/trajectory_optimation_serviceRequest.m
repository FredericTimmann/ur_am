classdef trajectory_optimation_serviceRequest < robotics.ros.Message
    %trajectory_optimation_serviceRequest MATLAB implementation of optimation_msgs/trajectory_optimation_serviceRequest
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'optimation_msgs/trajectory_optimation_serviceRequest' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = '85f20d48235c676a951608690ba6db9d' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant, Access = protected)
        GeometryMsgsPoseClass = robotics.ros.msg.internal.MessageFactory.getClassForType('geometry_msgs/Pose') % Dispatch to MATLAB class for message type geometry_msgs/Pose
        StdMsgsFloat32Class = robotics.ros.msg.internal.MessageFactory.getClassForType('std_msgs/Float32') % Dispatch to MATLAB class for message type std_msgs/Float32
    end
    
    properties (Dependent)
        StartPose
        GoalPose
        Time
    end
    
    properties (Access = protected)
        Cache = struct('StartPose', [], 'GoalPose', [], 'Time', []) % The cache for fast data access
    end
    
    properties (Constant, Hidden)
        PropertyList = {'GoalPose', 'StartPose', 'Time'} % List of non-constant message properties
        ROSPropertyList = {'goalPose', 'startPose', 'time'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = trajectory_optimation_serviceRequest(msg)
            %trajectory_optimation_serviceRequest Construct the message object trajectory_optimation_serviceRequest
            import com.mathworks.toolbox.robotics.ros.message.MessageInfo;
            
            % Support default constructor
            if nargin == 0
                obj.JavaMessage = obj.createNewJavaMessage;
                return;
            end
            
            % Construct appropriate empty array
            if isempty(msg)
                obj = obj.empty(0,1);
                return;
            end
            
            % Make scalar construction fast
            if isscalar(msg)
                % Check for correct input class
                if ~MessageInfo.compareTypes(msg(1), obj.MessageType)
                    error(message('robotics:ros:message:NoTypeMatch', obj.MessageType, ...
                        char(MessageInfo.getType(msg(1))) ));
                end
                obj.JavaMessage = msg(1);
                return;
            end
            
            % Check that this is a vector of scalar messages. Since this
            % is an object array, use arrayfun to verify.
            if ~all(arrayfun(@isscalar, msg))
                error(message('robotics:ros:message:MessageArraySizeError'));
            end
            
            % Check that all messages in the array have the correct type
            if ~all(arrayfun(@(x) MessageInfo.compareTypes(x, obj.MessageType), msg))
                error(message('robotics:ros:message:NoTypeMatchArray', obj.MessageType));
            end
            
            % Construct array of objects if necessary
            objType = class(obj);
            for i = 1:length(msg)
                obj(i,1) = feval(objType, msg(i)); %#ok<AGROW>
            end
        end
        
        function startpose = get.StartPose(obj)
            %get.StartPose Get the value for property StartPose
            if isempty(obj.Cache.StartPose)
                obj.Cache.StartPose = feval(obj.GeometryMsgsPoseClass, obj.JavaMessage.getStartPose);
            end
            startpose = obj.Cache.StartPose;
        end
        
        function set.StartPose(obj, startpose)
            %set.StartPose Set the value for property StartPose
            validateattributes(startpose, {obj.GeometryMsgsPoseClass}, {'nonempty', 'scalar'}, 'trajectory_optimation_serviceRequest', 'StartPose');
            
            obj.JavaMessage.setStartPose(startpose.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.StartPose)
                obj.Cache.StartPose.setJavaObject(startpose.getJavaObject);
            end
        end
        
        function goalpose = get.GoalPose(obj)
            %get.GoalPose Get the value for property GoalPose
            if isempty(obj.Cache.GoalPose)
                obj.Cache.GoalPose = feval(obj.GeometryMsgsPoseClass, obj.JavaMessage.getGoalPose);
            end
            goalpose = obj.Cache.GoalPose;
        end
        
        function set.GoalPose(obj, goalpose)
            %set.GoalPose Set the value for property GoalPose
            validateattributes(goalpose, {obj.GeometryMsgsPoseClass}, {'nonempty', 'scalar'}, 'trajectory_optimation_serviceRequest', 'GoalPose');
            
            obj.JavaMessage.setGoalPose(goalpose.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.GoalPose)
                obj.Cache.GoalPose.setJavaObject(goalpose.getJavaObject);
            end
        end
        
        function time = get.Time(obj)
            %get.Time Get the value for property Time
            if isempty(obj.Cache.Time)
                obj.Cache.Time = feval(obj.StdMsgsFloat32Class, obj.JavaMessage.getTime);
            end
            time = obj.Cache.Time;
        end
        
        function set.Time(obj, time)
            %set.Time Set the value for property Time
            validateattributes(time, {obj.StdMsgsFloat32Class}, {'nonempty', 'scalar'}, 'trajectory_optimation_serviceRequest', 'Time');
            
            obj.JavaMessage.setTime(time.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.Time)
                obj.Cache.Time.setJavaObject(time.getJavaObject);
            end
        end
    end
    
    methods (Access = protected)
        function resetCache(obj)
            %resetCache Resets any cached properties
            obj.Cache.StartPose = [];
            obj.Cache.GoalPose = [];
            obj.Cache.Time = [];
        end
        
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Clear any existing cached properties
            cpObj.resetCache;
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Recursively copy compound properties
            cpObj.StartPose = copy(obj.StartPose);
            cpObj.GoalPose = copy(obj.GoalPose);
            cpObj.Time = copy(obj.Time);
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.StartPose = feval([obj.GeometryMsgsPoseClass '.loadobj'], strObj.StartPose);
            obj.GoalPose = feval([obj.GeometryMsgsPoseClass '.loadobj'], strObj.GoalPose);
            obj.Time = feval([obj.StdMsgsFloat32Class '.loadobj'], strObj.Time);
        end
    end
    
    methods (Access = ?robotics.ros.Message)
        function strObj = saveobj(obj)
            %saveobj Implements saving of message to MAT file
            
            % Return an empty element if object array is empty
            if isempty(obj)
                strObj = struct.empty;
                return
            end
            
            strObj.StartPose = saveobj(obj.StartPose);
            strObj.GoalPose = saveobj(obj.GoalPose);
            strObj.Time = saveobj(obj.Time);
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.optimation_msgs.trajectory_optimation_serviceRequest.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.optimation_msgs.trajectory_optimation_serviceRequest;
            obj.reload(strObj);
        end
    end
end
