%% Optimation of Spline Parameters
%Optimation Parameters
lb=[1,0];
ub=[19,7];
A = [];
b = [];
Aeq = [];
beq = [];
NONLCON= @int_spline_cond;
x0=[2,2];

%options = optimoptions('fmincon','Algorithm','sqp','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
options = optimoptions('fmincon','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
f=@(p) objective_t(p);
[adj0opt,E]=fmincon(f,x0,A,b,Aeq,beq,lb,ub,NONLCON,options);

function [ c,ceq ] = int_spline_cond( x )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

spline=get_bbspline(x);
q = fnint(spline);
ceq=fnval(q,1)-1;
c=[];
end