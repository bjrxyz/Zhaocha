function [xf,xl,yf,yl] = check_rectangle(diff_rec)

[m,n,p] = size(diff_rec);
b = 0;
 for j = n:-1:1
     for i = 1:m
        if( diff_rec(i,j,1) > 0 || diff_rec(i,j,2) > 0 ||diff_rec(i,j,3) > 0 )
            yl = j;
             b = 1;
             break;
        end
    end
if(b==1)
    break;
end

 end



b = 0;
for i = 1: m
 for j = 1:n
if( diff_rec(i,j,1) > 0 || diff_rec(i,j,2) > 0 ||diff_rec(i,j,3) > 0 )
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
if( diff_rec(i,j,1) > 0 || diff_rec(i,j,2) > 0 ||diff_rec(i,j,3) > 0 )
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

if( diff_rec(i,j,1) > 0 || diff_rec(i,j,2) > 0 ||diff_rec(i,j,3) > 0 )
   yf = j;
   b = 1;
   break;
end
 end
if(b==1)
    break;
end
end
