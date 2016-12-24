clear all;
MOTOMAN_MODIFIED_finalVersion % Loading model

%% Define parameters
%forward
Theta_1=0;
Theta_2=-pi/2;
Theta_3=0;
Theta_4=0;
Theta_5=0;
Theta_6=0;
%invers

% Coord_x1=3.2;
% Coord_y1=-2;
% Coord_z1=-4.8;
% 
% Coord_x2=3.2;
% Coord_y2=0;
% Coord_z2=-4.8;
Coord_x1=3.2;
Coord_y1=0;
Coord_z1=-4.8;

Coord_x2=3.2;
Coord_y2=2;
Coord_z2=-4.8;



Angle_x=0;
Angle_y=0;
Angle_z=0;

%mdl_MotomanHP6
q = [0 0 -pi/2 0 0 0 ];
T = p560m.fkine(q);
Forward_Kene_Coordinate=T*[0,0,0,1]';



%% Instructions of using inverse kene: 
%% T1,T2 are 4by4 matrices, it defines the 
%% starting point and pose, and end point and pose
%% of the motomanHP3 robot
	
T1 = transl(Coord_x1,Coord_y1,Coord_z1)*trotx(Angle_x) *troty(Angle_y) * trotz(Angle_z);	% define the start point
T2 = transl(Coord_x2,Coord_y2,Coord_z2)*trotx(Angle_x) *troty(Angle_y) * trotz(Angle_z);	   % and destination
T = ctraj(T1, T2, 50); 	% compute a Cartesian path

% now solve the inverse kinematics
q = p560m.ikine(T); 
about q

% which has one row per time step and one column per joint angle
% Let's examine the joint space trajectory that results in straightline 
% Cartesian motion

subplot(3,1,1); plot(q(:,1)); xlabel('Time (s)'); ylabel('Joint 1 (rad)');
subplot(3,1,2); plot(q(:,2)); xlabel('Time (s)'); ylabel('Joint 2 (rad)');
subplot(3,1,3); plot(q(:,3)); xlabel('Time (s)'); ylabel('Joint 3 (rad)');

% This joint space trajectory can now be animated
clf
p560m.plot(q)

q2=q;
save('q2')
