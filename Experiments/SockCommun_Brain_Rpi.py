import math

class BrainCommuViaSock:
    def __init__(self):
        self.Uparm_OldShiftingSteps=0;
        self.Elbow_OldShiftingSteps=0;
    def Elbow_Angles2Steps(self,Angle_Deg=0):

        #Init
        MovingSide_InitLength=231.03; # connect to motor
        ShortSideLength=50;#mm
        LongSideLength=235.63;#mm
        pi=3.14159;
        alpha=pi/2;
        beta=0.19861847;

        #Converting
        Angle_Rad=Angle_Deg*(pi/180);# deg to rad
        AngleTheta=pi-(alpha+beta+Angle_Rad);

        MovingSide_NewLength=math.sqrt(ShortSideLength*ShortSideLength+
            LongSideLength*LongSideLength-2*LongSideLength*
            ShortSideLength*math.cos(AngleTheta));

        ShiftingLength=MovingSide_InitLength-MovingSide_NewLength; # in mm


        #Motor 1 revolution=6400 steps
        #1 revolution = 2mm, so 0.5R/m
        ShiftingSteps=0.5*ShiftingLength*6400;

        UpdateShiftingSteps=ShiftingSteps-self.Elbow_OldShiftingSteps;
        self.Elbow_OldShiftingSteps=ShiftingSteps;

        UpdateShiftingSteps=int(UpdateShiftingSteps)
        #print ('Elbow_UpdateShiftingSteps: %d',UpdateShiftingSteps)


        return UpdateShiftingSteps


    def UpArm_Angles2Steps(self,Angle_Deg=0):
        MovingSide_InitLength=274.61;#connect to motor
        ShortSideLength=65;#mm
        LongSideLength=280.85;
        pi=3.14159;
        alpha=pi/2;
        beta=0.2122;
        Angle_Rad=Angle_Deg*(pi/180);#deg to rad
        AngleTheta=pi-(alpha+beta+Angle_Rad);

        MovingSide_NewLength=math.sqrt(ShortSideLength*ShortSideLength
            +LongSideLength*LongSideLength-2*LongSideLength
            *ShortSideLength*math.cos(AngleTheta));

        ShiftingLength=MovingSide_InitLength-MovingSide_NewLength; # in mm


        #Motor 1 revolution=1600 steps
        #1 revolution = 2mm, so 0.5R/m
        ShiftingSteps=0.5*ShiftingLength*1600;

        UpdateShiftingSteps=ShiftingSteps-self.Uparm_OldShiftingSteps;
        self.Uparm_OldShiftingSteps=ShiftingSteps;

        UpdateShiftingSteps=int(UpdateShiftingSteps)
        #print('Up_arm UpdateShiftingSteps: %d' % UpdateShiftingSteps)          
        return UpdateShiftingSteps



if __name__=='__main__':
    objBrainSockCommu=BrainCommuViaSock()
    while True:
        objBrainSockCommu.UpArm_Angles2Steps()
        objBrainSockCommu.Elbow_Angles2Steps()
        cmd=raw_input("Please input cmd:")
