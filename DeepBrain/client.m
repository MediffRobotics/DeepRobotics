% CLIENT connect to a server and read a ReceivedMessage
%
% Usage - ReceivedMessage = client(host, port, number_of_retries)
classdef client
         properties
             input_socket;
             input_stream;
             d_input_stream;
             
             % For motor control
             OldShiftingSteps;
         end
         
         methods 
            function obj=client ()
                import java.net.Socket
                import java.io.*                                
                
                obj.OldShiftingSteps=0;
                global Uparm_OldShiftingSteps;
                Uparm_OldShiftingSteps=0;
                
                global Elbow_OldShiftingSteps;
                Elbow_OldShiftingSteps=0;
            end
            
            function OpenSocket(obj) 
                import java.net.Socket
                import java.io.*
                % Init variables
                number_of_retries = 5; 
                host='192.168.0.16';
                port=3000;                
                retry = 0;                                
                ReceivedMessage      = [];             
                
                % Staring connection                                   
                fprintf(1, 'Retry %d connecting to %s:%d\n', ...
                        retry, host, port);

                % throws if unable to connect
                global input_socket ;
                input_socket = Socket(host, port);

                % get a buffered data input stream from the socket
                %obj.input_stream   = obj.input_socket.getInputStream;
                %obj.d_input_stream = DataInputStream(obj.input_stream);
                fprintf(1, 'Connected to server\n');
                
            end
            
            function CloseSocket(obj)
                    import java.net.Socket
                    import java.io.*                                     
                  %% Close socket
                    global input_socket;
                    input_socket.close;
            end
            
            function MoveArm(obj,SendMessage_Deg)
                    import java.net.Socket
                    import java.io.*
                  %% write data to socket (remote hosts)
                    global input_socket ;
                    Read_output_stream=input_socket.getOutputStream;
                    d_Readoutput_stream = DataOutputStream(Read_output_stream);

                  %% Sending data to Up arm
                    % output the data over the DataOutputStream
                    % Convert to stream of bytes            
%                     UpdateShiftingSteps=obj.UpArm_Angles2Steps(SendMessage_Deg);
%                     SendMessage=[num2str(int32(UpdateShiftingSteps)) 'B'];
%                     fprintf(1, 'Writing %d bytes\n', length(SendMessage));
%                     d_Readoutput_stream.writeBytes(char(SendMessage));
%                     d_Readoutput_stream.flush;
                    
                  %% Sending data to elbow
                    
                    UpdateShiftingSteps=obj.Elbow_Angles2Steps(SendMessage_Deg);
                    SendMessage=[num2str(int32(UpdateShiftingSteps)) 'C'];
                    fprintf(1, 'Writing %d bytes\n', length(SendMessage));
                    d_Readoutput_stream.writeBytes(char(SendMessage));
                    d_Readoutput_stream.flush;
                    
                  %% 
                
            end
            
         function UpdateShiftingSteps=Elbow_Angles2Steps(obj,Angle_Deg)
              
              global Elbow_OldShiftingSteps;  
              
              MovingSide_InitLength=231.03; % connect to motor
              ShortSideLength=50;%mm
              LongSideLength=235.63;%mm
              pi=3.14159;
              alpha=pi/2;
              beta=0.19861847;
              Angle_Rad=Angle_Deg*(pi/180);% deg to rad
              AngleTheta=pi-(alpha+beta+Angle_Rad);
              
              MovingSide_NewLength=sqrt(ShortSideLength^2+...
                  LongSideLength^2-2*LongSideLength*ShortSideLength*cos(AngleTheta));
              
              ShiftingLength=MovingSide_InitLength-MovingSide_NewLength; % in mm
              
              
              %Motor 1 revolution=6400 steps              
              %1 revolution = 2mm, so 0.5R/m
              ShiftingSteps=0.5*ShiftingLength*6400;  
              
              UpdateShiftingSteps=ShiftingSteps-Elbow_OldShiftingSteps;
              Elbow_OldShiftingSteps=ShiftingSteps;
            end
            
            function UpdateShiftingSteps=UpArm_Angles2Steps(obj,Angle_Deg)              
              global Uparm_OldShiftingSteps;  
              
              MovingSide_InitLength=274.61; % connect to motor
              ShortSideLength=65;%mm
              LongSideLength=280.85;
              pi=3.14159;
              alpha=pi/2;
              beta=0.2122;
              Angle_Rad=Angle_Deg*(pi/180);% deg to rad
              AngleTheta=pi-(alpha+beta+Angle_Rad);
              
              MovingSide_NewLength=sqrt(ShortSideLength^2+...
                  LongSideLength^2-2*LongSideLength*ShortSideLength*cos(AngleTheta));
              
              ShiftingLength=MovingSide_InitLength-MovingSide_NewLength; % in mm
              
              
              %Motor 1 revolution=1600 steps
              %1 revolution = 2mm, so 0.5R/m
              ShiftingSteps=0.5*ShiftingLength*1600;  
              
              UpdateShiftingSteps=ShiftingSteps-Uparm_OldShiftingSteps;
              Uparm_OldShiftingSteps=ShiftingSteps;
            end
            
            function ReceivedMessage = SockRecevingMoveData(obj)
                
                ReceivedMessage=0;
              %% write data to socket (remote hosts)
                Read_output_stream=input_socket.getOutputStream;
                d_Readoutput_stream = DataOutputStream(Read_output_stream);

                % output the data over the DataOutputStream
                % Convert to stream of bytes
                % pause(0.5);            
                fprintf(1, 'Writing %d bytes\n', length(SendMessage));
                d_Readoutput_stream.writeBytes(char(SendMessage));
                d_Readoutput_stream.flush;

                return ;                                     
            end
            
         end
        
end