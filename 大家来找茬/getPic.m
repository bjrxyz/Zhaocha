function [pic_l,pic_r] = getPic(dat)

kk=dat;
M=408;
N=377;

pic_l=kk(190:472,15:392,:);
pic_r=kk(190:472,M:M+N,:);