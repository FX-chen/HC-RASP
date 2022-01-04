#pragma once

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <string>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <condition_variable>
#include <unistd.h>
using namespace std;

extern bool sensor_switch;
extern bool ms5837_state;
extern bool dvl_v_state;
extern bool dvl_p_state;

extern float ms5837_pressure;
extern float ms5837_temperature;

extern float hc_depth_force;
extern float hc_yaw_force;
extern float hc_att_force;

extern float hc_depth_error;
extern float hc_yaw_error;
extern float hc_att_error;

extern float hc_depth_from_pix;
extern float hc_att_from_pix;
extern float hc_yaw_from_pix;

extern float hc_depth_from_rasp;
extern float hc_att_from_rasp;
extern float hc_yaw_from_rasp;

extern deque<vector<unsigned char>> process_deque;

extern mutex deque_mutex;

extern float att[3];
extern float velocity_and_distance[4];
void cal_robust_yaw_init();
void cal_robust_depth_hold_init();
void cal_robust_att_init();

float cal_robust_yaw_run();
float cal_robust_depth_hold_run();
float cal_robust_att_run();

void dvlA50_pos_data_python2cpp();
void dvlA50_vel_data_python2cpp();
void ms5837_data_python2cpp();

void send_to_deque(float *, int , int , int );
void send_to_pixhawk();
void ms5837_data_connect();
void receive_from_pixhawk_init();
void receive_from_pixhawk();

// enum pixhawk_mode{

// };
