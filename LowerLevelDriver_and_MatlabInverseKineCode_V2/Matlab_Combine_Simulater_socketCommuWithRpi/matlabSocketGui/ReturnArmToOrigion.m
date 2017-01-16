function  SockReturnArmToOrigion( handles )
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
    
    
    MovementsForJoint_e=[num2str(eSum) 'e,'];
    MovementsForJoint_f=[num2str(fSum) 'f,'];
    MovementsForJoint_g=[num2str(gSum) 'g,'];
    MovementsForJoint_h=[num2str(hSum) 'h;'];
    
    str_stepsVal=[MovementsForJoint_e MovementsForJoint_f MovementsForJoint_g MovementsForJoint_h];      
    SendingBySocketInRaw( str_stepsVal )            
end

