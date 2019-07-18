close all;
clear all;
global srv_state;
srv_state='starting..';
try
    rosinit('http://frederic:11311/');
    pause(1);
catch
    %pass;
end

optmation_server = rossvcserver('/matlab_srv/trj_opt_server','optimation_msgs/trajectory_optimation_service',@opt_srv_callback);
%optmation_server.NewMessageFcn = @opt_srv_callback;
tr_opt_ex_sub = rossubscriber('/matlab_srv/trj_opt_executiv', 'optimation_msgs/trajectory_optimation_msg',@execute_sub_callback);
tr_opt_ex_sub.NewMessageFcn = {@execute_sub_callback};
desing_pos_sub = rossubscriber('/matlab_srv/show_pos', 'std_msgs/Empty',@show_pos_callback);
desing_pos_sub.NewMessageFcn = {@show_pos_callback};
pos_pub = rospublisher('/matlab_srv/designed_pos/y','std_msgs/Float32');
%vel_pub = rospublisher('/matlab_srv/designed_vel/y','std_msgs/Float32');
pause(0.1);
posmsg=rosmessage('std_msgs/Float32');
send(pos_pub,posmsg);
%send(vel_pub,posmsg);

srv_state='ready.....';
function responce=opt_srv_callback(src,reqMsg,defaultRespMsg)
%function publish data to start optimation if Matlabscript for optimation
%is not running
tr_opt_ex_pub = rospublisher('/matlab_srv/trj_opt_executiv','optimation_msgs/trajectory_optimation_msg');
pause(0.1);
global srv_state
if srv_state=='ready.....'
    %pub: reqMsg
    'state ready! starting optimation'

    pubMsg=rosmessage('optimation_msgs/trajectory_optimation_msg');
    pubMsg.StartPose=reqMsg.StartPose;
    pubMsg.GoalPose=reqMsg.GoalPose;
    pubMsg.Time=reqMsg.Time;

    %msg.Data=reqMsg.Data;
    send(tr_opt_ex_pub,pubMsg);
    srv_state='running...';
else 
    srv_state='error.....';
end
responce.Veloctiy=[1445 245.4 234];
%responce.Data=srv_state;
end
function execute_sub_callback(src,msg)
'calling function'
spline_opti_singleParam(msg)
'function called'
end
function show_pos_callback(src,data)
pub_designed_pos();
end
