
clear L
%            theta    d        a    alpha
L(1) = Link([  0      0        0       0       0], 'modified');
L(1).m=11.2;
L(1).r=[0.03349, 0, 0.023016];
L(1).I=[0.0757, 0.0889, 0.0813, 0, 0, -0.02646];

L(2) = Link([  0      0       1      -pi/2    0], 'modified');
L(2).m=3.63;
L(2).r=[0.1, 0.110, 0.445];
L(2).I=[0.0497, 0.0516, 0.0041, 0, 0, 0];

L(3) = Link([  0      0       2.9      0       0], 'modified');
L(3).m=12.05;
L(3).r=[0.08394, 0, 0.63617];
L(3).I=[0.0707, 0.0948, 0.0816, 0, 0, 0.0033];

L(4) = Link([  0      3       0.85    -pi/2    0], 'modified');
L(4).m=2.54;
L(4).r=[0.30, 0, 0.675];
L(4).I=[0.0156, 0.0362, 0.0438, 0, 0, 0];

L(5) = Link([  0      0        0      pi/2    0], 'modified');
L(5).m=0.74;
L(5).r=[0.43, 0, 0.675];
L(5).I=[0.0079, 0.012, 0.012, 0, 0, 0];

L(6) = Link([  0      0        0   -pi/2    0], 'modified');
L(6).m=0.13;
L(6).r=[0.48, 0, 0.675];
L(6).I=[0, 0, 0, 0, 0, 0];


p560m = SerialLink(L, 'name', 'MOTOMAN_HP3', 'manufacturer', 'Unimation', 'comment', 'AK&B');
p560m.plot([0 -pi/2 0 0 0 0  ])
clear L