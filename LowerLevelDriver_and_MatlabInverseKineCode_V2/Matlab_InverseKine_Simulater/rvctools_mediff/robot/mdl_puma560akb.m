%MDL_PUMA560AKB Create model of Puma 560 manipulator
%
% MDL_PUMA560AKB is a script that creates the workspace variable p560m
% which describes the kinematic and dynamic characterstics of a Unimation
%   qz         zero joint angle configuration
%   qr         vertical 'READY' configuration
%   qstretch   arm is stretched out in the X direction
%
% Notes::
% Puma 560 manipulator modified DH conventions.
%
% Also defines the workspace vectors:
% - SI units are used.
%
% References::
% -  "The Explicit Dynamic Model and Inertial Parameters of the Puma 560 Arm"
%    Armstrong, Khatib and Burdick
%    1986
%
% See also SerialLink, mdl_puma560, mdl_stanford_mdh.

% MODEL: Unimation, Puma560, dynamics, 6DOF, modified_DH


% Copyright (C) 1993-2015, by Peter I. Corke
%
% This file is part of The Robotics Toolbox for MATLAB (RTB).
% 
% RTB is free software: you can redistribute it and/or modify
% it under the terms of the GNU Lesser General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
% 
% RTB is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU Lesser General Public License for more details.
% 
% You should have received a copy of the GNU Leser General Public License
% along with RTB.  If not, see <http://www.gnu.org/licenses/>.
%
% http://www.petercorke.com

clear L
%            theta    d        a    alpha
L(1) = Link([  0      0        0       0       0], 'modified');
L(2) = Link([  0      0       1      -pi/2    0], 'modified');
L(3) = Link([  0      0       2.9      0       0], 'modified');
L(4) = Link([  0      3       0.85    pi/2    0], 'modified');
%L(5) = Link([  0      0        0      pi/2    0], 'modified');
%L(6) = Link([  0      0        -0.9   -pi/2    0], 'modified');



% %            theta    d        a    alpha
% L(1) = Link([  0      0        0       0       0], 'modified');
% L(2) = Link([  0      0.2435   0      -pi/2    0], 'modified');
% L(3) = Link([  0     -0.0934   0.4318  0       0], 'modified');
% L(4) = Link([  0      0.4331  -0.0203  pi/2    0], 'modified');
% L(5) = Link([  0      0        0      -pi/2    0], 'modified');
% L(6) = Link([  0      0        0       pi/2    0], 'modified');

% L(1) = Link([  0      0        0       0       0], 'modified');
% L(2) = Link([  0      0        0       -pi/2    0], 'modified');
% L(3) = Link([  0     0.15      0.4318           0       0], 'modified');
% L(4) = Link([  0      0.4331   0.0203  -pi/2    0], 'modified');
% L(5) = Link([  0      0        0      pi/2    0], 'modified');
% L(6) = Link([  0      0        0       -pi/2    0], 'modified');


% viscous friction (motor referenced)
% unknown

% Coulomb friction (motor referenced)
% unknown

%
% some useful poses
%

p560m = SerialLink(L, 'name', 'Puma560-AKB', 'manufacturer', 'Unimation', 'comment', 'AK&B');
p560m.plot([0 -pi/2 0 0  ])
clear L
