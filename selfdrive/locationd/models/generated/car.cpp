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
void err_fun(double *nom_x, double *delta_x, double *out_8163086174142454753) {
   out_8163086174142454753[0] = delta_x[0] + nom_x[0];
   out_8163086174142454753[1] = delta_x[1] + nom_x[1];
   out_8163086174142454753[2] = delta_x[2] + nom_x[2];
   out_8163086174142454753[3] = delta_x[3] + nom_x[3];
   out_8163086174142454753[4] = delta_x[4] + nom_x[4];
   out_8163086174142454753[5] = delta_x[5] + nom_x[5];
   out_8163086174142454753[6] = delta_x[6] + nom_x[6];
   out_8163086174142454753[7] = delta_x[7] + nom_x[7];
   out_8163086174142454753[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7477760585665234547) {
   out_7477760585665234547[0] = -nom_x[0] + true_x[0];
   out_7477760585665234547[1] = -nom_x[1] + true_x[1];
   out_7477760585665234547[2] = -nom_x[2] + true_x[2];
   out_7477760585665234547[3] = -nom_x[3] + true_x[3];
   out_7477760585665234547[4] = -nom_x[4] + true_x[4];
   out_7477760585665234547[5] = -nom_x[5] + true_x[5];
   out_7477760585665234547[6] = -nom_x[6] + true_x[6];
   out_7477760585665234547[7] = -nom_x[7] + true_x[7];
   out_7477760585665234547[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5986426489713363296) {
   out_5986426489713363296[0] = 1.0;
   out_5986426489713363296[1] = 0;
   out_5986426489713363296[2] = 0;
   out_5986426489713363296[3] = 0;
   out_5986426489713363296[4] = 0;
   out_5986426489713363296[5] = 0;
   out_5986426489713363296[6] = 0;
   out_5986426489713363296[7] = 0;
   out_5986426489713363296[8] = 0;
   out_5986426489713363296[9] = 0;
   out_5986426489713363296[10] = 1.0;
   out_5986426489713363296[11] = 0;
   out_5986426489713363296[12] = 0;
   out_5986426489713363296[13] = 0;
   out_5986426489713363296[14] = 0;
   out_5986426489713363296[15] = 0;
   out_5986426489713363296[16] = 0;
   out_5986426489713363296[17] = 0;
   out_5986426489713363296[18] = 0;
   out_5986426489713363296[19] = 0;
   out_5986426489713363296[20] = 1.0;
   out_5986426489713363296[21] = 0;
   out_5986426489713363296[22] = 0;
   out_5986426489713363296[23] = 0;
   out_5986426489713363296[24] = 0;
   out_5986426489713363296[25] = 0;
   out_5986426489713363296[26] = 0;
   out_5986426489713363296[27] = 0;
   out_5986426489713363296[28] = 0;
   out_5986426489713363296[29] = 0;
   out_5986426489713363296[30] = 1.0;
   out_5986426489713363296[31] = 0;
   out_5986426489713363296[32] = 0;
   out_5986426489713363296[33] = 0;
   out_5986426489713363296[34] = 0;
   out_5986426489713363296[35] = 0;
   out_5986426489713363296[36] = 0;
   out_5986426489713363296[37] = 0;
   out_5986426489713363296[38] = 0;
   out_5986426489713363296[39] = 0;
   out_5986426489713363296[40] = 1.0;
   out_5986426489713363296[41] = 0;
   out_5986426489713363296[42] = 0;
   out_5986426489713363296[43] = 0;
   out_5986426489713363296[44] = 0;
   out_5986426489713363296[45] = 0;
   out_5986426489713363296[46] = 0;
   out_5986426489713363296[47] = 0;
   out_5986426489713363296[48] = 0;
   out_5986426489713363296[49] = 0;
   out_5986426489713363296[50] = 1.0;
   out_5986426489713363296[51] = 0;
   out_5986426489713363296[52] = 0;
   out_5986426489713363296[53] = 0;
   out_5986426489713363296[54] = 0;
   out_5986426489713363296[55] = 0;
   out_5986426489713363296[56] = 0;
   out_5986426489713363296[57] = 0;
   out_5986426489713363296[58] = 0;
   out_5986426489713363296[59] = 0;
   out_5986426489713363296[60] = 1.0;
   out_5986426489713363296[61] = 0;
   out_5986426489713363296[62] = 0;
   out_5986426489713363296[63] = 0;
   out_5986426489713363296[64] = 0;
   out_5986426489713363296[65] = 0;
   out_5986426489713363296[66] = 0;
   out_5986426489713363296[67] = 0;
   out_5986426489713363296[68] = 0;
   out_5986426489713363296[69] = 0;
   out_5986426489713363296[70] = 1.0;
   out_5986426489713363296[71] = 0;
   out_5986426489713363296[72] = 0;
   out_5986426489713363296[73] = 0;
   out_5986426489713363296[74] = 0;
   out_5986426489713363296[75] = 0;
   out_5986426489713363296[76] = 0;
   out_5986426489713363296[77] = 0;
   out_5986426489713363296[78] = 0;
   out_5986426489713363296[79] = 0;
   out_5986426489713363296[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2329993318510941356) {
   out_2329993318510941356[0] = state[0];
   out_2329993318510941356[1] = state[1];
   out_2329993318510941356[2] = state[2];
   out_2329993318510941356[3] = state[3];
   out_2329993318510941356[4] = state[4];
   out_2329993318510941356[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2329993318510941356[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2329993318510941356[7] = state[7];
   out_2329993318510941356[8] = state[8];
}
void F_fun(double *state, double dt, double *out_595541159135160017) {
   out_595541159135160017[0] = 1;
   out_595541159135160017[1] = 0;
   out_595541159135160017[2] = 0;
   out_595541159135160017[3] = 0;
   out_595541159135160017[4] = 0;
   out_595541159135160017[5] = 0;
   out_595541159135160017[6] = 0;
   out_595541159135160017[7] = 0;
   out_595541159135160017[8] = 0;
   out_595541159135160017[9] = 0;
   out_595541159135160017[10] = 1;
   out_595541159135160017[11] = 0;
   out_595541159135160017[12] = 0;
   out_595541159135160017[13] = 0;
   out_595541159135160017[14] = 0;
   out_595541159135160017[15] = 0;
   out_595541159135160017[16] = 0;
   out_595541159135160017[17] = 0;
   out_595541159135160017[18] = 0;
   out_595541159135160017[19] = 0;
   out_595541159135160017[20] = 1;
   out_595541159135160017[21] = 0;
   out_595541159135160017[22] = 0;
   out_595541159135160017[23] = 0;
   out_595541159135160017[24] = 0;
   out_595541159135160017[25] = 0;
   out_595541159135160017[26] = 0;
   out_595541159135160017[27] = 0;
   out_595541159135160017[28] = 0;
   out_595541159135160017[29] = 0;
   out_595541159135160017[30] = 1;
   out_595541159135160017[31] = 0;
   out_595541159135160017[32] = 0;
   out_595541159135160017[33] = 0;
   out_595541159135160017[34] = 0;
   out_595541159135160017[35] = 0;
   out_595541159135160017[36] = 0;
   out_595541159135160017[37] = 0;
   out_595541159135160017[38] = 0;
   out_595541159135160017[39] = 0;
   out_595541159135160017[40] = 1;
   out_595541159135160017[41] = 0;
   out_595541159135160017[42] = 0;
   out_595541159135160017[43] = 0;
   out_595541159135160017[44] = 0;
   out_595541159135160017[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_595541159135160017[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_595541159135160017[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_595541159135160017[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_595541159135160017[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_595541159135160017[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_595541159135160017[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_595541159135160017[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_595541159135160017[53] = -9.8000000000000007*dt;
   out_595541159135160017[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_595541159135160017[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_595541159135160017[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_595541159135160017[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_595541159135160017[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_595541159135160017[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_595541159135160017[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_595541159135160017[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_595541159135160017[62] = 0;
   out_595541159135160017[63] = 0;
   out_595541159135160017[64] = 0;
   out_595541159135160017[65] = 0;
   out_595541159135160017[66] = 0;
   out_595541159135160017[67] = 0;
   out_595541159135160017[68] = 0;
   out_595541159135160017[69] = 0;
   out_595541159135160017[70] = 1;
   out_595541159135160017[71] = 0;
   out_595541159135160017[72] = 0;
   out_595541159135160017[73] = 0;
   out_595541159135160017[74] = 0;
   out_595541159135160017[75] = 0;
   out_595541159135160017[76] = 0;
   out_595541159135160017[77] = 0;
   out_595541159135160017[78] = 0;
   out_595541159135160017[79] = 0;
   out_595541159135160017[80] = 1;
}
void h_25(double *state, double *unused, double *out_6264512820833169783) {
   out_6264512820833169783[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7182703864182213592) {
   out_7182703864182213592[0] = 0;
   out_7182703864182213592[1] = 0;
   out_7182703864182213592[2] = 0;
   out_7182703864182213592[3] = 0;
   out_7182703864182213592[4] = 0;
   out_7182703864182213592[5] = 0;
   out_7182703864182213592[6] = 1;
   out_7182703864182213592[7] = 0;
   out_7182703864182213592[8] = 0;
}
void h_24(double *state, double *unused, double *out_7209438580732961695) {
   out_7209438580732961695[0] = state[4];
   out_7209438580732961695[1] = state[5];
}
void H_24(double *state, double *unused, double *out_9038332425548469462) {
   out_9038332425548469462[0] = 0;
   out_9038332425548469462[1] = 0;
   out_9038332425548469462[2] = 0;
   out_9038332425548469462[3] = 0;
   out_9038332425548469462[4] = 1;
   out_9038332425548469462[5] = 0;
   out_9038332425548469462[6] = 0;
   out_9038332425548469462[7] = 0;
   out_9038332425548469462[8] = 0;
   out_9038332425548469462[9] = 0;
   out_9038332425548469462[10] = 0;
   out_9038332425548469462[11] = 0;
   out_9038332425548469462[12] = 0;
   out_9038332425548469462[13] = 0;
   out_9038332425548469462[14] = 1;
   out_9038332425548469462[15] = 0;
   out_9038332425548469462[16] = 0;
   out_9038332425548469462[17] = 0;
}
void h_30(double *state, double *unused, double *out_6421699489184298928) {
   out_6421699489184298928[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4347349868035721269) {
   out_4347349868035721269[0] = 0;
   out_4347349868035721269[1] = 0;
   out_4347349868035721269[2] = 0;
   out_4347349868035721269[3] = 0;
   out_4347349868035721269[4] = 1;
   out_4347349868035721269[5] = 0;
   out_4347349868035721269[6] = 0;
   out_4347349868035721269[7] = 0;
   out_4347349868035721269[8] = 0;
}
void h_26(double *state, double *unused, double *out_22657971770449782) {
   out_22657971770449782[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3441200545308157368) {
   out_3441200545308157368[0] = 0;
   out_3441200545308157368[1] = 0;
   out_3441200545308157368[2] = 0;
   out_3441200545308157368[3] = 0;
   out_3441200545308157368[4] = 0;
   out_3441200545308157368[5] = 0;
   out_3441200545308157368[6] = 0;
   out_3441200545308157368[7] = 1;
   out_3441200545308157368[8] = 0;
}
void h_27(double *state, double *unused, double *out_8885181194169795075) {
   out_8885181194169795075[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6522113179836146180) {
   out_6522113179836146180[0] = 0;
   out_6522113179836146180[1] = 0;
   out_6522113179836146180[2] = 0;
   out_6522113179836146180[3] = 1;
   out_6522113179836146180[4] = 0;
   out_6522113179836146180[5] = 0;
   out_6522113179836146180[6] = 0;
   out_6522113179836146180[7] = 0;
   out_6522113179836146180[8] = 0;
}
void h_29(double *state, double *unused, double *out_7589443290260440665) {
   out_7589443290260440665[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3837118523721329085) {
   out_3837118523721329085[0] = 0;
   out_3837118523721329085[1] = 1;
   out_3837118523721329085[2] = 0;
   out_3837118523721329085[3] = 0;
   out_3837118523721329085[4] = 0;
   out_3837118523721329085[5] = 0;
   out_3837118523721329085[6] = 0;
   out_3837118523721329085[7] = 0;
   out_3837118523721329085[8] = 0;
}
void h_28(double *state, double *unused, double *out_8201935348530386713) {
   out_8201935348530386713[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8919517540790859659) {
   out_8919517540790859659[0] = 1;
   out_8919517540790859659[1] = 0;
   out_8919517540790859659[2] = 0;
   out_8919517540790859659[3] = 0;
   out_8919517540790859659[4] = 0;
   out_8919517540790859659[5] = 0;
   out_8919517540790859659[6] = 0;
   out_8919517540790859659[7] = 0;
   out_8919517540790859659[8] = 0;
}
void h_31(double *state, double *unused, double *out_5096563518434777372) {
   out_5096563518434777372[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7213349826059174020) {
   out_7213349826059174020[0] = 0;
   out_7213349826059174020[1] = 0;
   out_7213349826059174020[2] = 0;
   out_7213349826059174020[3] = 0;
   out_7213349826059174020[4] = 0;
   out_7213349826059174020[5] = 0;
   out_7213349826059174020[6] = 0;
   out_7213349826059174020[7] = 0;
   out_7213349826059174020[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8163086174142454753) {
  err_fun(nom_x, delta_x, out_8163086174142454753);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7477760585665234547) {
  inv_err_fun(nom_x, true_x, out_7477760585665234547);
}
void car_H_mod_fun(double *state, double *out_5986426489713363296) {
  H_mod_fun(state, out_5986426489713363296);
}
void car_f_fun(double *state, double dt, double *out_2329993318510941356) {
  f_fun(state,  dt, out_2329993318510941356);
}
void car_F_fun(double *state, double dt, double *out_595541159135160017) {
  F_fun(state,  dt, out_595541159135160017);
}
void car_h_25(double *state, double *unused, double *out_6264512820833169783) {
  h_25(state, unused, out_6264512820833169783);
}
void car_H_25(double *state, double *unused, double *out_7182703864182213592) {
  H_25(state, unused, out_7182703864182213592);
}
void car_h_24(double *state, double *unused, double *out_7209438580732961695) {
  h_24(state, unused, out_7209438580732961695);
}
void car_H_24(double *state, double *unused, double *out_9038332425548469462) {
  H_24(state, unused, out_9038332425548469462);
}
void car_h_30(double *state, double *unused, double *out_6421699489184298928) {
  h_30(state, unused, out_6421699489184298928);
}
void car_H_30(double *state, double *unused, double *out_4347349868035721269) {
  H_30(state, unused, out_4347349868035721269);
}
void car_h_26(double *state, double *unused, double *out_22657971770449782) {
  h_26(state, unused, out_22657971770449782);
}
void car_H_26(double *state, double *unused, double *out_3441200545308157368) {
  H_26(state, unused, out_3441200545308157368);
}
void car_h_27(double *state, double *unused, double *out_8885181194169795075) {
  h_27(state, unused, out_8885181194169795075);
}
void car_H_27(double *state, double *unused, double *out_6522113179836146180) {
  H_27(state, unused, out_6522113179836146180);
}
void car_h_29(double *state, double *unused, double *out_7589443290260440665) {
  h_29(state, unused, out_7589443290260440665);
}
void car_H_29(double *state, double *unused, double *out_3837118523721329085) {
  H_29(state, unused, out_3837118523721329085);
}
void car_h_28(double *state, double *unused, double *out_8201935348530386713) {
  h_28(state, unused, out_8201935348530386713);
}
void car_H_28(double *state, double *unused, double *out_8919517540790859659) {
  H_28(state, unused, out_8919517540790859659);
}
void car_h_31(double *state, double *unused, double *out_5096563518434777372) {
  h_31(state, unused, out_5096563518434777372);
}
void car_H_31(double *state, double *unused, double *out_7213349826059174020) {
  H_31(state, unused, out_7213349826059174020);
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
