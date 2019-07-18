function [ bbspline ] = get_bbspline( argin )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
%a=[0 0   1 1];
if size(argin,2)~=2
    'wrong arg size'
    return
end
num_coefz=round(argin(1));
coefz=argin(2);
step_size=0.05;
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
bbspline=spmak(points,c);
end

