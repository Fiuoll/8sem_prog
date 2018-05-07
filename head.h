#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "laspack/qmatrix.h"
#include "structs.h"
#include "laspack/itersolv.h"
#include "laspack/errhandl.h"
#include "laspack/rtc.h"
#include "time.h"
#define STRLEN 1234
#define LASPACK 1
#define eps 1e-8
#define MAX_ITER 2000
#define OMEGA 1
#define COEF M_PI
#define LEN 1234


/// PRINTS
void print_to_file (const char * filename, double *X, double *Y, double * data, int size);
void print_norm_to_file (FILE *fp, int n, int m, double *array);
void print_norms_to_file (const char * filename, int n, int m,
                          double *ncg, double *ncv1, double *ncv2,
                          double *nl2g, double *nl2v1, double *nl2v2);

/// NORMS
void Norm_c (int it, int n,
             double *G, double *V1, double *V2, double *X, double *Y, double t,
             double *res_G, double *res_V1, double *res_V2);
void Norm_l2 (int it, int n,
              double *G, double *V1, double *V2, double *X, double *Y, double t,
              double *res_G, double *res_V1, double *res_V2);

///SETKA
void set_str (int *st, double *X, double *Y, int *lef, int *rig, int *bot, int *top, P_she *p_s,
              int *i, int st_left_corner, int st_middle, int st_right_corner, int str_len,
              double x_begin, double y_begin, int str_len_top, int str_len_bot);
void fill_1 (int *x, unsigned int n);
void Setka (int *st, double *X, double *Y, int *lef, int *rig, int *bot, int *top, P_she *p_s);

/// functions
void param_dif (P_gas * p_d);
void param_she_step (P_she *p_s, P_gas *p_d, int it_t, int it_sp);
double sm_g (double x, double y, double t);
double sm_vx (double x, double y, double t);
double sm_vy (double x, double y, double t);
double Func_0 (double t, double x, double y);
double Func_1 (double t, double x, double y, double p_rho, double mu);
double Func_2 (double t, double x, double y, double p_rho, double mu);
double dvdy (double t, double x, double y);

///SHEMA
void Shema (double *G, double *V1, double *V2, int *st, double *X, double *Y, int *M0L, int *M0R, P_she *p_s, P_gas *p_d);
