close all
clear all

rosinit

sub = rossubscriber('/debug');
mat_vel_p = rospublisher('/mat_vel','geometry_msgs/Twist');
msg =  rosmessage(mat_vel_p);

Setpoint = 1,4; %0.1 - 1.4

msg.Linear.X = 0; %m/s
send(mat_vel_p,msg);
pause(3);

debug = receive(sub,10);
encoder3_last = debug.Angular.Y;
encoder1_last = debug.Linear.Y;

msg.Linear.X = Setpoint;
send(mat_vel_p,msg);
pause(1.5);


msg.Linear.X = 0; %m/s
send(mat_vel_p,msg);
pause(3);

debug = receive(sub,10);
encoder3_new = debug.Angular.Y;
encoder1_new = debug.Linear.Y;

encoder3 = encoder3_new -encoder3_last;
encoder1 = encoder1_new -encoder1_last;
encoder1_meters = encoder1*0.0089759790*0.067;
encoder3_meters = encoder3*0.0089759790*0.067;

 val = [encoder1 encoder1_meters encoder3 encoder3_meters];
rosshutdown