t = tcpip('169.254.177.40', 30004, 'NetworkRole', 'server');
fopen(t);

data = fread(t, 1)
fclose(t);
clear all;