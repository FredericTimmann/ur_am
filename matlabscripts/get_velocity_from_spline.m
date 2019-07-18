function [ V_dimless,acc_dimless ] = get_velocity_from_spline(bbspline,time,freq)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


%ppspline = fn2fm(bbspline,'pp')
acc=fnder(bbspline,1);
size_V=time*freq;
V_dimless = fnval(bbspline,linspace(0,1,size_V));
acc_dimless=fnval(acc,linspace(0,1,size_V));
%spline_values=spline_values(:)+t(:);
%spline_values=spline_values(:);

%plot(t,spline_values);
%hold on;

%plot(t,acc_values);

%plot(t,int_values);


end

