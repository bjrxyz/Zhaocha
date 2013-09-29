function [diff] = setZero(xf,xl,yf,yl,diff)
%diff(xf:xl,yf:yl,:) = 0;
    [m,n,p] = size(diff);

%将矩形区域设为0
ex_margin = 20;
if(xf>ex_margin)
    xf = xf - ex_margin;
else
    xf = 1;
end
if(yf>ex_margin)
    yf = yf - ex_margin;
else
    yf = 1;
end
if(xl+ex_margin < m)
    xl = xl + ex_margin;
else
    xl = m;
end
if(yl+ex_margin < n)
    yl = yl + ex_margin;
else
    yl = n;
end


for i = xf: xl
    for j= yf:yl
        diff(i,j,:) = 0;
    end
end