close all
clear all

rosinit

sub = rossubscriber('/odom');
mat_vel_p = rospublisher('/mat_vel','geometry_msgs/Twist');
msg =  rosmessage(mat_vel_p);

msg.Linear.X = 0; %m/s
mag.Angular.Z = 0;
send(mat_vel_p,msg);
pause(3);

odom = receive(sub,10);
x = odom.Pose.Pose.Position.X;
y = odom.Pose.Pose.Position.Y;

plot(x,y,'-o');



Setpoint = 0;
Setang = -2;
msg.Linear.X = Setpoint; %m/s
msg.Angular.Z = Setang;
send(mat_vel_p,msg);

time = rostime("now");
while rostime("now") - time <5
    i = i+1
    odom = receive(sub,10);
    x_new = odom.Pose.Pose.Position.X;
    y_new = odom.Pose.Pose.Position.Y;
    x = x_new;
    y = y_new; 
end     
i = 0;
time = rostime("now");
odom = receive(sub,10);
j = 1;
while rostime("now") - time <10
    i = i+1
    odom = receive(sub,10);
    x_new = odom.Pose.Pose.Position.X;
    y_new = odom.Pose.Pose.Position.Y;
    plot(x_new,y_new,'-o');
    plot([x x_new],[y y_new],'-r');
    hold on;
    x = x_new;
    y = y_new;
 
    Setpoint = Setpoint+0.002
        
    msg.Linear.X = Setpoint;
        
    send(mat_vel_p,msg);
   
end     
pause(2)
Setpoint = 0;
msg.Linear.X = 0;
msg.Angular.Z = 0;
send(mat_vel_p,msg);
time = rostime("now") ;
i =1
for i=1:10
 send(mat_vel_p,msg);
 i = i+1;
end

rosshutdown