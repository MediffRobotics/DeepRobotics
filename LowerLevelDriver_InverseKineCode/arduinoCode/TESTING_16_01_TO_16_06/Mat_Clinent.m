data='hello';

t = tcpip('172.16.0.155', 30001, 'NetworkRole', 'client');
fopen(t)
fwrite(t, data)


