clear all;
clc
Delta = 5;
[X , Y] = meshgrid(-20:1:20);
Gaussian_Image = X.^2 + Y.^2 ;
Gaussian_Image = -Gaussian_Image/(2*Delta*Delta);
Gaussian_Image = exp(Gaussian_Image) / ((2*pi) * Delta*Delta);
figure 
surf(X,Y,Gaussian_Image);shading interp;
