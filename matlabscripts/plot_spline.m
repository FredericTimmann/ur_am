function [ V_dimless,acc_dimless ] = plot_spline(argin)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if size(argin,2)<2 || size(argin,2)>5
    'wrong arg size'
    return
end
try
    close('plotfig');
end
if size(argin,2)==2
    num_coefz=round(argin(1));
    coefz=argin(2);
    freq=50;
    time=2;
    step_size=0.05;
if size(argin,2)==4
    num_coefz=round(argin(1));
    coefz=argin(2);
    freq=argin(3);
    time=argin(4);
    step_size=0.05;
end
if size(argin,2)==5
    num_coefz=round(argin(1));
    coefz=argin(2);
    freq=argin(3);
    time=argin(4);
    step_size=argin(5);
end
plotfig=figure('Name','plotfig');
if mod(num_coefz,2)==1
    a=zeros(1,num_coefz);
    a(ceil(end/2))=0.5;
    l_int=zeros(1,(num_coefz-1)/2);
    u_int=zeros(1,(num_coefz-1)/2);
    for i=1:((num_coefz-1)/2)
        l_int(end+1-i)=0.5-i*step_size;
        u_int(i)=0.5+i*step_size;
    end
    a=[l_int 0.5 u_int];
end
if mod(num_coefz,2)==0
    a=zeros(1,num_coefz);
    a(ceil(end/2))=0.5;
    a(floor(end/2))=0.5;
    l_int=zeros(1,(num_coefz/2-1));
    u_int=zeros(1,(num_coefz/2-1));
    for i=1:(num_coefz/2-1)
        l_int(end+1-i)=0.5-i*step_size;
        u_int(i)=0.5+i*step_size;
    end
    a=[l_int 0.5 0.5 u_int];
end


%a=augknt([0,1,[0.2 0.3 0.4 0.5 0.6 0.7 0.8]],3);
points=augknt([0,1,a], 3);
%c=zeros(1,num_coefz);
c=ones(1,num_coefz);
c=c*coefz;
%c=coeffs;



bbspline=spmak(points,c)
%ppspline = fn2fm(bbspline,'pp')
acc=fnder(bbspline,1);
t = linspace(0,1,110);
spline_values = fnval(bbspline,t);
acc_values = fnval(acc,t);
q = fnint(bbspline);
int_values = fnval(q,t);
fnval(q,1)

size_V=time*freq;
V_dimless = fnval(bbspline,linspace(0,1,size_V));
acc_dimless=fnval(acc,linspace(0,1,size_V));
%spline_values=spline_values(:)+t(:);
%spline_values=spline_values(:);

plot(t,spline_values);
hold on;
plot(t,acc_values);
plot(t,int_values);


end

