function [ E, opt_splineParam] = objective_t( opt_p,msg,client,distance,goalMsg)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
'called objective'

lb=0;
ub=4;
A = [];
b = [];
Aeq = [];
beq = [];
NONLCON= [];
%NONLCON= @int_spline_cond;
x0=[3];
%options = optimoptions('fmincon','Algorithm','sqp','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
options = optimoptions('fmincon','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
f=@(p) integral(p,opt_p);
[opt_splineParam]=fmincon(f,x0,A,b,Aeq,beq,lb,ub,NONLCON,options);
bbspline=get_bbspline([opt_p  opt_splineParam]);
opt_splineParam
goalMsg.Frequenz=25;
global srv_state;
srv_state='optimat..'
time=msg.Time.Data;
%get veloctity vector for movement with respect to optimationParams
%bbspline=get_bbspline(p);
[ V_dimless,acc_dimless ] = get_velocity_from_spline(bbspline,time,goalMsg.Frequenz);
'has_spline Values'

%[client,goalMsg] = rosactionclient('/trajectory_execution');
'client'
goalMsg.StartPose=msg.StartPose;
goalMsg.GoalPose=msg.GoalPose;
goalMsg.Time=msg.Time.Data;
goalMsg.VelocityVector=(V_dimless*distance/time)+0.001;
'client_sending'

[resultMsg,state,status] = sendGoalAndWait(client,goalMsg)
%send Velocity vector to action_server: simulate_optimation 
%actClient = rosactionclient(actionname,actiontype)
%sendGoal(actClient,goalMsg)
%waitForServer(actClient);
%[resultMsg,resultState] = sendGoalAndWait(actClient,goalMsg,10)

E=resultMsg.Energy;
E=double(abs(E*E));
'return energie'
end
function [i]=integral(c,p)
spline=get_bbspline([c  p]);
q = fnint(spline);
i=(fnval(q,1)-1)*(fnval(q,1)-1)
end




