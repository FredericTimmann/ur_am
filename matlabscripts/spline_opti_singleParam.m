function [ ret_spline ] = spline_opti_singleParam( msg )
%% message mapping
%calcDistance 
distance=sqrt((msg.GoalPose.Position.X-msg.StartPose.Position.X)^2+(msg.GoalPose.Position.Y-msg.StartPose.Position.Y)^2+(msg.GoalPose.Position.Z-msg.StartPose.Position.Z)^2)
%% Optimation of Spline Parameters
%Optimation Parameters
lb=[2];
ub=[19];
A = [];
b = [];
Aeq = [];
beq = [];
NONLCON= @int_spline_cond;
x0=[2];
[client,goalMsg] = rosactionclient('/trajectory_execution');
E=zeros(1,19);
coef=E;
for i=15:19
[E(i),coef(i)]=objective_t_singleParam(15,msg,client,distance,goalMsg);
end

ret_spline=get_bbspline([5 coef(15)]);
function [ c,ceq ] = int_spline_cond( x )
%Nonlin Condindition for spline intgral 
%   Detailed explanation goes here
spline=get_bbspline(x);
q = fnint(spline);
ceq=fnval(q,1)-1
c=[];
end
end

