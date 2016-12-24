s = serial('COM6');
set(s,'BaudRate',9600);
s.BytesAvailableFcnMode = 'terminator';  
s.BytesAvailableFcn = {@callback};  
fopen(s);

fprintf(s,'20f')
pause;
fclose(s)
delete(s)
clear s