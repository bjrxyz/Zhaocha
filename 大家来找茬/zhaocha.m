clear all;

close all;
dat = imread('t.jpg');

kk=dat;
M=408;
N=377;
a1=kk(190:472,15:392,:);
a2=kk(190:472,M:M+N,:);

 diff = imabsdiff(a1,a2);
 diff_01 = im2bw(diff);

 
 
check = imread('checked.jpg');
check_a=check(190:472,15:392,:);
check_b=check(190:472,M:M+N,:);

d = check_a - a1;

[m,n,p] = size(d);

[xf,yf] = find(d(:,:,1),1,'first');
[xl,yl] = find(d(:,:,1),1,'last');

for i = 1: m
  indices =  find(d(i,:,:));
  num = size(indices,2);
  if(num > 1)
      xf = min(indices);
      break;
  end
end

for i = m : 1
  indices =  find(d(i,:,:));
  num = size(indices,2);
  if(num > 1)
      xl = max(indices);
      break;
  end
end

for i = 1: n
  indices =  find(d(:,i,:));
  num = size(indices,2);
  if(num > 1)
      yf = min(indices);
      break;
  end
end

for i = n:1
  indices =  find(d(:,i,:));
  num = size(indices,2);
  if(num > 1)
      yl = max(indices);
      break;
  end
end




for i = 1: m
 for j = 1:n
if( d(i,j,1) > 0 || d(i,j,2) > 0 ||d(i,j,3) > 0 )
   xf = i;
   break;
end
end
end


for i = m : 1
 for j = 1:n
if( d(i,j,1) > 0 || d(i,j,2) > 0 ||d(i,j,3) > 0 )
   xl = i;
   break;
end
end
end

 for j = 1:n
for i = 1: m

if( d(i,j,1) > 0 || d(i,j,2) > 0 ||d(i,j,3) > 0 )
   yf = j;
   break;
end
end
end

 for j = n:1
for i = 1;m

if( d(i,j,1) > 0 || d(i,j,2) > 0 ||d(i,j,3) > 0 )
   yl = j;
   break;
end
end
end


%{
count = 1;

for i = 1: m
 for j = 1:n
if( d(i,j,1) > 0 || d(i,j,2) > 0 ||d(i,j,3) > 0 )
    
    r(1,count) = i;
    count = count+1;
end
end
end
 %}

figure, imshow(diff);
figure ,imshow(d);

diff2 = diff;
for i = xf: xl
    for j= yf:yl
        diff2(i,j,:) = 0;
    end
end

%diff(xf:xl,yf:yl,:) = 0;

ddd = imabsdiff(diff2,diff);
figure, imshow(diff2)
figure, imshow(ddd)