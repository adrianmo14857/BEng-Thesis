/*
 * myTurtlebot_core_config.h
 *
 *  Created on: 2 gru 2019
 *      Author: adrian
 */

#ifndef MYTURTLEBOT_CORE_CONFIG_H_
#define MYTURTLEBOT_CORE_CONFIG_H_

#include "Arduino.h"
#include "DualVNH5019MotorShield.h"
#include "PID_v1.h"
#include "MPU9250.h"
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <stdint.h>

#define CONTROL_MOTOR_SPEED_FREQUENCY          	1000   //hz
#define CONTROL_MOTOR_TIMEOUT                  	500  //ms
#define IMU_PUBLISH_FREQUENCY                  	200  //hz
#define SENSOR_INFO_PUBLISH_FREQUENCY		30 //hz
#define DRIVE_INFORMATION_PUBLISH_FREQUENCY    	200   //hz

#define WHEEL_RADIUS                     0.067
#define TURNING_RADIUS                   0.24
#define WHEEL_SEPARATION				 0.29
#define MAX_LINEAR_VELOCITY              (WHEEL_RADIUS * 2 * 3.14159265359 * 251 / 60)
#define MAX_ANGULAR_VELOCITY             (MAX_LINEAR_VELOCITY / TURNING_RADIUS)

#define MIN_LINEAR_VELOCITY              -MAX_LINEAR_VELOCITY
#define MIN_ANGULAR_VELOCITY             -MAX_ANGULAR_VELOCITY

#define WHEEL_NUM                        2

#define LEFT                             0
#define RIGHT                            1

#define LINEAR                           0
#define ANGULAR                          1

#define DEG2RAD(x)                       (x * 0.01745329252)  // *PI/180
#define RAD2DEG(x)                       (x * 57.2957795131)  // *180/PI

#define TICK2RAD                         0.0089759790 // 2PI/700
#define TICK2METERS						 TICK2RAD*WHEEL_RADIUS



/*******************************************************************************
* Encoder pins
*******************************************************************************/
#define encoder1A 36//A pin PC8
#define encoder1B 35//B pin PC6
#define encoder2A 34//A pin PC5
#define encoder2B 33//B pin PA12
#define encoder3A 41//A pin PB2
#define encoder3B 40//B pin PB1
#define encoder4A 45//A pin PB15 //encoder 4 - damaged
#define encoder4B 39//B pin PC4  //encoder 4 - damaged

/*******************************************************************************
* Functions callback
*******************************************************************************/
void commandVelocityCallback(const geometry_msgs::Twist& cmd_vel_msg);
void matlabVelocityCallback(const geometry_msgs::Twist& mat_vel_msg);
void joyVelocityCallback(const sensor_msgs::Joy& joy_vel_msg);
void pidParamCallback(const std_msgs::Float32MultiArray &pid_param);
/*******************************************************************************
* Functions publish
*******************************************************************************/
void publishImuMsg(void);
void publishOdometry(void);
void publishImuState(void);
void publish_L_EnginesStatus(void);
void publish_R_EnginesStatus(void);
void debugPublish();
/*******************************************************************************
* Functions
*******************************************************************************/
void encoder_init(void);
void wheelSpeed1(void);
void wheelSpeed2(void);
void wheelSpeed3(void);
void wheelSpeed4(void);
void pid_init(void);
void imu_init(void);
void initOdom(void);
void updateTime(void);
ros::Time rosNow(void);
void initOdom(void);
bool calcOdometry(double diff_time);
void updateOdometry(void);
void updateTF(geometry_msgs::TransformStamped& odom_tf);
void updateTFPrefix(bool isConnected);
void controlMotor(float* value);
void setSetpoint();
/*******************************************************************************
* Motor shield variables
*******************************************************************************/
DualVNH5019MotorShield md;

/*******************************************************************************
* Encoder variables
*******************************************************************************/
long int duration1 = 0;//the number of the pulses
long int duration2 = 0;
long int duration3 = 0;
long int duration4 = 0;
int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;
boolean direction1;//the rotation direction
boolean direction2;
boolean direction3;
boolean direction4;
double abs_duration1;
double abs_duration2;
int vel_flag;

/*******************************************************************************
* PID variables
*******************************************************************************/
double Setpoint[WHEEL_NUM], Input[WHEEL_NUM], Output[WHEEL_NUM];
double Kp=1, Ki=60, Kd=0;
PID myPID_l(&Input[LEFT], &Output[LEFT], &Setpoint[LEFT], Kp, Ki, Kd, DIRECT);
PID myPID_r(&Input[RIGHT], &Output[RIGHT], &Setpoint[RIGHT], Kp, Ki, Kd, DIRECT);
/*******************************************************************************
* MPU9250 variables
*******************************************************************************/
int imu_status;
MPU9250 IMU(Wire,0x68);


/*******************************************************************************
* setup variables
*******************************************************************************/
unsigned long prev_update_time;
float odom_pose[3] = {0.0,0.0,0.0};
double odom_vel[3];
boolean setup_end = false;


/*******************************************************************************
* ROS NodeHandle
*******************************************************************************/
ros::NodeHandle nh;

ros::Time current_time;

uint32_t current_offset;

/*******************************************************************************
* Subscriber
*******************************************************************************/
ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", commandVelocityCallback);

ros::Subscriber<sensor_msgs::Joy> joy_vel_sub("joy", joyVelocityCallback);

ros::Subscriber<geometry_msgs::Twist> mat_vel_sub("mat_vel", matlabVelocityCallback);

ros::Subscriber<std_msgs::Float32MultiArray> pid_param_sub("pid_param",pidParamCallback);


/*******************************************************************************
* Publisher
*******************************************************************************/

std_msgs::Int32 imu_state_msg;
ros::Publisher imu_state_pub("imu_state", &imu_state_msg);

//cmd_vel debug
geometry_msgs::Twist debug_msg;
ros::Publisher debug_pub("debug",&debug_msg);

// IMU
sensor_msgs::Imu imu_msg;
ros::Publisher imu_pub("imu", &imu_msg);

// Odometry
nav_msgs::Odometry odom;
ros::Publisher odom_pub("odom", &odom);


std_msgs::Bool l_engines_state_msgs;
ros::Publisher l_engines_state_pub("l_engines_state", &l_engines_state_msgs);

std_msgs::Bool r_engines_state_msgs;
ros::Publisher r_engines_state_pub("r_engines_state", &r_engines_state_msgs);

/*******************************************************************************
* ROS Parameter
*******************************************************************************/

char imu_frame_id[30];
char odom_header_frame_id[30];
char odom_child_frame_id[30];

char get_prefix[10];
char* get_tf_prefix = get_prefix;
/*******************************************************************************
* Transform Broadcaster
*******************************************************************************/
geometry_msgs::TransformStamped odom_tf;
tf::TransformBroadcaster tf_broadcaster;


/*******************************************************************************
* Set velocity
*******************************************************************************/
float goal_velocity[WHEEL_NUM] = {0.0, 0.0};
int32_t joy_button;
float joy_goal_velocity[WHEEL_NUM] = {0.0, 0.0};
float cmd_goal_velocity[WHEEL_NUM] = {0.0, 0.0};
float mat_goal_velocity[WHEEL_NUM] = {0.0, 0.0};
float zero_velocity[WHEEL_NUM] = {0.0, 0.0};
static uint32_t tTime[10];
long int last_tick[WHEEL_NUM] = {0, 0};
double  last_velocity[WHEEL_NUM]  = {0.0, 0.0};
long int current_tick[WHEEL_NUM];
int gain = 0.4;
double angular_vel =0;
double test[5];
#endif /* MYTURTLEBOT_CORE_CONFIG_H_ */
