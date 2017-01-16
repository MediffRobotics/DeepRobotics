function  SockReturnArmToOrigion( handles )
    global ReceivedTimesFromSerial;
    global AllMovements;
    MotorTagBase='a'-1;

    % Return arm to origion
    aSum=0;
    bSum=0;
    cSum=0;
    dSum=0;
    eSum=0;
    fSum=0;
   

    CurrentMovements=AllMovements{1};
    aSum=sum(CurrentMovements{'a'-MotorTagBase})+aSum;
    bSum=sum(CurrentMovements{'b'-MotorTagBase})+bSum;
    cSum=sum(CurrentMovements{'c'-MotorTagBase})+cSum;
    dSum=sum(CurrentMovements{'d'-MotorTagBase})+dSum;
    eSum=sum(CurrentMovements{'e'-MotorTagBase})+eSum;
    fSum=sum(CurrentMovements{'f'-MotorTagBase})+fSum;

    aSum=-aSum;
    bSum=-bSum;
    cSum=-cSum;
    dSum=-dSum;
    eSum=-eSum;
    fSum=-fSum;

    
    MovementsForJoint_a=[num2str(aSum) 'a,'];
    MovementsForJoint_b=[num2str(bSum) 'b,'];    
    MovementsForJoint_c=[num2str(cSum) 'c,'];
    MovementsForJoint_d=[num2str(dSum) 'd,'];
    MovementsForJoint_e=[num2str(eSum) 'e,'];
    MovementsForJoint_f=[num2str(fSum) 'f;'];
    
    str_stepsVal=[MovementsForJoint_a MovementsForJoint_b ...
        MovementsForJoint_c MovementsForJoint_d ...
        MovementsForJoint_e MovementsForJoint_f ];      
    
    SendingBySocketInRaw( str_stepsVal )            
end

