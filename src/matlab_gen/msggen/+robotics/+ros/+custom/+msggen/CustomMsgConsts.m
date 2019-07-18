classdef CustomMsgConsts
    %CustomMsgConsts This class stores all message types
    %   The message types are constant properties, which in turn resolve
    %   to the strings of the actual types.
    
    %   Copyright 2014-2019 The MathWorks, Inc.
    
    properties (Constant)
        custom_msgs_AddInts = 'custom_msgs/AddInts'
        custom_msgs_AddIntsRequest = 'custom_msgs/AddIntsRequest'
        custom_msgs_AddIntsResponse = 'custom_msgs/AddIntsResponse'
        custom_msgs_mytest = 'custom_msgs/mytest'
        optimation_msgs_AddTwoInts = 'optimation_msgs/AddTwoInts'
        optimation_msgs_AddTwoIntsRequest = 'optimation_msgs/AddTwoIntsRequest'
        optimation_msgs_AddTwoIntsResponse = 'optimation_msgs/AddTwoIntsResponse'
        optimation_msgs_TrajectoryExecutionAction = 'optimation_msgs/TrajectoryExecutionAction'
        optimation_msgs_TrajectoryExecutionActionFeedback = 'optimation_msgs/TrajectoryExecutionActionFeedback'
        optimation_msgs_TrajectoryExecutionActionGoal = 'optimation_msgs/TrajectoryExecutionActionGoal'
        optimation_msgs_TrajectoryExecutionActionResult = 'optimation_msgs/TrajectoryExecutionActionResult'
        optimation_msgs_TrajectoryExecutionFeedback = 'optimation_msgs/TrajectoryExecutionFeedback'
        optimation_msgs_TrajectoryExecutionGoal = 'optimation_msgs/TrajectoryExecutionGoal'
        optimation_msgs_TrajectoryExecutionResult = 'optimation_msgs/TrajectoryExecutionResult'
        optimation_msgs_trajectory_optimation_msg = 'optimation_msgs/trajectory_optimation_msg'
        optimation_msgs_trajectory_optimation_service = 'optimation_msgs/trajectory_optimation_service'
        optimation_msgs_trajectory_optimation_serviceRequest = 'optimation_msgs/trajectory_optimation_serviceRequest'
        optimation_msgs_trajectory_optimation_serviceResponse = 'optimation_msgs/trajectory_optimation_serviceResponse'
    end
    
    methods (Static, Hidden)
        function messageList = getMessageList
            %getMessageList Generate a cell array with all message types.
            %   The list will be sorted alphabetically.
            
            persistent msgList
            if isempty(msgList)
                msgList = cell(15, 1);
                msgList{1} = 'custom_msgs/AddIntsRequest';
                msgList{2} = 'custom_msgs/AddIntsResponse';
                msgList{3} = 'custom_msgs/mytest';
                msgList{4} = 'optimation_msgs/AddTwoIntsRequest';
                msgList{5} = 'optimation_msgs/AddTwoIntsResponse';
                msgList{6} = 'optimation_msgs/TrajectoryExecutionAction';
                msgList{7} = 'optimation_msgs/TrajectoryExecutionActionFeedback';
                msgList{8} = 'optimation_msgs/TrajectoryExecutionActionGoal';
                msgList{9} = 'optimation_msgs/TrajectoryExecutionActionResult';
                msgList{10} = 'optimation_msgs/TrajectoryExecutionFeedback';
                msgList{11} = 'optimation_msgs/TrajectoryExecutionGoal';
                msgList{12} = 'optimation_msgs/TrajectoryExecutionResult';
                msgList{13} = 'optimation_msgs/trajectory_optimation_msg';
                msgList{14} = 'optimation_msgs/trajectory_optimation_serviceRequest';
                msgList{15} = 'optimation_msgs/trajectory_optimation_serviceResponse';
            end
            
            messageList = msgList;
        end
        
        function serviceList = getServiceList
            %getServiceList Generate a cell array with all service types.
            %   The list will be sorted alphabetically.
            
            persistent svcList
            if isempty(svcList)
                svcList = cell(3, 1);
                svcList{1} = 'custom_msgs/AddInts';
                svcList{2} = 'optimation_msgs/AddTwoInts';
                svcList{3} = 'optimation_msgs/trajectory_optimation_service';
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            serviceList = svcList;
        end
        
        function actionList = getActionList
            %getActionList Generate a cell array with all action types.
            %   The list will be sorted alphabetically.
            
            persistent actList
            if isempty(actList)
                actList = cell(1, 1);
                actList{1} = 'optimation_msgs/TrajectoryExecution';
            end
            
            % The message list was already sorted, so don't need to sort
            % again.
            actionList = actList;
        end
    end
end
