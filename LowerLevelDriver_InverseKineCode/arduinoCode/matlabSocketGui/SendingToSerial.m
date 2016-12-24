function  SendingToSerial( Val_stepps,MotorFlag,handles)
          
    str_stepsVal=[num2str(Val_stepps) MotorFlag];
    fprintf(handles.serial,'%s',str_stepsVal);    


end

