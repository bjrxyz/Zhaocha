clear all;
close all;

fname = {'d:/zhaocha/p1.bmp','d:\\zhaocha\\p2.bmp','d:\\zhaocha\\p3.bmp','d:\\zhaocha\\p4.bmp'}

dat = imread(fname{1});
[pic_l,pic_r] = getPic(dat);
%图片左右不同
diff = imabsdiff(pic_l,pic_r);

figure,imshow(diff);
for num = 1: 5
    
    %找出点击坐标
    diff_01 = im2bw(diff);     
    figure, imshow(diff_01);
    [xf,yf] = findNotZero(diff_01);
    %[xf,yf] = findNotZero(diff_01);

    
    fprintf('\n 点击坐标 xf,yf:%d,%d\n',xf,yf);
    %将坐标写入文件
    fid = fopen('d:\\zhaocha\\point.txt', 'wt');
    fprintf(fid, '%d\n', xf);
    fprintf(fid, '%d\n', yf);
    fclose(fid);
    pause;

    pic_last = pic_l;
    %读图像 计算矩形区域
    check = imread(fname{num+1});
    [pic_l,pic_r] = getPic(check);

    diff_rec = pic_l - pic_last;
    %diff_lr = pic_r - pic_l;
    [m,n,p] = size(diff_rec);


   % [xf,xl,yf,yl] = check_rectangle(diff_rec);
    diff_rec_gray = im2bw(diff_rec);
    [xf,xl,yf,yl] = getRectangleGray(diff_rec_gray);
    
 
diff = setZero(xf,xl,yf,yl,diff);
%setZero(diff_lr);




%figure, imshow(diff_lr);
%figure ,imshow(diff_rec);
figure, imshow(diff)
%figure, imshow(ddd)

end