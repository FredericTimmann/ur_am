function [ ret_spline ] = spline_opti( msg )
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
%options = optimoptions('fmincon','Algorithm','sqp','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
options = optimoptions('fmincon','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
f=@(p) objective_t(p,msg,client,distance,goalMsg);
[opt_splineParam,E]=fmincon(f,x0,A,b,Aeq,beq,lb,ub,NONLCON,options);
ret_spline=get_bbspline(opt_splineParam);


function [ c,ceq ] = int_spline_cond( x )
%Nonlin Condindition for spline intgral 
%   Detailed explanation goes here
spline=get_bbspline(x);
q = fnint(spline);
ceq=fnval(q,1)-1
c=[];
end
end

