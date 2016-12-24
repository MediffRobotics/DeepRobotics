function [ output_string ] = MovementRecording( input_val,input_MotorFlag,sign )
    global movementsRecording;
 
    if(isempty(movementsRecording))
        movementsRecording{'a'}=[];
        movementsRecording{'b'}=[];
        movementsRecording{'c'}=[];
        movementsRecording{'d'}=[];
        movementsRecording{'f'}=[1];
        movementsRecording{'g'}=[1];
        movementsRecording{'h'}=[1];
    end    
    val_int=sign*int64(input_val);    % convert to singed int          
    output_string =[num2str(val_int) input_MotorFlag]; %make a command
    
    %% for steppers
    if(input_MotorFlag>='f'||input_MotorFlag>='h')
             % determine the condition to create a new element    
             % if signs are different, creat a new element.
            if((movementsRecording{input_MotorFlag}(end)*val_int)<0)
                % concate nating movements
                movementsRecording{input_MotorFlag}=[movementsRecording{input_MotorFlag} val_int] ;      
            % diplay it
            else
                movementsRecording{input_MotorFlag}(end)=movementsRecording{input_MotorFlag}(end)+val_int ;     
            end
    
    else
    %% for servos    
        movementsRecording{input_MotorFlag}=[movementsRecording{input_MotorFlag} val_int] ;
        
    end
    
    display( movementsRecording{input_MotorFlag});
    [':' input_MotorFlag ]

end

