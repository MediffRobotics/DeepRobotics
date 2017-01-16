function SendingDataToArmBySocket(str_stepsVal)

%global sockCommu;
%fwrite(sockCommu, str_stepsVal)
number_of_retries=3;
client('192.168.0.16', 3000, number_of_retries,str_stepsVal);
end