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
void err_fun(double *nom_x, double *delta_x, double *out_7953529481471973559) {
   out_7953529481471973559[0] = delta_x[0] + nom_x[0];
   out_7953529481471973559[1] = delta_x[1] + nom_x[1];
   out_7953529481471973559[2] = delta_x[2] + nom_x[2];
   out_7953529481471973559[3] = delta_x[3] + nom_x[3];
   out_7953529481471973559[4] = delta_x[4] + nom_x[4];
   out_7953529481471973559[5] = delta_x[5] + nom_x[5];
   out_7953529481471973559[6] = delta_x[6] + nom_x[6];
   out_7953529481471973559[7] = delta_x[7] + nom_x[7];
   out_7953529481471973559[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8561638954627258171) {
   out_8561638954627258171[0] = -nom_x[0] + true_x[0];
   out_8561638954627258171[1] = -nom_x[1] + true_x[1];
   out_8561638954627258171[2] = -nom_x[2] + true_x[2];
   out_8561638954627258171[3] = -nom_x[3] + true_x[3];
   out_8561638954627258171[4] = -nom_x[4] + true_x[4];
   out_8561638954627258171[5] = -nom_x[5] + true_x[5];
   out_8561638954627258171[6] = -nom_x[6] + true_x[6];
   out_8561638954627258171[7] = -nom_x[7] + true_x[7];
   out_8561638954627258171[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3187805969915069940) {
   out_3187805969915069940[0] = 1.0;
   out_3187805969915069940[1] = 0;
   out_3187805969915069940[2] = 0;
   out_3187805969915069940[3] = 0;
   out_3187805969915069940[4] = 0;
   out_3187805969915069940[5] = 0;
   out_3187805969915069940[6] = 0;
   out_3187805969915069940[7] = 0;
   out_3187805969915069940[8] = 0;
   out_3187805969915069940[9] = 0;
   out_3187805969915069940[10] = 1.0;
   out_3187805969915069940[11] = 0;
   out_3187805969915069940[12] = 0;
   out_3187805969915069940[13] = 0;
   out_3187805969915069940[14] = 0;
   out_3187805969915069940[15] = 0;
   out_3187805969915069940[16] = 0;
   out_3187805969915069940[17] = 0;
   out_3187805969915069940[18] = 0;
   out_3187805969915069940[19] = 0;
   out_3187805969915069940[20] = 1.0;
   out_3187805969915069940[21] = 0;
   out_3187805969915069940[22] = 0;
   out_3187805969915069940[23] = 0;
   out_3187805969915069940[24] = 0;
   out_3187805969915069940[25] = 0;
   out_3187805969915069940[26] = 0;
   out_3187805969915069940[27] = 0;
   out_3187805969915069940[28] = 0;
   out_3187805969915069940[29] = 0;
   out_3187805969915069940[30] = 1.0;
   out_3187805969915069940[31] = 0;
   out_3187805969915069940[32] = 0;
   out_3187805969915069940[33] = 0;
   out_3187805969915069940[34] = 0;
   out_3187805969915069940[35] = 0;
   out_3187805969915069940[36] = 0;
   out_3187805969915069940[37] = 0;
   out_3187805969915069940[38] = 0;
   out_3187805969915069940[39] = 0;
   out_3187805969915069940[40] = 1.0;
   out_3187805969915069940[41] = 0;
   out_3187805969915069940[42] = 0;
   out_3187805969915069940[43] = 0;
   out_3187805969915069940[44] = 0;
   out_3187805969915069940[45] = 0;
   out_3187805969915069940[46] = 0;
   out_3187805969915069940[47] = 0;
   out_3187805969915069940[48] = 0;
   out_3187805969915069940[49] = 0;
   out_3187805969915069940[50] = 1.0;
   out_3187805969915069940[51] = 0;
   out_3187805969915069940[52] = 0;
   out_3187805969915069940[53] = 0;
   out_3187805969915069940[54] = 0;
   out_3187805969915069940[55] = 0;
   out_3187805969915069940[56] = 0;
   out_3187805969915069940[57] = 0;
   out_3187805969915069940[58] = 0;
   out_3187805969915069940[59] = 0;
   out_3187805969915069940[60] = 1.0;
   out_3187805969915069940[61] = 0;
   out_3187805969915069940[62] = 0;
   out_3187805969915069940[63] = 0;
   out_3187805969915069940[64] = 0;
   out_3187805969915069940[65] = 0;
   out_3187805969915069940[66] = 0;
   out_3187805969915069940[67] = 0;
   out_3187805969915069940[68] = 0;
   out_3187805969915069940[69] = 0;
   out_3187805969915069940[70] = 1.0;
   out_3187805969915069940[71] = 0;
   out_3187805969915069940[72] = 0;
   out_3187805969915069940[73] = 0;
   out_3187805969915069940[74] = 0;
   out_3187805969915069940[75] = 0;
   out_3187805969915069940[76] = 0;
   out_3187805969915069940[77] = 0;
   out_3187805969915069940[78] = 0;
   out_3187805969915069940[79] = 0;
   out_3187805969915069940[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2523547111431970385) {
   out_2523547111431970385[0] = state[0];
   out_2523547111431970385[1] = state[1];
   out_2523547111431970385[2] = state[2];
   out_2523547111431970385[3] = state[3];
   out_2523547111431970385[4] = state[4];
   out_2523547111431970385[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2523547111431970385[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2523547111431970385[7] = state[7];
   out_2523547111431970385[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8436932558355814908) {
   out_8436932558355814908[0] = 1;
   out_8436932558355814908[1] = 0;
   out_8436932558355814908[2] = 0;
   out_8436932558355814908[3] = 0;
   out_8436932558355814908[4] = 0;
   out_8436932558355814908[5] = 0;
   out_8436932558355814908[6] = 0;
   out_8436932558355814908[7] = 0;
   out_8436932558355814908[8] = 0;
   out_8436932558355814908[9] = 0;
   out_8436932558355814908[10] = 1;
   out_8436932558355814908[11] = 0;
   out_8436932558355814908[12] = 0;
   out_8436932558355814908[13] = 0;
   out_8436932558355814908[14] = 0;
   out_8436932558355814908[15] = 0;
   out_8436932558355814908[16] = 0;
   out_8436932558355814908[17] = 0;
   out_8436932558355814908[18] = 0;
   out_8436932558355814908[19] = 0;
   out_8436932558355814908[20] = 1;
   out_8436932558355814908[21] = 0;
   out_8436932558355814908[22] = 0;
   out_8436932558355814908[23] = 0;
   out_8436932558355814908[24] = 0;
   out_8436932558355814908[25] = 0;
   out_8436932558355814908[26] = 0;
   out_8436932558355814908[27] = 0;
   out_8436932558355814908[28] = 0;
   out_8436932558355814908[29] = 0;
   out_8436932558355814908[30] = 1;
   out_8436932558355814908[31] = 0;
   out_8436932558355814908[32] = 0;
   out_8436932558355814908[33] = 0;
   out_8436932558355814908[34] = 0;
   out_8436932558355814908[35] = 0;
   out_8436932558355814908[36] = 0;
   out_8436932558355814908[37] = 0;
   out_8436932558355814908[38] = 0;
   out_8436932558355814908[39] = 0;
   out_8436932558355814908[40] = 1;
   out_8436932558355814908[41] = 0;
   out_8436932558355814908[42] = 0;
   out_8436932558355814908[43] = 0;
   out_8436932558355814908[44] = 0;
   out_8436932558355814908[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8436932558355814908[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8436932558355814908[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8436932558355814908[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8436932558355814908[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8436932558355814908[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8436932558355814908[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8436932558355814908[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8436932558355814908[53] = -9.8000000000000007*dt;
   out_8436932558355814908[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8436932558355814908[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8436932558355814908[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8436932558355814908[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8436932558355814908[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8436932558355814908[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8436932558355814908[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8436932558355814908[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8436932558355814908[62] = 0;
   out_8436932558355814908[63] = 0;
   out_8436932558355814908[64] = 0;
   out_8436932558355814908[65] = 0;
   out_8436932558355814908[66] = 0;
   out_8436932558355814908[67] = 0;
   out_8436932558355814908[68] = 0;
   out_8436932558355814908[69] = 0;
   out_8436932558355814908[70] = 1;
   out_8436932558355814908[71] = 0;
   out_8436932558355814908[72] = 0;
   out_8436932558355814908[73] = 0;
   out_8436932558355814908[74] = 0;
   out_8436932558355814908[75] = 0;
   out_8436932558355814908[76] = 0;
   out_8436932558355814908[77] = 0;
   out_8436932558355814908[78] = 0;
   out_8436932558355814908[79] = 0;
   out_8436932558355814908[80] = 1;
}
void h_25(double *state, double *unused, double *out_1320688641235206598) {
   out_1320688641235206598[0] = state[6];
}
void H_25(double *state, double *unused, double *out_779577982243876219) {
   out_779577982243876219[0] = 0;
   out_779577982243876219[1] = 0;
   out_779577982243876219[2] = 0;
   out_779577982243876219[3] = 0;
   out_779577982243876219[4] = 0;
   out_779577982243876219[5] = 0;
   out_779577982243876219[6] = 1;
   out_779577982243876219[7] = 0;
   out_779577982243876219[8] = 0;
}
void h_24(double *state, double *unused, double *out_744883210361811476) {
   out_744883210361811476[0] = state[4];
   out_744883210361811476[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1393071616761623347) {
   out_1393071616761623347[0] = 0;
   out_1393071616761623347[1] = 0;
   out_1393071616761623347[2] = 0;
   out_1393071616761623347[3] = 0;
   out_1393071616761623347[4] = 1;
   out_1393071616761623347[5] = 0;
   out_1393071616761623347[6] = 0;
   out_1393071616761623347[7] = 0;
   out_1393071616761623347[8] = 0;
   out_1393071616761623347[9] = 0;
   out_1393071616761623347[10] = 0;
   out_1393071616761623347[11] = 0;
   out_1393071616761623347[12] = 0;
   out_1393071616761623347[13] = 0;
   out_1393071616761623347[14] = 1;
   out_1393071616761623347[15] = 0;
   out_1393071616761623347[16] = 0;
   out_1393071616761623347[17] = 0;
}
void h_30(double *state, double *unused, double *out_4268414631590691559) {
   out_4268414631590691559[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3297910940751124846) {
   out_3297910940751124846[0] = 0;
   out_3297910940751124846[1] = 0;
   out_3297910940751124846[2] = 0;
   out_3297910940751124846[3] = 0;
   out_3297910940751124846[4] = 1;
   out_3297910940751124846[5] = 0;
   out_3297910940751124846[6] = 0;
   out_3297910940751124846[7] = 0;
   out_3297910940751124846[8] = 0;
}
void h_26(double *state, double *unused, double *out_6648586004224909908) {
   out_6648586004224909908[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4084103952004676820) {
   out_4084103952004676820[0] = 0;
   out_4084103952004676820[1] = 0;
   out_4084103952004676820[2] = 0;
   out_4084103952004676820[3] = 0;
   out_4084103952004676820[4] = 0;
   out_4084103952004676820[5] = 0;
   out_4084103952004676820[6] = 0;
   out_4084103952004676820[7] = 1;
   out_4084103952004676820[8] = 0;
}
void h_27(double *state, double *unused, double *out_5473148673880532630) {
   out_5473148673880532630[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5521505011935068063) {
   out_5521505011935068063[0] = 0;
   out_5521505011935068063[1] = 0;
   out_5521505011935068063[2] = 0;
   out_5521505011935068063[3] = 1;
   out_5521505011935068063[4] = 0;
   out_5521505011935068063[5] = 0;
   out_5521505011935068063[6] = 0;
   out_5521505011935068063[7] = 0;
   out_5521505011935068063[8] = 0;
}
void h_29(double *state, double *unused, double *out_4871730516267169076) {
   out_4871730516267169076[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3808142285065517030) {
   out_3808142285065517030[0] = 0;
   out_3808142285065517030[1] = 1;
   out_3808142285065517030[2] = 0;
   out_3808142285065517030[3] = 0;
   out_3808142285065517030[4] = 0;
   out_3808142285065517030[5] = 0;
   out_3808142285065517030[6] = 0;
   out_3808142285065517030[7] = 0;
   out_3808142285065517030[8] = 0;
}
void h_28(double *state, double *unused, double *out_2659607263110788522) {
   out_2659607263110788522[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1274256732004013544) {
   out_1274256732004013544[0] = 1;
   out_1274256732004013544[1] = 0;
   out_1274256732004013544[2] = 0;
   out_1274256732004013544[3] = 0;
   out_1274256732004013544[4] = 0;
   out_1274256732004013544[5] = 0;
   out_1274256732004013544[6] = 0;
   out_1274256732004013544[7] = 0;
   out_1274256732004013544[8] = 0;
}
void h_31(double *state, double *unused, double *out_1045494578950700709) {
   out_1045494578950700709[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3457895849771325344) {
   out_3457895849771325344[0] = 0;
   out_3457895849771325344[1] = 0;
   out_3457895849771325344[2] = 0;
   out_3457895849771325344[3] = 0;
   out_3457895849771325344[4] = 0;
   out_3457895849771325344[5] = 0;
   out_3457895849771325344[6] = 0;
   out_3457895849771325344[7] = 0;
   out_3457895849771325344[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7953529481471973559) {
  err_fun(nom_x, delta_x, out_7953529481471973559);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8561638954627258171) {
  inv_err_fun(nom_x, true_x, out_8561638954627258171);
}
void car_H_mod_fun(double *state, double *out_3187805969915069940) {
  H_mod_fun(state, out_3187805969915069940);
}
void car_f_fun(double *state, double dt, double *out_2523547111431970385) {
  f_fun(state,  dt, out_2523547111431970385);
}
void car_F_fun(double *state, double dt, double *out_8436932558355814908) {
  F_fun(state,  dt, out_8436932558355814908);
}
void car_h_25(double *state, double *unused, double *out_1320688641235206598) {
  h_25(state, unused, out_1320688641235206598);
}
void car_H_25(double *state, double *unused, double *out_779577982243876219) {
  H_25(state, unused, out_779577982243876219);
}
void car_h_24(double *state, double *unused, double *out_744883210361811476) {
  h_24(state, unused, out_744883210361811476);
}
void car_H_24(double *state, double *unused, double *out_1393071616761623347) {
  H_24(state, unused, out_1393071616761623347);
}
void car_h_30(double *state, double *unused, double *out_4268414631590691559) {
  h_30(state, unused, out_4268414631590691559);
}
void car_H_30(double *state, double *unused, double *out_3297910940751124846) {
  H_30(state, unused, out_3297910940751124846);
}
void car_h_26(double *state, double *unused, double *out_6648586004224909908) {
  h_26(state, unused, out_6648586004224909908);
}
void car_H_26(double *state, double *unused, double *out_4084103952004676820) {
  H_26(state, unused, out_4084103952004676820);
}
void car_h_27(double *state, double *unused, double *out_5473148673880532630) {
  h_27(state, unused, out_5473148673880532630);
}
void car_H_27(double *state, double *unused, double *out_5521505011935068063) {
  H_27(state, unused, out_5521505011935068063);
}
void car_h_29(double *state, double *unused, double *out_4871730516267169076) {
  h_29(state, unused, out_4871730516267169076);
}
void car_H_29(double *state, double *unused, double *out_3808142285065517030) {
  H_29(state, unused, out_3808142285065517030);
}
void car_h_28(double *state, double *unused, double *out_2659607263110788522) {
  h_28(state, unused, out_2659607263110788522);
}
void car_H_28(double *state, double *unused, double *out_1274256732004013544) {
  H_28(state, unused, out_1274256732004013544);
}
void car_h_31(double *state, double *unused, double *out_1045494578950700709) {
  h_31(state, unused, out_1045494578950700709);
}
void car_H_31(double *state, double *unused, double *out_3457895849771325344) {
  H_31(state, unused, out_3457895849771325344);
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
