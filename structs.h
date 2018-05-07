#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
  double Segm_T;
  double Segm_X;
  double Segm_Y;
  double p_ro;
  double mu;
} P_gas;

typedef struct
{
  int M_x;
  int M_y;
  int N;
  int Dim;
  int nz;
  double h_x;
  double h_y;
  double tau;
  double eta;
  double influx_vel;
  double influx_rho;
} P_she;


#endif // STRUCTS_H
