function SendingDataToArmBySocket(str_stepsVal)

global sockCommu;
fwrite(sockCommu, str_stepsVal)

end