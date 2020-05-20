#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-01-10 17:07:17

#include "Arduino.h"
#include "myTurtlebot_core_config.h"

void setup() ;
void loop() ;
void setSetpoint() ;
void encoder_init(void) ;
void wheelSpeed1(void) ;
void wheelSpeed2(void) ;
void wheelSpeed3(void) ;
void wheelSpeed4(void) ;
void pid_init(void) ;
void imu_init(void) ;
void updateTime(void) ;
void publishImuMsg(void) ;
void publishOdometry(void) ;
void publishImuState(void) ;
void publish_L_EnginesStatus(void) ;
void publish_R_EnginesStatus(void) ;
void initOdom(void) ;
bool calcOdometry(double diff_time) ;
void updateOdometry(void) ;
void updateTFPrefix(bool isConnected) ;
void controlMotor(float* value) ;
void debugPublish() ;

#include "myTurtlebot_core.ino"


#endif
