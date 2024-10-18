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
void err_fun(double *nom_x, double *delta_x, double *out_175062233760829800) {
   out_175062233760829800[0] = delta_x[0] + nom_x[0];
   out_175062233760829800[1] = delta_x[1] + nom_x[1];
   out_175062233760829800[2] = delta_x[2] + nom_x[2];
   out_175062233760829800[3] = delta_x[3] + nom_x[3];
   out_175062233760829800[4] = delta_x[4] + nom_x[4];
   out_175062233760829800[5] = delta_x[5] + nom_x[5];
   out_175062233760829800[6] = delta_x[6] + nom_x[6];
   out_175062233760829800[7] = delta_x[7] + nom_x[7];
   out_175062233760829800[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1023813954514447638) {
   out_1023813954514447638[0] = -nom_x[0] + true_x[0];
   out_1023813954514447638[1] = -nom_x[1] + true_x[1];
   out_1023813954514447638[2] = -nom_x[2] + true_x[2];
   out_1023813954514447638[3] = -nom_x[3] + true_x[3];
   out_1023813954514447638[4] = -nom_x[4] + true_x[4];
   out_1023813954514447638[5] = -nom_x[5] + true_x[5];
   out_1023813954514447638[6] = -nom_x[6] + true_x[6];
   out_1023813954514447638[7] = -nom_x[7] + true_x[7];
   out_1023813954514447638[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6061121551881314496) {
   out_6061121551881314496[0] = 1.0;
   out_6061121551881314496[1] = 0;
   out_6061121551881314496[2] = 0;
   out_6061121551881314496[3] = 0;
   out_6061121551881314496[4] = 0;
   out_6061121551881314496[5] = 0;
   out_6061121551881314496[6] = 0;
   out_6061121551881314496[7] = 0;
   out_6061121551881314496[8] = 0;
   out_6061121551881314496[9] = 0;
   out_6061121551881314496[10] = 1.0;
   out_6061121551881314496[11] = 0;
   out_6061121551881314496[12] = 0;
   out_6061121551881314496[13] = 0;
   out_6061121551881314496[14] = 0;
   out_6061121551881314496[15] = 0;
   out_6061121551881314496[16] = 0;
   out_6061121551881314496[17] = 0;
   out_6061121551881314496[18] = 0;
   out_6061121551881314496[19] = 0;
   out_6061121551881314496[20] = 1.0;
   out_6061121551881314496[21] = 0;
   out_6061121551881314496[22] = 0;
   out_6061121551881314496[23] = 0;
   out_6061121551881314496[24] = 0;
   out_6061121551881314496[25] = 0;
   out_6061121551881314496[26] = 0;
   out_6061121551881314496[27] = 0;
   out_6061121551881314496[28] = 0;
   out_6061121551881314496[29] = 0;
   out_6061121551881314496[30] = 1.0;
   out_6061121551881314496[31] = 0;
   out_6061121551881314496[32] = 0;
   out_6061121551881314496[33] = 0;
   out_6061121551881314496[34] = 0;
   out_6061121551881314496[35] = 0;
   out_6061121551881314496[36] = 0;
   out_6061121551881314496[37] = 0;
   out_6061121551881314496[38] = 0;
   out_6061121551881314496[39] = 0;
   out_6061121551881314496[40] = 1.0;
   out_6061121551881314496[41] = 0;
   out_6061121551881314496[42] = 0;
   out_6061121551881314496[43] = 0;
   out_6061121551881314496[44] = 0;
   out_6061121551881314496[45] = 0;
   out_6061121551881314496[46] = 0;
   out_6061121551881314496[47] = 0;
   out_6061121551881314496[48] = 0;
   out_6061121551881314496[49] = 0;
   out_6061121551881314496[50] = 1.0;
   out_6061121551881314496[51] = 0;
   out_6061121551881314496[52] = 0;
   out_6061121551881314496[53] = 0;
   out_6061121551881314496[54] = 0;
   out_6061121551881314496[55] = 0;
   out_6061121551881314496[56] = 0;
   out_6061121551881314496[57] = 0;
   out_6061121551881314496[58] = 0;
   out_6061121551881314496[59] = 0;
   out_6061121551881314496[60] = 1.0;
   out_6061121551881314496[61] = 0;
   out_6061121551881314496[62] = 0;
   out_6061121551881314496[63] = 0;
   out_6061121551881314496[64] = 0;
   out_6061121551881314496[65] = 0;
   out_6061121551881314496[66] = 0;
   out_6061121551881314496[67] = 0;
   out_6061121551881314496[68] = 0;
   out_6061121551881314496[69] = 0;
   out_6061121551881314496[70] = 1.0;
   out_6061121551881314496[71] = 0;
   out_6061121551881314496[72] = 0;
   out_6061121551881314496[73] = 0;
   out_6061121551881314496[74] = 0;
   out_6061121551881314496[75] = 0;
   out_6061121551881314496[76] = 0;
   out_6061121551881314496[77] = 0;
   out_6061121551881314496[78] = 0;
   out_6061121551881314496[79] = 0;
   out_6061121551881314496[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4532091831907629649) {
   out_4532091831907629649[0] = state[0];
   out_4532091831907629649[1] = state[1];
   out_4532091831907629649[2] = state[2];
   out_4532091831907629649[3] = state[3];
   out_4532091831907629649[4] = state[4];
   out_4532091831907629649[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4532091831907629649[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4532091831907629649[7] = state[7];
   out_4532091831907629649[8] = state[8];
}
void F_fun(double *state, double dt, double *out_600891598851444343) {
   out_600891598851444343[0] = 1;
   out_600891598851444343[1] = 0;
   out_600891598851444343[2] = 0;
   out_600891598851444343[3] = 0;
   out_600891598851444343[4] = 0;
   out_600891598851444343[5] = 0;
   out_600891598851444343[6] = 0;
   out_600891598851444343[7] = 0;
   out_600891598851444343[8] = 0;
   out_600891598851444343[9] = 0;
   out_600891598851444343[10] = 1;
   out_600891598851444343[11] = 0;
   out_600891598851444343[12] = 0;
   out_600891598851444343[13] = 0;
   out_600891598851444343[14] = 0;
   out_600891598851444343[15] = 0;
   out_600891598851444343[16] = 0;
   out_600891598851444343[17] = 0;
   out_600891598851444343[18] = 0;
   out_600891598851444343[19] = 0;
   out_600891598851444343[20] = 1;
   out_600891598851444343[21] = 0;
   out_600891598851444343[22] = 0;
   out_600891598851444343[23] = 0;
   out_600891598851444343[24] = 0;
   out_600891598851444343[25] = 0;
   out_600891598851444343[26] = 0;
   out_600891598851444343[27] = 0;
   out_600891598851444343[28] = 0;
   out_600891598851444343[29] = 0;
   out_600891598851444343[30] = 1;
   out_600891598851444343[31] = 0;
   out_600891598851444343[32] = 0;
   out_600891598851444343[33] = 0;
   out_600891598851444343[34] = 0;
   out_600891598851444343[35] = 0;
   out_600891598851444343[36] = 0;
   out_600891598851444343[37] = 0;
   out_600891598851444343[38] = 0;
   out_600891598851444343[39] = 0;
   out_600891598851444343[40] = 1;
   out_600891598851444343[41] = 0;
   out_600891598851444343[42] = 0;
   out_600891598851444343[43] = 0;
   out_600891598851444343[44] = 0;
   out_600891598851444343[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_600891598851444343[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_600891598851444343[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_600891598851444343[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_600891598851444343[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_600891598851444343[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_600891598851444343[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_600891598851444343[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_600891598851444343[53] = -9.8000000000000007*dt;
   out_600891598851444343[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_600891598851444343[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_600891598851444343[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_600891598851444343[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_600891598851444343[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_600891598851444343[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_600891598851444343[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_600891598851444343[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_600891598851444343[62] = 0;
   out_600891598851444343[63] = 0;
   out_600891598851444343[64] = 0;
   out_600891598851444343[65] = 0;
   out_600891598851444343[66] = 0;
   out_600891598851444343[67] = 0;
   out_600891598851444343[68] = 0;
   out_600891598851444343[69] = 0;
   out_600891598851444343[70] = 1;
   out_600891598851444343[71] = 0;
   out_600891598851444343[72] = 0;
   out_600891598851444343[73] = 0;
   out_600891598851444343[74] = 0;
   out_600891598851444343[75] = 0;
   out_600891598851444343[76] = 0;
   out_600891598851444343[77] = 0;
   out_600891598851444343[78] = 0;
   out_600891598851444343[79] = 0;
   out_600891598851444343[80] = 1;
}
void h_25(double *state, double *unused, double *out_1465933540090437536) {
   out_1465933540090437536[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6060839720447098667) {
   out_6060839720447098667[0] = 0;
   out_6060839720447098667[1] = 0;
   out_6060839720447098667[2] = 0;
   out_6060839720447098667[3] = 0;
   out_6060839720447098667[4] = 0;
   out_6060839720447098667[5] = 0;
   out_6060839720447098667[6] = 1;
   out_6060839720447098667[7] = 0;
   out_6060839720447098667[8] = 0;
}
void h_24(double *state, double *unused, double *out_8339032357269173087) {
   out_8339032357269173087[0] = state[4];
   out_8339032357269173087[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3157839167193257724) {
   out_3157839167193257724[0] = 0;
   out_3157839167193257724[1] = 0;
   out_3157839167193257724[2] = 0;
   out_3157839167193257724[3] = 0;
   out_3157839167193257724[4] = 1;
   out_3157839167193257724[5] = 0;
   out_3157839167193257724[6] = 0;
   out_3157839167193257724[7] = 0;
   out_3157839167193257724[8] = 0;
   out_3157839167193257724[9] = 0;
   out_3157839167193257724[10] = 0;
   out_3157839167193257724[11] = 0;
   out_3157839167193257724[12] = 0;
   out_3157839167193257724[13] = 0;
   out_3157839167193257724[14] = 1;
   out_3157839167193257724[15] = 0;
   out_3157839167193257724[16] = 0;
   out_3157839167193257724[17] = 0;
}
void h_30(double *state, double *unused, double *out_5707104254723676519) {
   out_5707104254723676519[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5931500773303858597) {
   out_5931500773303858597[0] = 0;
   out_5931500773303858597[1] = 0;
   out_5931500773303858597[2] = 0;
   out_5931500773303858597[3] = 0;
   out_5931500773303858597[4] = 1;
   out_5931500773303858597[5] = 0;
   out_5931500773303858597[6] = 0;
   out_5931500773303858597[7] = 0;
   out_5931500773303858597[8] = 0;
}
void h_26(double *state, double *unused, double *out_6650614107625338954) {
   out_6650614107625338954[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2319336401573042443) {
   out_2319336401573042443[0] = 0;
   out_2319336401573042443[1] = 0;
   out_2319336401573042443[2] = 0;
   out_2319336401573042443[3] = 0;
   out_2319336401573042443[4] = 0;
   out_2319336401573042443[5] = 0;
   out_2319336401573042443[6] = 0;
   out_2319336401573042443[7] = 1;
   out_2319336401573042443[8] = 0;
}
void h_27(double *state, double *unused, double *out_1570852511353895149) {
   out_1570852511353895149[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3756737461503433686) {
   out_3756737461503433686[0] = 0;
   out_3756737461503433686[1] = 0;
   out_3756737461503433686[2] = 0;
   out_3756737461503433686[3] = 1;
   out_3756737461503433686[4] = 0;
   out_3756737461503433686[5] = 0;
   out_3756737461503433686[6] = 0;
   out_3756737461503433686[7] = 0;
   out_3756737461503433686[8] = 0;
}
void h_29(double *state, double *unused, double *out_1295658449069389260) {
   out_1295658449069389260[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2043374734633882653) {
   out_2043374734633882653[0] = 0;
   out_2043374734633882653[1] = 1;
   out_2043374734633882653[2] = 0;
   out_2043374734633882653[3] = 0;
   out_2043374734633882653[4] = 0;
   out_2043374734633882653[5] = 0;
   out_2043374734633882653[6] = 0;
   out_2043374734633882653[7] = 0;
   out_2043374734633882653[8] = 0;
}
void h_28(double *state, double *unused, double *out_2657579159710359476) {
   out_2657579159710359476[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3039024282435647921) {
   out_3039024282435647921[0] = 1;
   out_3039024282435647921[1] = 0;
   out_3039024282435647921[2] = 0;
   out_3039024282435647921[3] = 0;
   out_3039024282435647921[4] = 0;
   out_3039024282435647921[5] = 0;
   out_3039024282435647921[6] = 0;
   out_3039024282435647921[7] = 0;
   out_3039024282435647921[8] = 0;
}
void h_31(double *state, double *unused, double *out_1924134902248999198) {
   out_1924134902248999198[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6091485682324059095) {
   out_6091485682324059095[0] = 0;
   out_6091485682324059095[1] = 0;
   out_6091485682324059095[2] = 0;
   out_6091485682324059095[3] = 0;
   out_6091485682324059095[4] = 0;
   out_6091485682324059095[5] = 0;
   out_6091485682324059095[6] = 0;
   out_6091485682324059095[7] = 0;
   out_6091485682324059095[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_175062233760829800) {
  err_fun(nom_x, delta_x, out_175062233760829800);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1023813954514447638) {
  inv_err_fun(nom_x, true_x, out_1023813954514447638);
}
void car_H_mod_fun(double *state, double *out_6061121551881314496) {
  H_mod_fun(state, out_6061121551881314496);
}
void car_f_fun(double *state, double dt, double *out_4532091831907629649) {
  f_fun(state,  dt, out_4532091831907629649);
}
void car_F_fun(double *state, double dt, double *out_600891598851444343) {
  F_fun(state,  dt, out_600891598851444343);
}
void car_h_25(double *state, double *unused, double *out_1465933540090437536) {
  h_25(state, unused, out_1465933540090437536);
}
void car_H_25(double *state, double *unused, double *out_6060839720447098667) {
  H_25(state, unused, out_6060839720447098667);
}
void car_h_24(double *state, double *unused, double *out_8339032357269173087) {
  h_24(state, unused, out_8339032357269173087);
}
void car_H_24(double *state, double *unused, double *out_3157839167193257724) {
  H_24(state, unused, out_3157839167193257724);
}
void car_h_30(double *state, double *unused, double *out_5707104254723676519) {
  h_30(state, unused, out_5707104254723676519);
}
void car_H_30(double *state, double *unused, double *out_5931500773303858597) {
  H_30(state, unused, out_5931500773303858597);
}
void car_h_26(double *state, double *unused, double *out_6650614107625338954) {
  h_26(state, unused, out_6650614107625338954);
}
void car_H_26(double *state, double *unused, double *out_2319336401573042443) {
  H_26(state, unused, out_2319336401573042443);
}
void car_h_27(double *state, double *unused, double *out_1570852511353895149) {
  h_27(state, unused, out_1570852511353895149);
}
void car_H_27(double *state, double *unused, double *out_3756737461503433686) {
  H_27(state, unused, out_3756737461503433686);
}
void car_h_29(double *state, double *unused, double *out_1295658449069389260) {
  h_29(state, unused, out_1295658449069389260);
}
void car_H_29(double *state, double *unused, double *out_2043374734633882653) {
  H_29(state, unused, out_2043374734633882653);
}
void car_h_28(double *state, double *unused, double *out_2657579159710359476) {
  h_28(state, unused, out_2657579159710359476);
}
void car_H_28(double *state, double *unused, double *out_3039024282435647921) {
  H_28(state, unused, out_3039024282435647921);
}
void car_h_31(double *state, double *unused, double *out_1924134902248999198) {
  h_31(state, unused, out_1924134902248999198);
}
void car_H_31(double *state, double *unused, double *out_6091485682324059095) {
  H_31(state, unused, out_6091485682324059095);
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
