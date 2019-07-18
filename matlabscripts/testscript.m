%   Detailed explanation goes here
close all;
%optMsg=rosmessage('optimation_msgs/trajectory_optimation_msg');

%type in a,b in range [0 5]
a1=12;

%time i [s] for movement
t_ges=2;
%distance in [mm] for movement
s_ges=200;
%Command frequency
freq=50;

syms theta_a1;
%calc 
%A=1-(a2*(((a1/a2)*theta_a1^4)^(1/4)))-(2*a1*theta_a1^5);
%B=1-(((a1/a2)*theta_a1^4)^(1/4))-(2*theta_a1);
A=(1-(2*a1*(theta_a1^3)));
B=(1-(2*theta_a1));

h=((A/B)-(3*a1*(theta_a1^2)))==0;
tic
%tt_1=solve(h,theta_a1,'Real', true)
[solx, param, cond] = solve(h, theta_a1, 'ReturnConditions', true,'Real',true);
toc
%tt_2=((a1/a2)*tt_1^4)^(1/4);
solx(1)
solx(2)
solx(3)

s(1)=real(double(solx(1)))
s(2)=real(double(solx(2)))
s(3)=real(double(solx(3)))

b=sort(s);

theta_a11=b(2);
theta_a21=1-theta_a11;

%acceleration steps
%time for acceleration
ta_real_1=theta_a11*t_ges;
ta_real_2=(theta_a21*t_ges);

N_a1=ceil(ta_real_1*freq);

theta_s_a11=ta_real_1/t_ges;
theta_s_a21=1-theta_s_a11;

ts_invl_1=0:1/freq:ta_real_1;
ts_invl_2=ts_invl_1(end)+1/freq:1/freq:ta_real_2;
ts_invl_3=ts_invl_2(end)+1/freq:1/freq:t_ges;

points = [0 0 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9  1 1];
coefs=[0.3 0.2 0.2 0.2 0.2 0.2 0.2 0.2 0.2 ];

%B-Form Formulation
bbspline=my_spmak(points,coefs);
t1=linspace(0,theta_a11,N_a1);
t2=linspace(theta_a11,theta_a21,500);
t22=linspace(0,1-(2*theta_a11),500);

t3=linspace(theta_a21,1,N_a1);
t33=linspace(-theta_a11,0,N_a1);

m=3*a1*theta_a11^2;
b=a1*(theta_a11^3);
linfun=@(x) (m*x)+b;
parfun=@(x) (a1*(x^3));
der_parfun=@(x) (3*a1*(x^2));
der2_parfun=@(x) (6*a1*(x));
Interval=0.1436;
S1=parfun(Interval)
V1=der_parfun(Interval)
V1_=der_parfun(Interval)*s_ges/t_ges

A1=der2_parfun(Interval)


for i=1:length(t1) 
parVal(i)=parfun(t1(i));
par2Val(i)=parfun(t33(i))+1;
end
for i=1:length(t22) 
linVal(i)=linfun(t22(i));
end


for i=1:length(t1) 
V1_real(i)=der_parfun(t1(i))*s_ges/t_ges;
end
for i=1:length(ts_invl_2) 
V2_real(i)=m*s_ges/t_ges;
end
for i=1:length(t3) 
V3_real(i)=(der_parfun(t33(i)))*s_ges/t_ges;
end
V_real=[V1_real V2_real V3_real];
fig=figure();
hold on;
plot(t1,parVal,'b');
1
plot(t2,linVal,'b');
'2'
plot(t3,par2Val,'b');

%% Optimation of Spline Parameters
%Optimation Parameters
lb_spline=coefs-0.4;
ub_spline=coefs+0.4;
lb_acc=10;
ub_acc=100;
A = [];
b = [];
Aeq = [];
beq = [];
NONLCON= [];
spline_param=coefs;
acc_param=a1;
time_param=1;
%%updatefig2(points,spline_param);

options = optimoptions('fmincon','Algorithm','sqp','Display','final-detailed','MaxFunEvals',1000,'MaxIter',20000,'TolFun', 1e-8,'TolX',1e-6);
f=@(p) objective_t(p,points);
[adj0opt,E]=fmincon(f,acc_param,A,b,Aeq,beq,lb_acc,ub_acc,NONLCON,options);


%optispline=updatefig2(points,adj0opt);

adj0opt
global srv_state
srv_state='ready.....';
end

