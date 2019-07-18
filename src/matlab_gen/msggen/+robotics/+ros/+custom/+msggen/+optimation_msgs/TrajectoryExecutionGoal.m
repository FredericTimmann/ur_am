classdef TrajectoryExecutionGoal < robotics.ros.Message
    %TrajectoryExecutionGoal MATLAB implementation of optimation_msgs/TrajectoryExecutionGoal
    %   This class was automatically generated by
    %   robotics.ros.msg.internal.gen.MessageClassGenerator.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    %#ok<*INUSD>
    
    properties (Constant)
        MessageType = 'optimation_msgs/TrajectoryExecutionGoal' % The ROS message type
    end
    
    properties (Constant, Hidden)
        MD5Checksum = 'ea451a2ad70ed9c78ee392b0e39f6b47' % The MD5 Checksum of the message definition
    end
    
    properties (Access = protected)
        JavaMessage % The Java message object
    end
    
    properties (Constant, Access = protected)
        GeometryMsgsPoseClass = robotics.ros.msg.internal.MessageFactory.getClassForType('geometry_msgs/Pose') % Dispatch to MATLAB class for message type geometry_msgs/Pose
    end
    
    properties (Dependent)
        Frequenz
        Time
        StartPose
        GoalPose
        VelocityVector
    end
    
    properties (Access = protected)
        Cache = struct('StartPose', [], 'GoalPose', []) % The cache for fast data access
    end
    
    properties (Constant, Hidden)
        PropertyList = {'Frequenz', 'GoalPose', 'StartPose', 'Time', 'VelocityVector'} % List of non-constant message properties
        ROSPropertyList = {'frequenz', 'GoalPose', 'StartPose', 'time', 'velocityVector'} % List of non-constant ROS message properties
    end
    
    methods
        function obj = TrajectoryExecutionGoal(msg)
            %TrajectoryExecutionGoal Construct the message object TrajectoryExecutionGoal
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
        
        function frequenz = get.Frequenz(obj)
            %get.Frequenz Get the value for property Frequenz
            frequenz = single(obj.JavaMessage.getFrequenz);
        end
        
        function set.Frequenz(obj, frequenz)
            %set.Frequenz Set the value for property Frequenz
            validateattributes(frequenz, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryExecutionGoal', 'Frequenz');
            
            obj.JavaMessage.setFrequenz(frequenz);
        end
        
        function time = get.Time(obj)
            %get.Time Get the value for property Time
            time = single(obj.JavaMessage.getTime);
        end
        
        function set.Time(obj, time)
            %set.Time Set the value for property Time
            validateattributes(time, {'numeric'}, {'nonempty', 'scalar'}, 'TrajectoryExecutionGoal', 'Time');
            
            obj.JavaMessage.setTime(time);
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
            validateattributes(startpose, {obj.GeometryMsgsPoseClass}, {'nonempty', 'scalar'}, 'TrajectoryExecutionGoal', 'StartPose');
            
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
            validateattributes(goalpose, {obj.GeometryMsgsPoseClass}, {'nonempty', 'scalar'}, 'TrajectoryExecutionGoal', 'GoalPose');
            
            obj.JavaMessage.setGoalPose(goalpose.getJavaObject);
            
            % Update cache if necessary
            if ~isempty(obj.Cache.GoalPose)
                obj.Cache.GoalPose.setJavaObject(goalpose.getJavaObject);
            end
        end
        
        function velocityvector = get.VelocityVector(obj)
            %get.VelocityVector Get the value for property VelocityVector
            javaArray = obj.JavaMessage.getVelocityVector;
            array = obj.readJavaArray(javaArray, 'single');
            velocityvector = single(array);
        end
        
        function set.VelocityVector(obj, velocityvector)
            %set.VelocityVector Set the value for property VelocityVector
            if ~isvector(velocityvector) && isempty(velocityvector)
                % Allow empty [] input
                velocityvector = single.empty(0,1);
            end
            
            validateattributes(velocityvector, {'numeric'}, {'vector'}, 'TrajectoryExecutionGoal', 'VelocityVector');
            
            javaArray = obj.JavaMessage.getVelocityVector;
            array = obj.writeJavaArray(velocityvector, javaArray, 'single');
            obj.JavaMessage.setVelocityVector(array);
        end
    end
    
    methods (Access = protected)
        function resetCache(obj)
            %resetCache Resets any cached properties
            obj.Cache.StartPose = [];
            obj.Cache.GoalPose = [];
        end
        
        function cpObj = copyElement(obj)
            %copyElement Implements deep copy behavior for message
            
            % Call default copy method for shallow copy
            cpObj = copyElement@robotics.ros.Message(obj);
            
            % Clear any existing cached properties
            cpObj.resetCache;
            
            % Create a new Java message object
            cpObj.JavaMessage = obj.createNewJavaMessage;
            
            % Iterate over all primitive properties
            cpObj.Frequenz = obj.Frequenz;
            cpObj.Time = obj.Time;
            cpObj.VelocityVector = obj.VelocityVector;
            
            % Recursively copy compound properties
            cpObj.StartPose = copy(obj.StartPose);
            cpObj.GoalPose = copy(obj.GoalPose);
        end
        
        function reload(obj, strObj)
            %reload Called by loadobj to assign properties
            obj.Frequenz = strObj.Frequenz;
            obj.Time = strObj.Time;
            obj.VelocityVector = strObj.VelocityVector;
            obj.StartPose = feval([obj.GeometryMsgsPoseClass '.loadobj'], strObj.StartPose);
            obj.GoalPose = feval([obj.GeometryMsgsPoseClass '.loadobj'], strObj.GoalPose);
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
            
            strObj.Frequenz = obj.Frequenz;
            strObj.Time = obj.Time;
            strObj.VelocityVector = obj.VelocityVector;
            strObj.StartPose = saveobj(obj.StartPose);
            strObj.GoalPose = saveobj(obj.GoalPose);
        end
    end
    
    methods (Static, Access = {?matlab.unittest.TestCase, ?robotics.ros.Message})
        function obj = loadobj(strObj)
            %loadobj Implements loading of message from MAT file
            
            % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = robotics.ros.custom.msggen.optimation_msgs.TrajectoryExecutionGoal.empty(0,1);
                return
            end
            
            % Create an empty message object
            obj = robotics.ros.custom.msggen.optimation_msgs.TrajectoryExecutionGoal;
            obj.reload(strObj);
        end
    end
end
