function [ E, opt_splineParam] = objective_t_singleParam( opt_p,msg,client,distance,goalMsg)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
'called objective'
time=msg.Time.Data;
goalMsg.Frequenz=100;
lb=0;
ub=4;
A = [];
b = [];
Aeq = [];
beq = [];
NONLCON= [];
%NONLCON= @int_spline_cond;
x0=[1];
%options = optimoptions('fmincon','Algorithm','sqp','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
options = optimoptions('fmincon','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
f=@(p) integral(p,opt_p);
[opt_splineParam]=fmincon(f,x0,A,b,Aeq,beq,lb,ub,NONLCON,options);
bbspline=get_bbspline([opt_p  opt_splineParam]);
q = fnint(bbspline);
size_V=time*goalMsg.Frequenz;
pos_Val = msg.StartPose.Position.Y-(fnval(q,linspace(0,1,size_V))*distance);
for i=1:size_V-1
    vel_from_pos(i)=(pos_Val(i+1)-pos_Val(i))*goalMsg.Frequenz;
end
opt_splineParam

global srv_state;
srv_state='optimat..'

%get veloctity vector for movement with respect to optimationParams
%bbspline=get_bbspline(p);
[ V_dimless,acc_dimless ] = get_velocity_from_spline(bbspline,time,goalMsg.Frequenz);
'has_spline Values'

%[client,goalMsg] = rosactionclient('/trajectory_execution');
'client'
goalMsg.StartPose=msg.StartPose;
goalMsg.GoalPose=msg.GoalPose;
goalMsg.Time=msg.Time.Data;
%goalMsg.VelocityVector=(V_dimless*distance/time)+0.00001;
goalMsg.VelocityVector=vel_from_pos;

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
function [int]=integral(c,p)
spline=get_bbspline([p c]);
q = fnint(spline);
a=fnval(q,1);
int=(a-1)*(a-1)
end




