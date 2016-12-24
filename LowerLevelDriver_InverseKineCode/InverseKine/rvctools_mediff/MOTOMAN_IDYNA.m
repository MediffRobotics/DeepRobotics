clear all;
MOTOMAN_MODIFIED_finalVersion % Loading model
load('q.mat'); % Loading path data. path angles are saved in variable q               
load('q2.mat');

q=[q;q2];
%% qz: start 
%% qr: end
%% t: time

%% 


t=0:0.0577:5.7137;



%% q: joint space trajectory 
%% qd: velocity
%% qdd: acceleration
%% tau: joint torques

% Generating a series of q, qd,qdd for each group of joint angles
% qj=[0 0 0 0 0 0];
% qd=[0 0 0 0 0 0];
% qdd=[0 0 0 0 0 0];
[qj,qd,qdd] = jtraj(q(1,:), q(2,:),t(1:2)); % compute joint coordinate trajectory


for i=2:size(t,2)-1
    [a,b,c] = jtraj(q(i,:), q(i+1,:),t(i:i+1)); % compute joint coordinate trajectory

    qj=[qj;a(2,:)];
    qd=[qd;b(2,:)];
    qdd=[qdd;c(2,:)];
end

%[ qj,qd,qdd] = jtraj(q(1,:), q(100,:),t); % compute joint coordinate trajectory

%% q: joint space trajectory 
%% qd: velocity
%% qdd: acceleration
%% tau: joint torques
tau = p560m.rne(qj, qd, qdd); % compute inverse dynamics


%  Now the joint torques can be plotted as a function of time

plot( abs(tau(:,1:3))); xlabel('Time (s)'); ylabel('Joint torque (Nm)')

subplot(3,1,1); plot(qj(:,1)); xlabel('Time '); ylabel('Joint 1 (rad)');
subplot(3,1,2); plot(qj(:,2)); xlabel('Time '); ylabel('Joint 2 (rad)');
subplot(3,1,3); plot(qj(:,3)); xlabel('Time '); ylabel('Joint 3 (rad)');



