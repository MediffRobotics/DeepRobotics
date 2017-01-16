function startup_main(  )

% Add simulater path
addpath(genpath('rvctools_mediff'));

%Add socket communication path
addpath(genpath('SocketLib'));
%Add Move Controlling path

%% Init simulater
startup_rvc()
%global mediffSimulator;
%mediffSimulator=mediff();
end

