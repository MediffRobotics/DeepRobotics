%close all
clear all
deg = pi/180;
close;
%            theta    d      a   alpha
L(1) = Link([ 0      2.9      1   -pi/2   0]);
L(2) = Link([ 0       0      0   -pi/2     0]);
 L(3) = Link([ 0       2.8      0  pi/2   0]);
  L(4) = Link([ 0       0       0 ,-pi/2   0]);
 L(5) = Link([ 0       2.1      0      ,pi/2   0]);
  L(6) = Link([ 0       0      1       0     0]);

% 
% L(1) = Revolute('d', 0, 'a', 0, 'alpha', pi/2 );
% 
% L(2) = Revolute('d', 0, 'a', 2.90, 'alpha', 0);
% 
% L(3) = Revolute('d', 0, 'a', 0.85, 'alpha', -pi/2);
% 
% L(4) = Revolute('d', 3, 'a', 0, 'alpha', pi/2);
% 
% L(5) = Revolute('d', 0, 'a', 0, 'alpha', -pi/2 );
% 
% L(6) = Revolute('d', 0.90, 'a', 0, 'alpha', 0 );
% 

p560 = SerialLink(L, 'name', 'FUTURE ROBOT', ...
    'manufacturer', 'Unimation', 'ikine', 'puma', 'comment', 'viscous friction; params of 8/95');


p560.model3d = 'UNIMATE/MOTOMAN';



p560.plot([0 -pi/2 0  pi/3 0 pi/2] );
clear L
