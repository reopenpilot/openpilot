#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3449015484705141339) {
   out_3449015484705141339[0] = delta_x[0] + nom_x[0];
   out_3449015484705141339[1] = delta_x[1] + nom_x[1];
   out_3449015484705141339[2] = delta_x[2] + nom_x[2];
   out_3449015484705141339[3] = delta_x[3] + nom_x[3];
   out_3449015484705141339[4] = delta_x[4] + nom_x[4];
   out_3449015484705141339[5] = delta_x[5] + nom_x[5];
   out_3449015484705141339[6] = delta_x[6] + nom_x[6];
   out_3449015484705141339[7] = delta_x[7] + nom_x[7];
   out_3449015484705141339[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6783754562235548925) {
   out_6783754562235548925[0] = -nom_x[0] + true_x[0];
   out_6783754562235548925[1] = -nom_x[1] + true_x[1];
   out_6783754562235548925[2] = -nom_x[2] + true_x[2];
   out_6783754562235548925[3] = -nom_x[3] + true_x[3];
   out_6783754562235548925[4] = -nom_x[4] + true_x[4];
   out_6783754562235548925[5] = -nom_x[5] + true_x[5];
   out_6783754562235548925[6] = -nom_x[6] + true_x[6];
   out_6783754562235548925[7] = -nom_x[7] + true_x[7];
   out_6783754562235548925[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1094567786311116382) {
   out_1094567786311116382[0] = 1.0;
   out_1094567786311116382[1] = 0;
   out_1094567786311116382[2] = 0;
   out_1094567786311116382[3] = 0;
   out_1094567786311116382[4] = 0;
   out_1094567786311116382[5] = 0;
   out_1094567786311116382[6] = 0;
   out_1094567786311116382[7] = 0;
   out_1094567786311116382[8] = 0;
   out_1094567786311116382[9] = 0;
   out_1094567786311116382[10] = 1.0;
   out_1094567786311116382[11] = 0;
   out_1094567786311116382[12] = 0;
   out_1094567786311116382[13] = 0;
   out_1094567786311116382[14] = 0;
   out_1094567786311116382[15] = 0;
   out_1094567786311116382[16] = 0;
   out_1094567786311116382[17] = 0;
   out_1094567786311116382[18] = 0;
   out_1094567786311116382[19] = 0;
   out_1094567786311116382[20] = 1.0;
   out_1094567786311116382[21] = 0;
   out_1094567786311116382[22] = 0;
   out_1094567786311116382[23] = 0;
   out_1094567786311116382[24] = 0;
   out_1094567786311116382[25] = 0;
   out_1094567786311116382[26] = 0;
   out_1094567786311116382[27] = 0;
   out_1094567786311116382[28] = 0;
   out_1094567786311116382[29] = 0;
   out_1094567786311116382[30] = 1.0;
   out_1094567786311116382[31] = 0;
   out_1094567786311116382[32] = 0;
   out_1094567786311116382[33] = 0;
   out_1094567786311116382[34] = 0;
   out_1094567786311116382[35] = 0;
   out_1094567786311116382[36] = 0;
   out_1094567786311116382[37] = 0;
   out_1094567786311116382[38] = 0;
   out_1094567786311116382[39] = 0;
   out_1094567786311116382[40] = 1.0;
   out_1094567786311116382[41] = 0;
   out_1094567786311116382[42] = 0;
   out_1094567786311116382[43] = 0;
   out_1094567786311116382[44] = 0;
   out_1094567786311116382[45] = 0;
   out_1094567786311116382[46] = 0;
   out_1094567786311116382[47] = 0;
   out_1094567786311116382[48] = 0;
   out_1094567786311116382[49] = 0;
   out_1094567786311116382[50] = 1.0;
   out_1094567786311116382[51] = 0;
   out_1094567786311116382[52] = 0;
   out_1094567786311116382[53] = 0;
   out_1094567786311116382[54] = 0;
   out_1094567786311116382[55] = 0;
   out_1094567786311116382[56] = 0;
   out_1094567786311116382[57] = 0;
   out_1094567786311116382[58] = 0;
   out_1094567786311116382[59] = 0;
   out_1094567786311116382[60] = 1.0;
   out_1094567786311116382[61] = 0;
   out_1094567786311116382[62] = 0;
   out_1094567786311116382[63] = 0;
   out_1094567786311116382[64] = 0;
   out_1094567786311116382[65] = 0;
   out_1094567786311116382[66] = 0;
   out_1094567786311116382[67] = 0;
   out_1094567786311116382[68] = 0;
   out_1094567786311116382[69] = 0;
   out_1094567786311116382[70] = 1.0;
   out_1094567786311116382[71] = 0;
   out_1094567786311116382[72] = 0;
   out_1094567786311116382[73] = 0;
   out_1094567786311116382[74] = 0;
   out_1094567786311116382[75] = 0;
   out_1094567786311116382[76] = 0;
   out_1094567786311116382[77] = 0;
   out_1094567786311116382[78] = 0;
   out_1094567786311116382[79] = 0;
   out_1094567786311116382[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2340345652924283988) {
   out_2340345652924283988[0] = state[0];
   out_2340345652924283988[1] = state[1];
   out_2340345652924283988[2] = state[2];
   out_2340345652924283988[3] = state[3];
   out_2340345652924283988[4] = state[4];
   out_2340345652924283988[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2340345652924283988[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2340345652924283988[7] = state[7];
   out_2340345652924283988[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8115241479432949281) {
   out_8115241479432949281[0] = 1;
   out_8115241479432949281[1] = 0;
   out_8115241479432949281[2] = 0;
   out_8115241479432949281[3] = 0;
   out_8115241479432949281[4] = 0;
   out_8115241479432949281[5] = 0;
   out_8115241479432949281[6] = 0;
   out_8115241479432949281[7] = 0;
   out_8115241479432949281[8] = 0;
   out_8115241479432949281[9] = 0;
   out_8115241479432949281[10] = 1;
   out_8115241479432949281[11] = 0;
   out_8115241479432949281[12] = 0;
   out_8115241479432949281[13] = 0;
   out_8115241479432949281[14] = 0;
   out_8115241479432949281[15] = 0;
   out_8115241479432949281[16] = 0;
   out_8115241479432949281[17] = 0;
   out_8115241479432949281[18] = 0;
   out_8115241479432949281[19] = 0;
   out_8115241479432949281[20] = 1;
   out_8115241479432949281[21] = 0;
   out_8115241479432949281[22] = 0;
   out_8115241479432949281[23] = 0;
   out_8115241479432949281[24] = 0;
   out_8115241479432949281[25] = 0;
   out_8115241479432949281[26] = 0;
   out_8115241479432949281[27] = 0;
   out_8115241479432949281[28] = 0;
   out_8115241479432949281[29] = 0;
   out_8115241479432949281[30] = 1;
   out_8115241479432949281[31] = 0;
   out_8115241479432949281[32] = 0;
   out_8115241479432949281[33] = 0;
   out_8115241479432949281[34] = 0;
   out_8115241479432949281[35] = 0;
   out_8115241479432949281[36] = 0;
   out_8115241479432949281[37] = 0;
   out_8115241479432949281[38] = 0;
   out_8115241479432949281[39] = 0;
   out_8115241479432949281[40] = 1;
   out_8115241479432949281[41] = 0;
   out_8115241479432949281[42] = 0;
   out_8115241479432949281[43] = 0;
   out_8115241479432949281[44] = 0;
   out_8115241479432949281[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8115241479432949281[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8115241479432949281[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8115241479432949281[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8115241479432949281[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8115241479432949281[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8115241479432949281[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8115241479432949281[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8115241479432949281[53] = -9.8000000000000007*dt;
   out_8115241479432949281[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8115241479432949281[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8115241479432949281[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8115241479432949281[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8115241479432949281[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8115241479432949281[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8115241479432949281[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8115241479432949281[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8115241479432949281[62] = 0;
   out_8115241479432949281[63] = 0;
   out_8115241479432949281[64] = 0;
   out_8115241479432949281[65] = 0;
   out_8115241479432949281[66] = 0;
   out_8115241479432949281[67] = 0;
   out_8115241479432949281[68] = 0;
   out_8115241479432949281[69] = 0;
   out_8115241479432949281[70] = 1;
   out_8115241479432949281[71] = 0;
   out_8115241479432949281[72] = 0;
   out_8115241479432949281[73] = 0;
   out_8115241479432949281[74] = 0;
   out_8115241479432949281[75] = 0;
   out_8115241479432949281[76] = 0;
   out_8115241479432949281[77] = 0;
   out_8115241479432949281[78] = 0;
   out_8115241479432949281[79] = 0;
   out_8115241479432949281[80] = 1;
}
void h_25(double *state, double *unused, double *out_968310111308185806) {
   out_968310111308185806[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7490357294405748927) {
   out_7490357294405748927[0] = 0;
   out_7490357294405748927[1] = 0;
   out_7490357294405748927[2] = 0;
   out_7490357294405748927[3] = 0;
   out_7490357294405748927[4] = 0;
   out_7490357294405748927[5] = 0;
   out_7490357294405748927[6] = 1;
   out_7490357294405748927[7] = 0;
   out_7490357294405748927[8] = 0;
}
void h_24(double *state, double *unused, double *out_4932127618924512192) {
   out_4932127618924512192[0] = state[4];
   out_4932127618924512192[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6136065274647814426) {
   out_6136065274647814426[0] = 0;
   out_6136065274647814426[1] = 0;
   out_6136065274647814426[2] = 0;
   out_6136065274647814426[3] = 0;
   out_6136065274647814426[4] = 1;
   out_6136065274647814426[5] = 0;
   out_6136065274647814426[6] = 0;
   out_6136065274647814426[7] = 0;
   out_6136065274647814426[8] = 0;
   out_6136065274647814426[9] = 0;
   out_6136065274647814426[10] = 0;
   out_6136065274647814426[11] = 0;
   out_6136065274647814426[12] = 0;
   out_6136065274647814426[13] = 0;
   out_6136065274647814426[14] = 1;
   out_6136065274647814426[15] = 0;
   out_6136065274647814426[16] = 0;
   out_6136065274647814426[17] = 0;
}
void h_30(double *state, double *unused, double *out_8731575368128858247) {
   out_8731575368128858247[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7619696241548988997) {
   out_7619696241548988997[0] = 0;
   out_7619696241548988997[1] = 0;
   out_7619696241548988997[2] = 0;
   out_7619696241548988997[3] = 0;
   out_7619696241548988997[4] = 1;
   out_7619696241548988997[5] = 0;
   out_7619696241548988997[6] = 0;
   out_7619696241548988997[7] = 0;
   out_7619696241548988997[8] = 0;
}
void h_26(double *state, double *unused, double *out_1495171593677310341) {
   out_1495171593677310341[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6833503230295437023) {
   out_6833503230295437023[0] = 0;
   out_6833503230295437023[1] = 0;
   out_6833503230295437023[2] = 0;
   out_6833503230295437023[3] = 0;
   out_6833503230295437023[4] = 0;
   out_6833503230295437023[5] = 0;
   out_6833503230295437023[6] = 0;
   out_6833503230295437023[7] = 1;
   out_6833503230295437023[8] = 0;
}
void h_27(double *state, double *unused, double *out_2327937642317555634) {
   out_2327937642317555634[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8652284520360137708) {
   out_8652284520360137708[0] = 0;
   out_8652284520360137708[1] = 0;
   out_8652284520360137708[2] = 0;
   out_8652284520360137708[3] = 1;
   out_8652284520360137708[4] = 0;
   out_8652284520360137708[5] = 0;
   out_8652284520360137708[6] = 0;
   out_8652284520360137708[7] = 0;
   out_8652284520360137708[8] = 0;
}
void h_29(double *state, double *unused, double *out_3729902100468012602) {
   out_3729902100468012602[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7109464897234596813) {
   out_7109464897234596813[0] = 0;
   out_7109464897234596813[1] = 1;
   out_7109464897234596813[2] = 0;
   out_7109464897234596813[3] = 0;
   out_7109464897234596813[4] = 0;
   out_7109464897234596813[5] = 0;
   out_7109464897234596813[6] = 0;
   out_7109464897234596813[7] = 0;
   out_7109464897234596813[8] = 0;
}
void h_28(double *state, double *unused, double *out_6609501483561216142) {
   out_6609501483561216142[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6254880159405424229) {
   out_6254880159405424229[0] = 1;
   out_6254880159405424229[1] = 0;
   out_6254880159405424229[2] = 0;
   out_6254880159405424229[3] = 0;
   out_6254880159405424229[4] = 0;
   out_6254880159405424229[5] = 0;
   out_6254880159405424229[6] = 0;
   out_6254880159405424229[7] = 0;
   out_6254880159405424229[8] = 0;
}
void h_31(double *state, double *unused, double *out_510108749149624144) {
   out_510108749149624144[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7459711332528788499) {
   out_7459711332528788499[0] = 0;
   out_7459711332528788499[1] = 0;
   out_7459711332528788499[2] = 0;
   out_7459711332528788499[3] = 0;
   out_7459711332528788499[4] = 0;
   out_7459711332528788499[5] = 0;
   out_7459711332528788499[6] = 0;
   out_7459711332528788499[7] = 0;
   out_7459711332528788499[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3449015484705141339) {
  err_fun(nom_x, delta_x, out_3449015484705141339);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6783754562235548925) {
  inv_err_fun(nom_x, true_x, out_6783754562235548925);
}
void car_H_mod_fun(double *state, double *out_1094567786311116382) {
  H_mod_fun(state, out_1094567786311116382);
}
void car_f_fun(double *state, double dt, double *out_2340345652924283988) {
  f_fun(state,  dt, out_2340345652924283988);
}
void car_F_fun(double *state, double dt, double *out_8115241479432949281) {
  F_fun(state,  dt, out_8115241479432949281);
}
void car_h_25(double *state, double *unused, double *out_968310111308185806) {
  h_25(state, unused, out_968310111308185806);
}
void car_H_25(double *state, double *unused, double *out_7490357294405748927) {
  H_25(state, unused, out_7490357294405748927);
}
void car_h_24(double *state, double *unused, double *out_4932127618924512192) {
  h_24(state, unused, out_4932127618924512192);
}
void car_H_24(double *state, double *unused, double *out_6136065274647814426) {
  H_24(state, unused, out_6136065274647814426);
}
void car_h_30(double *state, double *unused, double *out_8731575368128858247) {
  h_30(state, unused, out_8731575368128858247);
}
void car_H_30(double *state, double *unused, double *out_7619696241548988997) {
  H_30(state, unused, out_7619696241548988997);
}
void car_h_26(double *state, double *unused, double *out_1495171593677310341) {
  h_26(state, unused, out_1495171593677310341);
}
void car_H_26(double *state, double *unused, double *out_6833503230295437023) {
  H_26(state, unused, out_6833503230295437023);
}
void car_h_27(double *state, double *unused, double *out_2327937642317555634) {
  h_27(state, unused, out_2327937642317555634);
}
void car_H_27(double *state, double *unused, double *out_8652284520360137708) {
  H_27(state, unused, out_8652284520360137708);
}
void car_h_29(double *state, double *unused, double *out_3729902100468012602) {
  h_29(state, unused, out_3729902100468012602);
}
void car_H_29(double *state, double *unused, double *out_7109464897234596813) {
  H_29(state, unused, out_7109464897234596813);
}
void car_h_28(double *state, double *unused, double *out_6609501483561216142) {
  h_28(state, unused, out_6609501483561216142);
}
void car_H_28(double *state, double *unused, double *out_6254880159405424229) {
  H_28(state, unused, out_6254880159405424229);
}
void car_h_31(double *state, double *unused, double *out_510108749149624144) {
  h_31(state, unused, out_510108749149624144);
}
void car_H_31(double *state, double *unused, double *out_7459711332528788499) {
  H_31(state, unused, out_7459711332528788499);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
