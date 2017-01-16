function [ output_string ] = MovementRecording( input_val,input_MotorFlag,sign,MoveIndex )
    global movementsRecording;  
    MotorTagBase='A'-1;
    
    persistent currentIndex;
    
    if(isempty(currentIndex))
        currentIndex=0;
    end
     input_MotorIndex=input_MotorFlag-MotorTagBase;
     
    if(MoveIndex>currentIndex)       
            movementsRecording{'A'-MotorTagBase}(MoveIndex)=1;
            movementsRecording{'B'-MotorTagBase}(MoveIndex)=1;
            movementsRecording{'C'-MotorTagBase}(MoveIndex)=1;
            movementsRecording{'D'-MotorTagBase}(MoveIndex)=1;
            movementsRecording{'E'-MotorTagBase}(MoveIndex)=1;
            movementsRecording{'F'-MotorTagBase}(MoveIndex)=1;  
    end
    currentIndex=MoveIndex;
    
    val_int=sign*int64(input_val);    % convert to singed int          
    output_string =[num2str(val_int) input_MotorFlag]; %make a command
    movementsRecording{input_MotorIndex}(MoveIndex)=...
        movementsRecording{input_MotorIndex}(MoveIndex)+val_int;

end

