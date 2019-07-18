close all;
clear all;
global val;
%rosinit('http://frederic:11311/')

%opt_server = rossvcserver('/opt_srv', 'custom_msgs/AddInts', @optcallback)
optmation_sub = rossubscriber('/matlab_srv/trj_opt','std_msgs/Float32',@optcallback);

optmation_sub.NewMessageFcn = {@optcallback};
function optcallback(src,msg)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
global val
val=msg.Data

 spline_opti(msg.Data)
%reqMsg.StartPose
'hello im am a callback'
%pause(10)
end