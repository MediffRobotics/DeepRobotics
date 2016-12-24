function callback_Serial(s, BytesAvailable,handles)  
    global rawDataFromSerial;
    global ReceivedTimesFromSerial;
    
    %Empty or received too many signals (>4) reset as 0
    if(isempty(ReceivedTimesFromSerial)||ReceivedTimesFromSerial>=4)
        ReceivedTimesFromSerial=0;
    end
    
    
    rawDataFromSerial = fscanf(s);
    set(handles.edit2,'string',rawDataFromSerial);
    ReceivedTimesFromSerial=ReceivedTimesFromSerial+1;
  
    ReceivedTimesFromSerial 
    rawDataFromSerial
end  

