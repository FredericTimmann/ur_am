function [  ] = pub_designed_pos( )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
time=4.7;
freq=50;
dist=1.4646;
num_coef=15;
%coef=1.9355;
coef=1.25;

pubmsg=rosmessage('std_msgs/Float32');
pubmsg.Data=0;
pos_pub = rospublisher('/matlab_srv/designed_pos/y','std_msgs/Float32');
vel_pub = rospublisher('/matlab_srv/designed_vel/y','std_msgs/Float32');

pause(0.1);
send(pos_pub,pubmsg);
send(vel_pub,pubmsg);

bbspline=get_bbspline([num_coef  coef]);
q = fnint(bbspline);
size_V=time*freq;
pos_Val = fnval(q,linspace(0,1,size_V))*dist;
vel_Val = fnval(bbspline,linspace(0,1,size_V))*dist/time;

'ready to pub'
r = robotics.Rate(freq);
for i=1:size_V
    pubmsg.Data=0.732-pos_Val(i);
    send(pos_pub,pubmsg);
    pubmsg.Data=-vel_Val(i);
    send(vel_pub,pubmsg);

    waitfor(r);
end

