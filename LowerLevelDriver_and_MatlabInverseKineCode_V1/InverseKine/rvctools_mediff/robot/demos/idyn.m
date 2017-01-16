
% Copyright (C) 1993-2014, by Peter I. Corke
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

%%begin

% Inverse dynamics computes the joint torques required to achieve the specified
% state of joint position, velocity and acceleration.  
% The recursive Newton-Euler formulation is an efficient matrix oriented
% algorithm for computing the inverse dynamics, and is implemented in the 
% function rne().
%
% Inverse dynamics requires inertial and mass parameters of each link, as well
% as the kinematic parameters.  This is achieved by augmenting the kinematic 
% description matrix with additional columns for the inertial and mass 
% parameters for each link.
%
% For example, for a Puma 560 in the zero angle pose, with all joint velocities
% of 5rad/s and accelerations of 1rad/s/s, the joint torques required are


% 
% tau = R.rne(q, qd, qdd) is the joint torque required for the robot R to 
% achieve the speci?ed joint positionq(1��N), velocityqd(1��N) and accelerationqdd(1��N),
% where N is the number of robot joints. 

%% QUESTION1: joint positionq(1��N) MEANS ANGLES?


mdl_puma560
tau = p560.rne(qz, 5*ones(1,6), ones(1,6))

% As with other functions the inverse dynamics can be computed for each point 
% on a trajectory.  Create a joint coordinate trajectory and compute velocity 
% and acceleration as well

t = [0:.056:2]; 		% create time vector
[q,qd,qdd] = jtraj(qz, qr, t); % compute joint coordinate trajectory
%% qz: start 
%% qr: end
%% t: time


%% q: joint space trajectory 
%% qd: velocity
%% qdd: acceleration
%% tau: joint torques
tau = p560.rne(q, qd, qdd); % compute inverse dynamics


%  Now the joint torques can be plotted as a function of time

plot(t, tau(:,1:3)); xlabel('Time (s)'); ylabel('Joint torque (Nm)')

% Much of the torque on joints 2 and 3 of a Puma 560 (mounted conventionally) is
% due to gravity.  That component can be computed using gravload()

%% taug = R.gravload(q) is the joint gravity loading (1��N) for the robot R in 
%% the joint con?guration q (1��N), where N is the number of robot joints. 
%% Gravitational acceleration is a property of the robot object.

taug = p560.gravload(q);
plot(t, taug(:,1:3)); xlabel('Time (s)'); ylabel('Gravity torque (Nm)')

% Now lets plot that as a fraction of the total torque required over the 
% trajectory

subplot(2,1,1); plot(t,[tau(:,2) taug(:,2)]); xlabel('Time (s)'); ylabel('Torque on joint 2 (Nm)');
subplot(2,1,2); plot(t,[tau(:,3) taug(:,3)]); xlabel('Time (s)'); ylabel('Torque on joint 3 (Nm)');

% The inertia seen by the waist (joint 1) motor changes markedly with robot 
% configuration.  The function inertia() computes the manipulator inertia matrix
% for any given configuration.
%
% Let's compute the variation in joint 1 inertia, that is M(1,1), as the 
% manipulator moves along the trajectory (this may take a few minutes)

%i = R.inertia(q) is the symmetric joint inertia matrix (N �� N) which relates 
%joint torque to joint acceleration for the robot at joint con?gurationq. 
%If q is a matrix (K ��N), each row is interpretted as a joint state vector,
%and the result is a 3d-matrix (N �� N �� K) where each plane corresponds to
%the inertia for the corresponding row ofq.


M = p560.inertia(q);



M11 = squeeze(M(1,1,:));
clf; plot(t, M11); xlabel('Time (s)'); ylabel('Inertia on joint 1 (kgms2)')

% Clearly the inertia seen by joint 1 varies considerably over this path.
% This is one of many challenges to control design in robotics, achieving 
% stability and high-performance in the face of plant variation.  In fact 
% for this example the inertia varies by a factor of
max(M11)/min(M11)
