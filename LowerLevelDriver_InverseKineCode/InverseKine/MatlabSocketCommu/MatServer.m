clear all;
t = tcpip('0.0.0.0', 30000, 'NetworkRole', 'server');
fopen(t);
data = fread(t, t.BytesAvailable);
plot(data);
