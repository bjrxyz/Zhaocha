clear all;
close all;


picdata = imread('pic.bmp');

%ͼƬ���ȡ����
x = 392-15;
y = 420;

first_x_start = 10;
second_x = first_x_start + x + 132;

y_start = 200;

a1=picdata(y_start:y + y_start , first_x_start:(x+first_x_start),:);
a2=picdata(y_start:y + y_start , second_x:(second_x+x),:);


figure;
imshow(a1);
figure;
imshow(a2);


diff = imabsdiff(a1,a2);
figure, imshow(diff)

%ͼ���ȶ�ֵ������ͬ��

diff_01 = im2bw(imabsdiff(im2bw(a1), im2bw(a2)));
figure, imshow(diff_01)

%se = strel('line',15,15);
SE=strel('arbitrary',eye(5));
se = strel('rectangle',[20 20]);
bw2 = imdilate(diff_01,se);

%figure, imshow(bw2), title('Dilated')


%�ָ�����Ϊԭ�д�С,ʹ����ͬ�ĽṹԪ�ضԸ�ʴ����ͼ���������.
bw3=imdilate(diff_01,se);
figure,imshow(bw3)



