close all
clear all

rosinit;
sub = rossubscriber('/joy');
pause(1);
figure(1)
grid on
hold on
for i=1:1000
    msg2 = receive(sub,10);
    gain = (msg2.Axes(6)-1)*(-0.5)
    plot(msg2.Axes(1)*gain,msg2.Axes(2)*gain,'-o');
    i=i+1;
end

rosshutdown