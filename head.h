#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "laspack/qmatrix.h"
#include "structs.h"
#include "laspack/itersolv.h"
#include "laspack/errhandl.h"
#include "laspack/rtc.h"
#include <time.h>
#include <unistd.h>
#define STRLEN 1234
#define LEN 1234

#define eps 1e-8
#define EPS 1e-14
#define MAX_ITER 2000
#define OMEGA 1
#define COEF  M_PI

#define LASPACK 1
#define RELEASE 0
#define SOKOLOV 0

/// FOR GNUPLOT
#define FILE_COMMAND "com.txt"
#define FILE_G "g.txt"
#define FILE_V "v.txt"

/// PRINTS
void print_to_file (const char * filename, double *X, double *Y, double * data, int size);
void print_norm_to_file (FILE *fp, int n, int m, double *array);
void print_norms_to_file (const char * filename, int n, int m,
                          double *ncg, double *ncv1, double *ncv2,
                          double *nl2g, double *nl2v1, double *nl2v2, double *nwg, double *nwv1, double *nwv2);

/// NORMS
void Norm_c (int it, int n,
             double *G, double *V1, double *V2, double *X, double *Y, double t,
             double *res_G, double *res_V1, double *res_V2);
void Norm_l2 (int it, int n,
              double *G, double *V1, double *V2, double *X, double *Y, double t,
              double *res_G, double *res_V1, double *res_V2, double h, int *st);
void Norm_Wl2 (int it, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
               double *res_G, double *res_V1, double *res_V2, double h, int *st, int *M0L);

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
double inv_g (double t);
double inv_v1 (double t);

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

/// GNUPLOT
void my_sleep (double c);
void run_gnuplott (void);
void fill_command_file (const char *val_name, P_she *p_s, int time_step,
                        const char *val_path);
void print_paint_pm3d_command (char *path, const char *fname);
void print_paint_vectors_command (char *path, const char *fname);
void print_G_to_file (P_she *p_s, double *X, double *Y, int n, double *val, FILE *fp);
void print_V_to_file (P_she *p_s, double *X, double *Y, int n, double *V1, double *V2, FILE *fp);
void run_gnuplot (P_she *p_s, int time_step, double *X, double *Y, double *G, double *V1, double *V2);
double get_V_x (double x, double y, double h);
double get_V_y (double x, double y, double h);
void clean_png (const char *path);

/// SOKOLOV
void Setka_S (int *st, double *X, double *Y, int *bot, int *top, P_she *p_s);
void Shema_S (double *G, int *st_H, double *X_H, double *Y_H, int *M0L_H, int *M0R_H,
              double *V1, double *V2, int *st, double *X, double *Y, int *M0L, int *M0R,
              P_she *p_s, P_gas *p_d);
int is_zero (double a);
void copy_answer_L_H (Vector *x, double *G, int n);
void copy_answer_L_V (Vector *x, double *V1, double *V2, int n);
void prepare_to_solve_system_L_H (Vector *d, double *G, int n);
void prepare_to_solve_system_L_V (Vector *d, double *V1, double *V2, int n);;
