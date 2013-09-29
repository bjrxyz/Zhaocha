clear all;
close all;

fname = {'p1.bmp','p2.bmp','p3.bmp','p4.bmp'}



for num = 1: 1

    dat = imread(fname{num});
[pic_l,pic_r] = getPic(dat);
%图片左右不同
diff_lr = imabsdiff(pic_l,pic_r);
if(num ==1)
    diff = diff_lr;
end

[xf,yf] = findNotZero(diff_lr);
 

fprintf('\n xf,yf:%d,%d\n',xf,yf);
pause;
 
check = imread(fname{num+1});
[check_a,check_b] = getPic(check);

%矩形区域
diff_rec = check_a - pic_l;

[m,n,p] = size(diff_rec);


 [xf,xl,yf,yl] = check_rectangle(diff_rec);
 

%将矩形区域设为0
for i = xf: xl
    for j= yf:yl
        diff(i,j,:) = 0;
    end
end

%diff(xf:xl,yf:yl,:) = 0;

ddd = imabsdiff(diff,diff_lr);


 figure, imshow(diff_lr);
figure ,imshow(diff_rec);
figure, imshow(diff)
%figure, imshow(ddd)

end