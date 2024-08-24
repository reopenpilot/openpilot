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
void err_fun(double *nom_x, double *delta_x, double *out_3353002278412945022) {
   out_3353002278412945022[0] = delta_x[0] + nom_x[0];
   out_3353002278412945022[1] = delta_x[1] + nom_x[1];
   out_3353002278412945022[2] = delta_x[2] + nom_x[2];
   out_3353002278412945022[3] = delta_x[3] + nom_x[3];
   out_3353002278412945022[4] = delta_x[4] + nom_x[4];
   out_3353002278412945022[5] = delta_x[5] + nom_x[5];
   out_3353002278412945022[6] = delta_x[6] + nom_x[6];
   out_3353002278412945022[7] = delta_x[7] + nom_x[7];
   out_3353002278412945022[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2772341814008064938) {
   out_2772341814008064938[0] = -nom_x[0] + true_x[0];
   out_2772341814008064938[1] = -nom_x[1] + true_x[1];
   out_2772341814008064938[2] = -nom_x[2] + true_x[2];
   out_2772341814008064938[3] = -nom_x[3] + true_x[3];
   out_2772341814008064938[4] = -nom_x[4] + true_x[4];
   out_2772341814008064938[5] = -nom_x[5] + true_x[5];
   out_2772341814008064938[6] = -nom_x[6] + true_x[6];
   out_2772341814008064938[7] = -nom_x[7] + true_x[7];
   out_2772341814008064938[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1523485746341985353) {
   out_1523485746341985353[0] = 1.0;
   out_1523485746341985353[1] = 0;
   out_1523485746341985353[2] = 0;
   out_1523485746341985353[3] = 0;
   out_1523485746341985353[4] = 0;
   out_1523485746341985353[5] = 0;
   out_1523485746341985353[6] = 0;
   out_1523485746341985353[7] = 0;
   out_1523485746341985353[8] = 0;
   out_1523485746341985353[9] = 0;
   out_1523485746341985353[10] = 1.0;
   out_1523485746341985353[11] = 0;
   out_1523485746341985353[12] = 0;
   out_1523485746341985353[13] = 0;
   out_1523485746341985353[14] = 0;
   out_1523485746341985353[15] = 0;
   out_1523485746341985353[16] = 0;
   out_1523485746341985353[17] = 0;
   out_1523485746341985353[18] = 0;
   out_1523485746341985353[19] = 0;
   out_1523485746341985353[20] = 1.0;
   out_1523485746341985353[21] = 0;
   out_1523485746341985353[22] = 0;
   out_1523485746341985353[23] = 0;
   out_1523485746341985353[24] = 0;
   out_1523485746341985353[25] = 0;
   out_1523485746341985353[26] = 0;
   out_1523485746341985353[27] = 0;
   out_1523485746341985353[28] = 0;
   out_1523485746341985353[29] = 0;
   out_1523485746341985353[30] = 1.0;
   out_1523485746341985353[31] = 0;
   out_1523485746341985353[32] = 0;
   out_1523485746341985353[33] = 0;
   out_1523485746341985353[34] = 0;
   out_1523485746341985353[35] = 0;
   out_1523485746341985353[36] = 0;
   out_1523485746341985353[37] = 0;
   out_1523485746341985353[38] = 0;
   out_1523485746341985353[39] = 0;
   out_1523485746341985353[40] = 1.0;
   out_1523485746341985353[41] = 0;
   out_1523485746341985353[42] = 0;
   out_1523485746341985353[43] = 0;
   out_1523485746341985353[44] = 0;
   out_1523485746341985353[45] = 0;
   out_1523485746341985353[46] = 0;
   out_1523485746341985353[47] = 0;
   out_1523485746341985353[48] = 0;
   out_1523485746341985353[49] = 0;
   out_1523485746341985353[50] = 1.0;
   out_1523485746341985353[51] = 0;
   out_1523485746341985353[52] = 0;
   out_1523485746341985353[53] = 0;
   out_1523485746341985353[54] = 0;
   out_1523485746341985353[55] = 0;
   out_1523485746341985353[56] = 0;
   out_1523485746341985353[57] = 0;
   out_1523485746341985353[58] = 0;
   out_1523485746341985353[59] = 0;
   out_1523485746341985353[60] = 1.0;
   out_1523485746341985353[61] = 0;
   out_1523485746341985353[62] = 0;
   out_1523485746341985353[63] = 0;
   out_1523485746341985353[64] = 0;
   out_1523485746341985353[65] = 0;
   out_1523485746341985353[66] = 0;
   out_1523485746341985353[67] = 0;
   out_1523485746341985353[68] = 0;
   out_1523485746341985353[69] = 0;
   out_1523485746341985353[70] = 1.0;
   out_1523485746341985353[71] = 0;
   out_1523485746341985353[72] = 0;
   out_1523485746341985353[73] = 0;
   out_1523485746341985353[74] = 0;
   out_1523485746341985353[75] = 0;
   out_1523485746341985353[76] = 0;
   out_1523485746341985353[77] = 0;
   out_1523485746341985353[78] = 0;
   out_1523485746341985353[79] = 0;
   out_1523485746341985353[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6342725627414992683) {
   out_6342725627414992683[0] = state[0];
   out_6342725627414992683[1] = state[1];
   out_6342725627414992683[2] = state[2];
   out_6342725627414992683[3] = state[3];
   out_6342725627414992683[4] = state[4];
   out_6342725627414992683[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6342725627414992683[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6342725627414992683[7] = state[7];
   out_6342725627414992683[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6523969226365794498) {
   out_6523969226365794498[0] = 1;
   out_6523969226365794498[1] = 0;
   out_6523969226365794498[2] = 0;
   out_6523969226365794498[3] = 0;
   out_6523969226365794498[4] = 0;
   out_6523969226365794498[5] = 0;
   out_6523969226365794498[6] = 0;
   out_6523969226365794498[7] = 0;
   out_6523969226365794498[8] = 0;
   out_6523969226365794498[9] = 0;
   out_6523969226365794498[10] = 1;
   out_6523969226365794498[11] = 0;
   out_6523969226365794498[12] = 0;
   out_6523969226365794498[13] = 0;
   out_6523969226365794498[14] = 0;
   out_6523969226365794498[15] = 0;
   out_6523969226365794498[16] = 0;
   out_6523969226365794498[17] = 0;
   out_6523969226365794498[18] = 0;
   out_6523969226365794498[19] = 0;
   out_6523969226365794498[20] = 1;
   out_6523969226365794498[21] = 0;
   out_6523969226365794498[22] = 0;
   out_6523969226365794498[23] = 0;
   out_6523969226365794498[24] = 0;
   out_6523969226365794498[25] = 0;
   out_6523969226365794498[26] = 0;
   out_6523969226365794498[27] = 0;
   out_6523969226365794498[28] = 0;
   out_6523969226365794498[29] = 0;
   out_6523969226365794498[30] = 1;
   out_6523969226365794498[31] = 0;
   out_6523969226365794498[32] = 0;
   out_6523969226365794498[33] = 0;
   out_6523969226365794498[34] = 0;
   out_6523969226365794498[35] = 0;
   out_6523969226365794498[36] = 0;
   out_6523969226365794498[37] = 0;
   out_6523969226365794498[38] = 0;
   out_6523969226365794498[39] = 0;
   out_6523969226365794498[40] = 1;
   out_6523969226365794498[41] = 0;
   out_6523969226365794498[42] = 0;
   out_6523969226365794498[43] = 0;
   out_6523969226365794498[44] = 0;
   out_6523969226365794498[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6523969226365794498[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6523969226365794498[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6523969226365794498[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6523969226365794498[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6523969226365794498[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6523969226365794498[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6523969226365794498[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6523969226365794498[53] = -9.8000000000000007*dt;
   out_6523969226365794498[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6523969226365794498[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6523969226365794498[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6523969226365794498[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6523969226365794498[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6523969226365794498[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6523969226365794498[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6523969226365794498[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6523969226365794498[62] = 0;
   out_6523969226365794498[63] = 0;
   out_6523969226365794498[64] = 0;
   out_6523969226365794498[65] = 0;
   out_6523969226365794498[66] = 0;
   out_6523969226365794498[67] = 0;
   out_6523969226365794498[68] = 0;
   out_6523969226365794498[69] = 0;
   out_6523969226365794498[70] = 1;
   out_6523969226365794498[71] = 0;
   out_6523969226365794498[72] = 0;
   out_6523969226365794498[73] = 0;
   out_6523969226365794498[74] = 0;
   out_6523969226365794498[75] = 0;
   out_6523969226365794498[76] = 0;
   out_6523969226365794498[77] = 0;
   out_6523969226365794498[78] = 0;
   out_6523969226365794498[79] = 0;
   out_6523969226365794498[80] = 1;
}
void h_25(double *state, double *unused, double *out_6530117229475646868) {
   out_6530117229475646868[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8463324805531082462) {
   out_8463324805531082462[0] = 0;
   out_8463324805531082462[1] = 0;
   out_8463324805531082462[2] = 0;
   out_8463324805531082462[3] = 0;
   out_8463324805531082462[4] = 0;
   out_8463324805531082462[5] = 0;
   out_8463324805531082462[6] = 1;
   out_8463324805531082462[7] = 0;
   out_8463324805531082462[8] = 0;
}
void h_24(double *state, double *unused, double *out_1130170633536611674) {
   out_1130170633536611674[0] = state[4];
   out_1130170633536611674[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2565027634501542261) {
   out_2565027634501542261[0] = 0;
   out_2565027634501542261[1] = 0;
   out_2565027634501542261[2] = 0;
   out_2565027634501542261[3] = 0;
   out_2565027634501542261[4] = 1;
   out_2565027634501542261[5] = 0;
   out_2565027634501542261[6] = 0;
   out_2565027634501542261[7] = 0;
   out_2565027634501542261[8] = 0;
   out_2565027634501542261[9] = 0;
   out_2565027634501542261[10] = 0;
   out_2565027634501542261[11] = 0;
   out_2565027634501542261[12] = 0;
   out_2565027634501542261[13] = 0;
   out_2565027634501542261[14] = 1;
   out_2565027634501542261[15] = 0;
   out_2565027634501542261[16] = 0;
   out_2565027634501542261[17] = 0;
}
void h_30(double *state, double *unused, double *out_8172950761738779840) {
   out_8172950761738779840[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8333985858387842392) {
   out_8333985858387842392[0] = 0;
   out_8333985858387842392[1] = 0;
   out_8333985858387842392[2] = 0;
   out_8333985858387842392[3] = 0;
   out_8333985858387842392[4] = 1;
   out_8333985858387842392[5] = 0;
   out_8333985858387842392[6] = 0;
   out_8333985858387842392[7] = 0;
   out_8333985858387842392[8] = 0;
}
void h_26(double *state, double *unused, double *out_3874751794556922630) {
   out_3874751794556922630[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4721821486657026238) {
   out_4721821486657026238[0] = 0;
   out_4721821486657026238[1] = 0;
   out_4721821486657026238[2] = 0;
   out_4721821486657026238[3] = 0;
   out_4721821486657026238[4] = 0;
   out_4721821486657026238[5] = 0;
   out_4721821486657026238[6] = 0;
   out_4721821486657026238[7] = 1;
   out_4721821486657026238[8] = 0;
}
void h_27(double *state, double *unused, double *out_6954246846552611516) {
   out_6954246846552611516[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6159222546587417481) {
   out_6159222546587417481[0] = 0;
   out_6159222546587417481[1] = 0;
   out_6159222546587417481[2] = 0;
   out_6159222546587417481[3] = 1;
   out_6159222546587417481[4] = 0;
   out_6159222546587417481[5] = 0;
   out_6159222546587417481[6] = 0;
   out_6159222546587417481[7] = 0;
   out_6159222546587417481[8] = 0;
}
void h_29(double *state, double *unused, double *out_4406829492715335639) {
   out_4406829492715335639[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4445859819717866448) {
   out_4445859819717866448[0] = 0;
   out_4445859819717866448[1] = 1;
   out_4445859819717866448[2] = 0;
   out_4445859819717866448[3] = 0;
   out_4445859819717866448[4] = 0;
   out_4445859819717866448[5] = 0;
   out_4445859819717866448[6] = 0;
   out_4445859819717866448[7] = 0;
   out_4445859819717866448[8] = 0;
}
void h_28(double *state, double *unused, double *out_4349841525743913865) {
   out_4349841525743913865[0] = state[0];
}
void H_28(double *state, double *unused, double *out_636539197351664126) {
   out_636539197351664126[0] = 1;
   out_636539197351664126[1] = 0;
   out_636539197351664126[2] = 0;
   out_636539197351664126[3] = 0;
   out_636539197351664126[4] = 0;
   out_636539197351664126[5] = 0;
   out_636539197351664126[6] = 0;
   out_636539197351664126[7] = 0;
   out_636539197351664126[8] = 0;
}
void h_31(double *state, double *unused, double *out_1684875949362256479) {
   out_1684875949362256479[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8493970767408042890) {
   out_8493970767408042890[0] = 0;
   out_8493970767408042890[1] = 0;
   out_8493970767408042890[2] = 0;
   out_8493970767408042890[3] = 0;
   out_8493970767408042890[4] = 0;
   out_8493970767408042890[5] = 0;
   out_8493970767408042890[6] = 0;
   out_8493970767408042890[7] = 0;
   out_8493970767408042890[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3353002278412945022) {
  err_fun(nom_x, delta_x, out_3353002278412945022);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2772341814008064938) {
  inv_err_fun(nom_x, true_x, out_2772341814008064938);
}
void car_H_mod_fun(double *state, double *out_1523485746341985353) {
  H_mod_fun(state, out_1523485746341985353);
}
void car_f_fun(double *state, double dt, double *out_6342725627414992683) {
  f_fun(state,  dt, out_6342725627414992683);
}
void car_F_fun(double *state, double dt, double *out_6523969226365794498) {
  F_fun(state,  dt, out_6523969226365794498);
}
void car_h_25(double *state, double *unused, double *out_6530117229475646868) {
  h_25(state, unused, out_6530117229475646868);
}
void car_H_25(double *state, double *unused, double *out_8463324805531082462) {
  H_25(state, unused, out_8463324805531082462);
}
void car_h_24(double *state, double *unused, double *out_1130170633536611674) {
  h_24(state, unused, out_1130170633536611674);
}
void car_H_24(double *state, double *unused, double *out_2565027634501542261) {
  H_24(state, unused, out_2565027634501542261);
}
void car_h_30(double *state, double *unused, double *out_8172950761738779840) {
  h_30(state, unused, out_8172950761738779840);
}
void car_H_30(double *state, double *unused, double *out_8333985858387842392) {
  H_30(state, unused, out_8333985858387842392);
}
void car_h_26(double *state, double *unused, double *out_3874751794556922630) {
  h_26(state, unused, out_3874751794556922630);
}
void car_H_26(double *state, double *unused, double *out_4721821486657026238) {
  H_26(state, unused, out_4721821486657026238);
}
void car_h_27(double *state, double *unused, double *out_6954246846552611516) {
  h_27(state, unused, out_6954246846552611516);
}
void car_H_27(double *state, double *unused, double *out_6159222546587417481) {
  H_27(state, unused, out_6159222546587417481);
}
void car_h_29(double *state, double *unused, double *out_4406829492715335639) {
  h_29(state, unused, out_4406829492715335639);
}
void car_H_29(double *state, double *unused, double *out_4445859819717866448) {
  H_29(state, unused, out_4445859819717866448);
}
void car_h_28(double *state, double *unused, double *out_4349841525743913865) {
  h_28(state, unused, out_4349841525743913865);
}
void car_H_28(double *state, double *unused, double *out_636539197351664126) {
  H_28(state, unused, out_636539197351664126);
}
void car_h_31(double *state, double *unused, double *out_1684875949362256479) {
  h_31(state, unused, out_1684875949362256479);
}
void car_H_31(double *state, double *unused, double *out_8493970767408042890) {
  H_31(state, unused, out_8493970767408042890);
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
