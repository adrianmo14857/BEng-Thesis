close all 
clear all

rosinit

sub = rossubscriber('/debug');
mat_vel_p = rospublisher('/mat_vel','geometry_msgs/Twist');
msg =  rosmessage(mat_vel_p);

msg.Linear.X = 0; %m/s
mag.Angular.Z = 0;
send(mat_vel_p,msg);
pause(3);
vel=[];
vel2=[];
y=[];
 for i=0:0.025:10
    msg.Linear.X = i
    send(mat_vel_p,msg);
    pause(3);
    debug = receive(sub,10);
    vel = [vel debug.Linear.X];
    vel2 = [vel2 debug.Angular.X];
    y=[y i];
    figure(1)
    plot(y,vel,'-r');
    hold on;
    grid on
    figure(2)
    plot(y,vel2,'-r');
    hold on;
    grid on
end

msg.Linear.X = 7; %m/s
mag.Angular.Z = 0;
send(mat_vel_p,msg);
pause(5);
msg.Linear.X = 4; %m/s
mag.Angular.Z = 0;
send(mat_vel_p,msg);
pause(5);
msg.Linear.X = 0; %m/s
mag.Angular.Z = 0;
send(mat_vel_p,msg);
xlabel('Sterowanie');
ylabel('Prędkość [m/s]');
rosshutdown