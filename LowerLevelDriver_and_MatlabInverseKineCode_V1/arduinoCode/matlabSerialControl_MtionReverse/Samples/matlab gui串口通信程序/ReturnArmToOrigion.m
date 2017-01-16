function  ReturnArmToOrigion( handles )
    global ReceivedTimesFromSerial;
    global AllMovements;
    MotorTagBase='a'-1;

    % Return arm to origion
    eSum=0;
    fSum=0;
    gSum=0;
    hSum=0;

    CurrentMovements=AllMovements{1};
    eSum=sum(CurrentMovements{'e'-MotorTagBase})+eSum;
    fSum=sum(CurrentMovements{'f'-MotorTagBase})+fSum;
    gSum=sum(CurrentMovements{'g'-MotorTagBase})+gSum;
    hSum=sum(CurrentMovements{'h'-MotorTagBase})+hSum;

    eSum=-eSum;
    fSum=-fSum;
    gSum=-gSum;
    hSum=-hSum;
    % Move to origion
    SendingToSerial( eSum,'e',handles );
    SendingToSerial( fSum,'f',handles );
    SendingToSerial( gSum,'g',handles );
    SendingToSerial( hSum,'h',handles );

    while (ReceivedTimesFromSerial<4)                       
            pause(0.01);                  
    end
        ReceivedTimesFromSerial=0;   
        pause(2);
     
end

