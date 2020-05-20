#include "myTurtlebot_core_config.h"


//The setup function is called once at startup of the sketch
void setup()
{

	//init ROS node handle
	nh.initNode();
	nh.getHardware() ->setBaud(57600);

	//subscribers
	nh.subscribe(cmd_vel_sub);
	nh.subscribe(joy_vel_sub);
	nh.subscribe(mat_vel_sub);
	nh.subscribe(pid_param_sub);

	//publishers
	nh.advertise(imu_state_pub);
	nh.advertise(imu_pub);
	nh.advertise(odom_pub);
	nh.advertise(l_engines_state_pub);
	nh.advertise(r_engines_state_pub);
	nh.advertise(debug_pub);
	tf_broadcaster.init(nh);

	//Init encoder
	encoder_init();
	//control LED

	pinMode(13,OUTPUT);
	digitalWrite(13,HIGH);

	//Init motor shield
	md.init();

	//Init PID
	pid_init();

	//Init imu
	imu_init();


	//Init odometry
	initOdom();

	prev_update_time = millis();

	setup_end = true;
}

// The loop function is called in an endless loop
void loop()
{
	uint32_t t=millis();
	updateTime();

	if(nh.connected())	initOdom();

	updateTFPrefix(nh.connected());


	if ((t-tTime[0]) >= (1000 / CONTROL_MOTOR_SPEED_FREQUENCY))
	{
		setSetpoint();
		if (((t-tTime[6]) > CONTROL_MOTOR_TIMEOUT) || ((t-tTime[7]) > CONTROL_MOTOR_TIMEOUT) || ((t-tTime[8]) > CONTROL_MOTOR_TIMEOUT))
	    {
			controlMotor(zero_velocity);
	    }
	    else
	    {
	    	controlMotor(goal_velocity);
	    }
	    tTime[0] = t;
	}
	if ((t-tTime[1]) >= (1000 / SENSOR_INFO_PUBLISH_FREQUENCY))
	{
		publishImuState();
		publish_L_EnginesStatus();
		publish_R_EnginesStatus();

	    tTime[1] = t;
	}
	if ((t-tTime[2]) >= (1000 / DRIVE_INFORMATION_PUBLISH_FREQUENCY))
	{
		debugPublish();
		publishOdometry();
	    tTime[2] = t;
	}
	if ((t-tTime[3]) >= (1000 / IMU_PUBLISH_FREQUENCY))
	{
		publishImuMsg();
	    tTime[3] = t;
	}

	nh.spinOnce();
}
void commandVelocityCallback(const geometry_msgs::Twist& cmd_vel_msg)
{
	cmd_goal_velocity[LINEAR]  = cmd_vel_msg.linear.x;
	cmd_goal_velocity[ANGULAR] = cmd_vel_msg.angular.z;

	cmd_goal_velocity[LINEAR]  = constrain(cmd_goal_velocity[LINEAR],  MIN_LINEAR_VELOCITY, MAX_LINEAR_VELOCITY);
	cmd_goal_velocity[ANGULAR] = constrain(cmd_goal_velocity[ANGULAR], MIN_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);

	tTime[6] = millis();
}
void matlabVelocityCallback(const geometry_msgs::Twist& mat_vel_msg)
{
	mat_goal_velocity[LINEAR]  = mat_vel_msg.linear.x;
	mat_goal_velocity[ANGULAR] = mat_vel_msg.angular.z;

	mat_goal_velocity[LINEAR]  = constrain(mat_goal_velocity[LINEAR],  MIN_LINEAR_VELOCITY, MAX_LINEAR_VELOCITY);
	mat_goal_velocity[ANGULAR] = constrain(mat_goal_velocity[ANGULAR], MIN_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);


	tTime[7] = millis();
}
void joyVelocityCallback(const sensor_msgs::Joy& joy_vel_msg)
{

	joy_button = joy_vel_msg.buttons[0];
	joy_goal_velocity[LINEAR]  = joy_vel_msg.axes[1] * MAX_LINEAR_VELOCITY;
	joy_goal_velocity[ANGULAR] = joy_vel_msg.axes[0] * MAX_ANGULAR_VELOCITY;

	joy_goal_velocity[LINEAR]  = constrain(joy_goal_velocity[LINEAR],  MIN_LINEAR_VELOCITY, MAX_LINEAR_VELOCITY);
	joy_goal_velocity[ANGULAR] = constrain(joy_goal_velocity[ANGULAR], MIN_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);


	tTime[8] = millis();
}
void setSetpoint()
{
	goal_velocity[LINEAR]  = cmd_goal_velocity[LINEAR] + joy_goal_velocity[LINEAR] + mat_goal_velocity[LINEAR];
	goal_velocity[ANGULAR] = cmd_goal_velocity[ANGULAR]+ joy_goal_velocity[ANGULAR] + mat_goal_velocity[ANGULAR];

	goal_velocity[LINEAR]  = constrain(goal_velocity[LINEAR],  MIN_LINEAR_VELOCITY, MAX_LINEAR_VELOCITY);
	goal_velocity[ANGULAR] = constrain(goal_velocity[ANGULAR], MIN_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);


	Setpoint[LEFT] = (double)(goal_velocity[LINEAR] - (goal_velocity[ANGULAR]*WHEEL_SEPARATION / 2));
	Setpoint[RIGHT] = (double)(goal_velocity[LINEAR] + (goal_velocity[ANGULAR]*WHEEL_SEPARATION / 2));

	Setpoint[LEFT] = constrain(Setpoint[LEFT], -MAX_LINEAR_VELOCITY,MAX_LINEAR_VELOCITY);
	Setpoint[RIGHT] = constrain(Setpoint[RIGHT], -MAX_LINEAR_VELOCITY,MAX_LINEAR_VELOCITY);

}

void pidParamCallback(const std_msgs::Float32MultiArray &pid_param)
{
	Kp = double(pid_param.data[0]);
	Ki = double(pid_param.data[1]);
	Kd = double(pid_param.data[2]);
	myPID_l.SetTunings(Kp,Ki,Kd);
	myPID_r.SetTunings(Kp,Ki,Kd);
}


void encoder_init(void)
{

	direction1 = true; //default ->Forward
	direction2 = true;
	direction3 = true;
	//direction4 = true; //encoder 4 - damaged

	pinMode(encoder1A,INPUT);
	pinMode(encoder2A,INPUT);
	pinMode(encoder3A,INPUT);
	//pinMode(encoder4A,INPUT); //encoder 4 - damaged
	pinMode(encoder1B,INPUT);
	pinMode(encoder2B,INPUT);
	pinMode(encoder3B,INPUT);
	//pinMode(encoder4B,INPUT); //encoder 4 - damaged



	attachInterrupt(digitalPinToInterrupt(encoder1A),wheelSpeed1,HIGH);
	attachInterrupt(digitalPinToInterrupt(encoder2A),wheelSpeed2,HIGH);
	attachInterrupt(digitalPinToInterrupt(encoder3A),wheelSpeed3,HIGH);
	//attachInterrupt(digitalPinToInterrupt(encoder4A),wheelSpeed4,HIGH); //encoder 4 - damaged

}
void wheelSpeed1(void)
{

	int state1B = digitalRead(encoder1B);
	if(state1B == HIGH)	direction1 = true;
	else	direction1 = false;

	if(direction1)	duration1--;
	else duration1++;
}
void wheelSpeed2(void)
{

	int state2B = digitalRead(encoder2B);
	if(state2B == HIGH)	direction2 = true;
	else	direction2 = false;

	if(direction2)	duration2--;
	else duration2++;
}

void wheelSpeed3(void)
{

	int state3B = digitalRead(encoder3B);
	if(state3B == HIGH)	direction3 = true;
	else	direction3 = false;

	if(direction3)	duration3++;
	else duration3--;
}
void wheelSpeed4(void)
{

	int state4B = digitalRead(encoder4B);
	if(state4B == HIGH)	direction4 = true;
	else	direction4 = false;

	if(!direction4)	duration4++;
	else duration4--;
}

void pid_init(void)
{
	myPID_l.SetMode(AUTOMATIC);
	myPID_l.SetSampleTime(10);
	myPID_l.SetOutputLimits(-10,10);
	myPID_r.SetMode(AUTOMATIC);
	myPID_r.SetSampleTime(10);
	myPID_r.SetOutputLimits(-10,10);
}

void imu_init(void)
{
	imu_status = IMU.begin();
}

void updateTime(void)
{
	current_offset = millis();
	current_time = nh.now();
}

ros::Time rosNow(void)
{
  return nh.now();
}

void publishImuMsg(void)
{
	IMU.readSensor();

	imu_msg.linear_acceleration.x =IMU.getAccelX_mss();
	imu_msg.linear_acceleration.y = IMU.getAccelY_mss();
	imu_msg.linear_acceleration.z = IMU.getAccelZ_mss();


	imu_msg.angular_velocity.x = IMU.getGyroX_rads();
	imu_msg.angular_velocity.y = IMU.getGyroY_rads();
	imu_msg.angular_velocity.z = IMU.getGyroZ_rads();

	imu_msg.orientation.x = IMU.getMagX_uT();
	imu_msg.orientation.y = IMU.getMagY_uT();
	imu_msg.orientation.z = IMU.getMagX_uT();
	imu_msg.header.stamp    = rosNow();
	imu_msg.header.frame_id = imu_frame_id;

	imu_pub.publish(&imu_msg);
}

void publishOdometry(void)
{
	unsigned long time_now = millis();
	unsigned long step_time = time_now - prev_update_time;

	prev_update_time = time_now;
	ros::Time stamp_now = rosNow();

	calcOdometry((double)(step_time * 0.001));

	updateOdometry();
	odom.header.stamp = stamp_now;
	odom_pub.publish(&odom);

	// odometry tf
	updateTF(odom_tf);
	odom_tf.header.stamp = stamp_now;
	tf_broadcaster.sendTransform(odom_tf);


}
void publishImuState(void)
{
	imu_state_msg.data = imu_status;

	imu_state_pub.publish(&imu_state_msg);
}

void publish_L_EnginesStatus(void)
{
	l_engines_state_msgs.data = md.getM1Fault();

	l_engines_state_pub.publish(&l_engines_state_msgs);
}

void publish_R_EnginesStatus(void)
{
	r_engines_state_msgs.data = md.getM2Fault();

	r_engines_state_pub.publish(&r_engines_state_msgs);
}

void initOdom(void)
{


	for (int index = 0; index < 3; index++)
	{
		odom_pose[index] = 0.0; //without it if trajectory
		odom_vel[index]  = 0.0; //without it if trajectory
	}

	odom.pose.pose.position.x = 0.0;
	odom.pose.pose.position.y = 0.0;
	odom.pose.pose.position.z = 0.0;

	odom.pose.pose.orientation.x = 0.0;
	odom.pose.pose.orientation.y = 0.0;
	odom.pose.pose.orientation.z = 0.0;
	odom.pose.pose.orientation.w = 0.0;

	odom.twist.twist.linear.x  = 0.0;
	odom.twist.twist.angular.z = 0.0;
}

bool calcOdometry(double diff_time)
{

	double D_l, D_r;      // rotation value of wheel [rad]
	double delta_s, theta, delta_theta;
	static double last_theta = 0.0;
	double v, w;                  // v = translational velocity [m/s], w = rotational velocity [rad/s]
	double step_time;

	D_l = D_r = 0.0;
	delta_s = delta_theta = theta = 0.0;
	v = w = 0.0;
	step_time = 0.0;

	step_time = diff_time;

	if (step_time == 0)
		return false;

	current_tick[LEFT] = duration1;//- last_tick[LEFT];
	current_tick[RIGHT] = duration3;// - last_tick[RIGHT];
	D_l = TICK2METERS * (double)current_tick[LEFT];
	D_r = TICK2METERS * (double)current_tick[RIGHT];
	test[0] = D_l;
	test[1] = D_r;
	if (isnan(D_l))
		D_l = 0.0;

	if (isnan(D_r))
	    D_r = 0.0;

	delta_s     = (D_r + D_l) / 2.0;
	theta =  (D_r - D_l) / WHEEL_SEPARATION;
	test[2] = theta;

	delta_theta = theta - last_theta;
	test[3] = delta_theta;
	  // compute odometric pose
	odom_pose[0] += delta_s * cos(odom_pose[2]+ (delta_theta / 2.0));
	odom_pose[1] += delta_s * sin(odom_pose[2]+ (delta_theta / 2.0));
	odom_pose[2] += theta;

	  // compute odometric instantaneouse velocity

	v = delta_s / step_time;
	w = theta / step_time;
	angular_vel = w;
	odom_vel[0] = v;
	odom_vel[1] = 0.0;
	odom_vel[2] = w;
	test[0] = v;
	last_velocity[LEFT]  = D_l / step_time;
	last_velocity[RIGHT] = D_r / step_time;
	last_theta = theta;
	test[4] = last_theta;

	last_tick[LEFT]      = duration1;
	last_tick[RIGHT] = duration3;
	duration1 = 0; //without it if trajectory
	duration2 = 0;
	duration3 = 0; //without it if trajectory
	return true;

}
void updateOdometry(void)
{
	odom.header.frame_id = odom_header_frame_id;
	odom.child_frame_id  = odom_child_frame_id;

	odom.pose.pose.position.x = odom_pose[0];
	odom.pose.pose.position.y = odom_pose[1];
	odom.pose.pose.position.z = 0;
	odom.pose.pose.orientation = tf::createQuaternionFromYaw(odom_pose[2]);

	odom.twist.twist.linear.x  = odom_vel[0];
	odom.twist.twist.angular.z = odom_vel[2];
}

void updateTF(geometry_msgs::TransformStamped& odom_tf)
{
	odom_tf.header = odom.header;
	odom_tf.child_frame_id = odom.child_frame_id;
	odom_tf.transform.translation.x = odom.pose.pose.position.x;
	odom_tf.transform.translation.y = odom.pose.pose.position.y;
	odom_tf.transform.translation.z = odom.pose.pose.position.z;
	odom_tf.transform.rotation      = odom.pose.pose.orientation;
}
void updateTFPrefix(bool isConnected)
{
	static bool isChecked = false;
	char log_msg[50];

	if (isConnected)
	{
		if (isChecked == false)
		{
			nh.getParam("~tf_prefix", &get_tf_prefix);

			if (!strcmp(get_tf_prefix, ""))
			{
				sprintf(odom_header_frame_id, "odom");
				sprintf(odom_child_frame_id, "base_footprint");

				sprintf(imu_frame_id, "imu_link");
			}
			else
			{
				strcpy(odom_header_frame_id, get_tf_prefix);
				strcpy(odom_child_frame_id, get_tf_prefix);

				strcpy(imu_frame_id, get_tf_prefix);

				strcat(odom_header_frame_id, "/odom");
				strcat(odom_child_frame_id, "/base_footprint");

				strcat(imu_frame_id, "/imu_link");
			}

			sprintf(log_msg, "Setup TF on Odometry [%s]", odom_header_frame_id);
			nh.loginfo(log_msg);

			sprintf(log_msg, "Setup TF on IMU [%s]", imu_frame_id);
			nh.loginfo(log_msg);

			isChecked = true;
		}
	}
	else
	{
		isChecked = false;
	}
}

void controlMotor(float* value)
{

	float lin_vel = value[LINEAR];
	float ang_vel = value[ANGULAR];


	Input[LEFT] = (double)last_velocity[LEFT];
	Input[RIGHT] = (double)last_velocity[RIGHT];

	myPID_l.Compute();
	myPID_r.Compute();

	md.setM1Speed(-40*Output[RIGHT]);
	md.setM2Speed(40*Output[LEFT]);
}

void debugPublish()
{

	debug_msg.linear.x = Input[LEFT];
	debug_msg.linear.y = duration1;//Setpoint[LEFT];
debug_msg.linear.z =Output[LEFT];

	debug_msg.angular.x=Input[RIGHT];
	debug_msg.angular.y=duration3;//Setpoint[RIGHT];
	debug_msg.angular.z = Output[RIGHT];

	debug_pub.publish(&debug_msg);
}
