#pragma once

#include</home/pi/FXC/Eigen/Core>  //Matrix and Array classes, basic linear algebra (including triangular and selfadjoint products), array manipulation
// #include</home/pi/FXC/Eigen/Dense> //Includes Core, Geometry, LU, Cholesky, SVD, QR, and Eigenvalues header files
#include "hc_rasp.h"
// #include"communication.h"
using namespace Eigen;
using namespace std;

void cal_robust_yaw_init();
void cal_robust_depth_init();
void cal_robust_att_init();
float cal_robust_yaw_run();
float cal_robust_depth_run();
float cal_robust_att_run();

