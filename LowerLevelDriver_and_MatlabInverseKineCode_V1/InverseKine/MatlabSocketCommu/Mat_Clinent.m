data='hello';

t = tcpip('172.16.0.155', 30006, 'NetworkRole', 'client');

set(t,'InputBufferSize',10);
fopen(t)

fwrite(t, data)
%fread(t,9)
%pause(1)
data=fscanf(t)

