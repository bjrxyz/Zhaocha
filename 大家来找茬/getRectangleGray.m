function [xf,xl,yf,yl] = getRectangleGray(diff_rec_gray)



[x,y] = find(diff_rec_gray);

xf = min(x);
xl = max(x);

yf = min(y);
yl = max(y);

%{
[m,n] = size(diff_rec_gray);
% 矩形左上角的x坐标
b = 0;
for i = 1: m
    for j = 1:n
        if( diff_rec_gray(i,j) > 0 )
            xf = i;
            b = 1;
            break;
        end
    end
    if(b==1)
        break;
    end
end

b= 0;
for i = m :-1: 1
 for j = 1:n
if( diff_rec_gray(i,j,1) > 0 || diff_rec_gray(i,j,2) > 0 ||diff_rec_gray(i,j,3) > 0 )
   xl = i;
   b = 1;
   break;
end
 end
if(b==1)
    break;
end
end

b= 0;
 for j = 1:n
for i = 1: m

if( diff_rec_gray(i,j,1) > 0 || diff_rec_gray(i,j,2) > 0 ||diff_rec_gray(i,j,3) > 0 )
   yf = j;
   b = 1;
   break;
end
 end
if(b==1)
    break;
end
 end


 b = 0;
 for j = n:-1:1
     for i = 1:m
        if( diff_rec_gray(i,j,1) > 0 || diff_rec_gray(i,j,2) > 0 ||diff_rec_gray(i,j,3) > 0 )
            yl = j;
             b = 1;
             break;
        end
    end
if(b==1)
    break;
end

 end

%}