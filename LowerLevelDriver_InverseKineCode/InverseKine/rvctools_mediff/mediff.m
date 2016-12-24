close all
clear all


%            theta    d      a   alpha
L(1) = Link([ 0      6       3   pi/2    0]);
L(2) = Link([ 0      0       6   pi      0]);
L(3) = Link([ 0      0       0   -pi/2   0]);
L(4) = Link([ 0      6       0   pi/2    0]);
L(5) = Link([ 0      0       0   -pi/2   0]);
L(6) = Link([ 0      4       0   0       0]);

mediffArm = SerialLink(L, 'name', 'MEDIFF ARM', ...
    'manufacturer', 'Unimation', 'ikine', 'puma',...
    'comment', 'viscous friction; params of 8/95');

mediffArm.model3d = 'UNIMATE/MOTOMAN';
mediffArm.plot([0 0 0 0 0 0] );

%% inverse
%T1 = transl(9, -0, -4) % define the start point
T1 = mediffArm.fkine([0 0 0 0 0 0]);
%T2 = transl(9, 0, 0)	% and destination
T2=T1+[0 0 0 2; ...
       0 0 0 -3;...
       0 0 0 4;...
       0 0 0 0];

T = ctraj(T1, T2, 5); 	% compute a Cartesian path
qi = mediffArm.ikine(T);
 
mediffArm.plot(qi);

% %mediffArm.teach();

 T = mediffArm.fkine(mediffArm.getpos())
% clear L T2=T1+[0 0 0 0;0 0 0 0; 0 0 0 2;0 0 0 0]
