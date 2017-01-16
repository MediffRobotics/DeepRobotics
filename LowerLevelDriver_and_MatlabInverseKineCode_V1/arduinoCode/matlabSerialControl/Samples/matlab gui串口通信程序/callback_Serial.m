function callback_Serial(s, BytesAvailable,handles)  
    global rawDataFromSerial;
    global ReceivedTimesFromSerial;
    if(isempty(ReceivedTimesFromSerial))
        ReceivedTimesFromSerial=0;
    end
    
    
    rawDataFromSerial = fscanf(s);
    set(handles.edit2,'string',rawDataFromSerial);
    ReceivedTimesFromSerial=ReceivedTimesFromSerial+1
  
%     if(out>='f' ||out>='h' )
%         ReceivedTimesFromSerial=ReceivedTimesFromSerial+1;
%     
%     end
     
end  

