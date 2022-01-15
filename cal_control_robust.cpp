#include "cal_control_robust.h"

Matrix<float,5,5> controller_yaw_AK200;//A discrete 200HZ 
Matrix<float,5,5> controller_depth_AK200;
Matrix<float,5,5> controller_att_AK200;

Matrix<float,5,1> controller_yaw_BK200;//B discrete 200HZ 
Matrix<float,5,1> controller_depth_BK200;
Matrix<float,5,1> controller_att_BK200;

Matrix<float,1,5> controller_yaw_CK200;//C discrete 200HZ 
Matrix<float,1,5> controller_depth_CK200;
Matrix<float,1,5> controller_att_CK200;

Matrix<float,5,1> controller_yaw_Xn;//Xn  
Matrix<float,5,1> controller_depth_Xn;
Matrix<float,5,1> controller_att_Xn;

Matrix<float,5,1> controller_yaw_Xn_1;//Xn 1  
Matrix<float,5,1> controller_depth_Xn_1;
Matrix<float,5,1> controller_att_Xn_1;

float hc_depth_force;
float hc_yaw_force;
float hc_att_force;

float hc_depth_error;
float hc_yaw_error;
float hc_att_error;

void cal_robust_yaw_init()
{
    hc_yaw_force = 0.0;
    hc_yaw_error = 0.0;
    controller_yaw_Xn << 0.0,0.0,0.0,0.0,0.0;
    controller_yaw_Xn_1 << 0.0,0.0,0.0,0.0,0.0;
    controller_yaw_AK200 << 0.9928, -0.0136, 0.0024, -0.0001, 0.0010,
                            -0.0137, 0.9668, 0.0005, 0.0000, -0.0005,
                            0.0025, 0.0017, 0.9974, 0.0001, -0.0029,
                            -0.0003, -0.0003, 0.0001, 1.0000, 0.0020,
                            -0.0107,0.0022, 0.0142, 0.0012 ,-0.0001;
    controller_yaw_BK200 << 0.0038, 0.0047, 0.0030, -0.0002, -0.0163;
    controller_yaw_CK200 << 0.0565, -0.065, -2.4055, 2.0112, -1010.886;
}

void cal_robust_depth_init()
{
    hc_depth_force = 0.0;
    hc_depth_error = 0.0;
    controller_depth_Xn << 0.0,0.0,0.0,0.0,0.0;
    controller_depth_Xn_1 << 0.0,0.0,0.0,0.0,0.0;
    controller_depth_AK200 << 0.9753, -0.0176, -0.0003, 0.0000, 0.0001,
                            -0.0201, 0.9851, 0.0002, -0.0000, -0.0001,
                            -0.0045, 0.0004, 0.9965, 0.0002, 0.0033,
                            0.0008, 0.0002, 0.0003, 1.0000, -0.0010,
                            -0.0195,0.0142, -0.0236, 0.0003 ,-0.0001;
    controller_depth_BK200 << 0.0134, 0.0033, -0.0120, 0.0012, -0.0740;
    controller_depth_CK200 << 0.0327, -0.0851, 3.2437, -1.0094, -982.8664;
}

void cal_robust_att_init()
{
    hc_att_force = 0.0;
    hc_att_error = 0.0;
    controller_att_Xn << 0.0,0.0,0.0,0.0,0.0;
    controller_att_Xn_1 << 0.0,0.0,0.0,0.0,0.0;
    controller_att_AK200 << 1,2,3,4,5,
                            2,3,4,5,6,
                            3,4,5,6,7,
                            4,5,6,7,8,
                            5,6,7,8,9;
    controller_att_BK200 << 1,2,3,4,5;
    controller_att_CK200 << 1,2,3,4,5;
}



float cal_robust_yaw_run()
{   
    controller_yaw_Xn_1 = controller_yaw_AK200 * controller_yaw_Xn + controller_yaw_BK200 * hc_yaw_error;
    hc_yaw_force = controller_yaw_CK200 * controller_yaw_Xn;
    controller_yaw_Xn = controller_yaw_Xn_1;    
    return hc_yaw_force;
}

float cal_robust_depth_run()
{
    controller_depth_Xn_1 = controller_depth_AK200 * controller_depth_Xn + controller_depth_BK200 * hc_depth_error;
    hc_depth_force = controller_depth_CK200 * controller_depth_Xn;
    controller_depth_Xn = controller_depth_Xn_1;    
    return hc_depth_force;
}

float cal_robust_att_run()
{
    // controller_att_Xn_1 = controller_att_AK200 * controller_att_Xn + controller_att_BK200 * hc_att_error;
    controller_att_Xn_1 = controller_att_AK200 * controller_att_Xn + controller_att_BK200 * hc_att_error;
    hc_att_force = controller_att_CK200 * controller_att_Xn;
    controller_att_Xn = controller_att_Xn_1;    
    return hc_att_force;
}





