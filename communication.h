#pragma once

#include <wiringPi.h>
#include <wiringSerial.h>
#include "hc_rasp.h"
#include <Python.h>
#include "cal_control_robust.h"

extern mutex some_mutex;



#define MaxFrameLength	    30			

#define Frame_Header1       0x3A                    
#define Frame_Header2       0x3B   
#define Frame_Tail1         0x7E                    
#define Frame_Tail2         0x7F 

// #define category_sensor     0x73
// #define category_control    0x63
#define control_mode_yaw_robust     0x79
#define control_mode_att_robust     0x61
#define control_mode_depth_robust   0x64

// #define sensor_mode_depth       0x48
#define sensor_mode_pressure    0x50
#define sensor_mode_v           0x56
// #define sensor_mode_vy          0x51
// #define sensor_mode_vz          0x52
// #define sensor_mode_distance    0x53
#define sensor_mode_att         0x41
// #define sensor_mode_pitch       0x55
// #define sensor_mode_yaw         0x56

#define protocol_len 2
#define protocol_payload     5
// #define end_first   9   //
// #define total_bit   11

#define arm         0x0f
#define disarm      0x00
#define turnon      0x80

union hc_sensor
{
    float value;
    unsigned char value_char[4];  
};

union hc_control
{
    float value;
    unsigned char value_char[4];	
};

union tran
{
    float value;
    unsigned char value_char[4];	
};

// extern int hs2_rec;

// extern int snum_rec;                               
// extern int tnum_rec;                               
// extern unsigned char chrtmp_rec[100];                  
// extern int f_h1_flag_rec;                          
// extern int f_h_flag_rec;                           
// extern int f_t1_flag_rec;



