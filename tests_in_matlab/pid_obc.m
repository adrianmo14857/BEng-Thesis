close all
clear all

rosinit

sub = rossubscriber('/debug');
mat_vel_p = rospublisher('/mat_vel','geometry_msgs/Twist');
msg =  rosmessage(mat_vel_p);

pid_param_pub = rospublisher('/pid_param','std_msgs/Float32MultiArray');
nastawy =  rosmessage(pid_param_pub);

Setpoint = 0;
Kp = 1;
Ki =  60;
Kd = 0.00;
msg.Linear.X = 0;
send(mat_vel_p,msg);

msg.Linear.X = Setpoint;
nastawy.Data(1) = Kp;
nastawy.Data(2) = Ki;
nastawy.Data(3) = Kd;

input = [];
current_time =  [];
kwadrat_bledu = 0;
i = 0;
    msg.Linear.X = Setpoint;
    send(pid_param_pub,nastawy);
    pause(2);
    send(pid_param_pub,nastawy);
    send(mat_vel_p,msg);
    time = rostime("now");
    while rostime("now") - time <3
        i = i+1;
        msg2 = receive(sub,10);
        input = [input msg2.Angular.X];
        y(i) = Setpoint;
        if msg2.Angular.X == 0
             msg.Linear.X = Setpoint
             send(mat_vel_p,msg);
        end
        figure(1)
        x= 1: length(input);
        plot(x,input,'-b');
        
        grid on;
        hold on;
        plot(x,y,'-r');
        hold on;
        kwadrat_bledu = kwadrat_bledu + (msg2.Angular.X - Setpoint)^2;
    end
    Setpoint = 1;
    msg.Linear.X = Setpoint;
    send(mat_vel_p,msg);
    time = rostime("now") ;
 while rostime("now") - time <2
        i = i+1;
        msg2 = receive(sub,10);
        input = [input msg2.Angular.X];
        y(i) = Setpoint;
        if msg2.Angular.X == 0
             msg.Linear.X = Setpoint
             send(mat_vel_p,msg);
        end
 
        x= 1: length(input);
        plot(x,input,'-b');
        hold on;
        plot(x,y,'-r');
        hold on;
        kwadrat_bledu = kwadrat_bledu + (msg2.Angular.X - Setpoint)^2;
 end
    Setpoint = 0;
    msg.Linear.X = Setpoint;
    send(mat_vel_p,msg);
    time = rostime("now") ;
 while rostime("now") - time <5
        i = i+1;
        msg2 = receive(sub,10);
        input = [input msg2.Angular.X];
        y(i) = Setpoint;
        if msg2.Angular.X == 0
             msg.Linear.X = Setpoint
             send(mat_vel_p,msg);
        end
 
        x= 1: length(input);
        plot(x,input,'-b');
        hold on;
        plot(x,y,'-r');
        hold on;
        kwadrat_bledu = kwadrat_bledu + (msg2.Angular.X - Setpoint)^2;
 end
 
 figure(2)    
x= linspace(0,60,length(input));
plot(x,input,'-b');
hold on
plot(x,y,'-r');
grid on
legend('Wartość pomiarowa','Wartość zadana');
xlabel('Czas [s]');
ylabel('Prędkość [m/s]');
msg.Linear.X = 0;
send(mat_vel_p,msg);
if msg2.Angular.X ~= 0
    msg.Linear.X = 0;
    send(mat_vel_p,msg);
end

rosshutdown