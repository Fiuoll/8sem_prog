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
#define EPS 1e-16
#define MAX_ITER 2000
#define OMEGA 1
#define COEF  M_PI
#define LEN 1234
#define RELEASE 0

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
              double *res_G, double *res_V1, double *res_V2, double h, int *st);

///SETKA
void set_str (int *st, double *X, double *Y, int *bot, int *top, P_she *p_s,
              int *i, int st_left_corner, int st_middle, int st_right_corner, int str_len,
              double x_begin, double y_begin, int str_len_top, int str_len_bot);
void fill_1 (int *x, unsigned int n);
void Setka (int *st, double *X, double *Y, int *bot, int *top, P_she *p_s);

/// functions
void correct_array (int n, double *a);
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
double min (double *array, int n);
void copy_answer_L (Vector *x, double *G, double *V1, double *V2, P_she *p_s);
void Shema (double *G, double *V1, double *V2, int *st, double *X, double *Y, int *M0L, int *M0R, P_she *p_s, P_gas *p_d);

/// SOLVER
void prepare_to_solve_system_L (Vector *d, double *G, double *V1, double *V2, int n);
void set_zero (int n, double *a);
void copy_answer (double *x, double *G, double *V1, double *V2, P_she *p_s);
void prepare_to_solve_system (double *d, double *G, double *V1, double *V2, int n);
int precond_matrix (int n, double *A, int * I);
int precond_vector (int n, double *A, double *b, double *res);
void linear_combination_2 (int n, double *a, double alpha, double *b, double omega, double *c, double *res);
void set_z (int n, double *z);
void linear_combination (int n, double *A, int *I, double *b, double *c, double *res, double omega);
void copy_vector (int n, const double *from, double *to);
void mult_matrix_vector (int n, double *A, int *I, double *x, double *res);
double scalar (int n, double *a, double *b);
int solve_system_BICGSTAB (double *A, int *I, double *b, int n, double *x);

int solve_system_BICGSTAB_wiki (double *A, int *I, double *b, int n, double *x);
