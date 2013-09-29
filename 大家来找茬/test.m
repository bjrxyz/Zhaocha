a = [0 0 0 0; 
    0 0  1 0;
    0 0 0 0; 
    0 1 1 0];
[x,y] = find(a);

xf = min(x);
xl = max(x);

yf = min(y);
yl = max(y);


[xf, yf] = find(a,1,'first')