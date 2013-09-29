function [xf,yf] = findNotZero(diff)


[xf, yf] = find(diff,1,'first');

%{
%灰度图的非向量实现
[m,n] = size(diff);

xf = 0;
yf = 0;

b = 0;
for i = 1: m
 for j = 1:n
if( diff(i,j) > 0)
   xf = i;
   yf = j;
  % fprintf('\n (xf,yf):%d,%d\n',i,j);
 %  fprintf('\n (x,y,z):%d,%d,%d\n',diff_rec(i,j,1),diff_rec(i,j,2),diff_rec(i,j,3));
   
   b = 1;
   break;
end
 end
if(b==1)
    break;
end
end
%}

%{

%此方法用于原图，没有灰度化的图
[m,n,p] = size(diff);

yu = 50;

b = 0;
for i = 1: m
 for j = 1:n
if( diff(i,j,1) > yu || diff(i,j,2) > yu ||diff(i,j,3) > yu )
   xf = i;
   yf = j;
  % fprintf('\n (xf,yf):%d,%d\n',i,j);
 %  fprintf('\n (x,y,z):%d,%d,%d\n',diff_rec(i,j,1),diff_rec(i,j,2),diff_rec(i,j,3));
   
   b = 1;
   break;
end
 end
if(b==1)
    break;
end
end
%}