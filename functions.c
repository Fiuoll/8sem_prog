#include "head.h"

void param_dif (P_gas * p_d)
{
  p_d->Segm_T = 1;
  p_d->Segm_X = COEF;
  p_d->Segm_Y = COEF;
  p_d->p_ro = 1;
  p_d->mu = 0.1;
}

void param_she_step (P_she *p_s, P_gas *p_d, int it_t, int it_sp)
{
  int x, y;
  int init_x = INIT_X;
  int init_y = INIT_X;
  int init_t = INIT_T;
  x = p_s->M_x = init_x * (1 << (it_sp));
  y = p_s->M_y = init_y * (1 << (it_sp));
  p_s->N   = init_t * (1 << (it_t));
  p_s->h_x = p_d->Segm_X / (p_s->M_x - 1);
  p_s->h_y = p_d->Segm_Y / (p_s->M_y - 1);
  p_s->tau = p_d->Segm_T / p_s->N;
  p_s->eta = 1;
  p_s->gamma = 1.4;
  p_s->Dim = (2 * x - 1) *(3 * y - 2) + y * (x - 1);

  if (SOKOLOV)
    p_s->S_DimH = 7 *(x - 1) * (y - 1);
  else
    p_s->S_DimH = 0;


  p_s->nz = 3 * p_s->Dim + 1;
  p_s->nz += (4 + 1 + 2 - 3) * (2 * x - 1 - 2); // status 3
  p_s->nz += (4 + 1 + 1 - 3) * (2 * y - 1 - 1); // status 1
  p_s->nz += (4 + 1 + 1 - 3) * (3 * y - 2 - 1); // status 2
  p_s->nz += (1 + 1 + 1 - 3) * (2);             // status 7
  p_s->nz += (1 + 1 + 1 - 3) * (y);             // status 4
  p_s->nz += (4 + 1 + 1 - 3) * (x - 2);         // status 5
  p_s->nz += (4 + 1 + 1 - 3) * (3 * x - 2 - 2); // status 6
  p_s->nz += (9 + 7 + 7 - 3) * ((2 * x - 1 - 2) * (3 * y - 2 - 2) + (x - 1) * (y - 2)); // status 0

  printf ("Params system: hx = %f, hy = %f, tau = %f\n", p_s->h_x, p_s->h_y, p_s->tau);
}

double inv_g (double t)
{
  (void) t;
  return 1;
}
double inv_v1 (double t)
{
  (void) t;
  return 0.;
}

double sm_g (double t, double x, double y)
{
  if (RELEASE)
    return 1;

//  return cos (x) * sin (y) + t;
  return log ((cos (x) + 1.5) * (sin (y) + 1.5)) + t;
  return log ((cos (2 * x) + 3./2.) * (sin (2 * y) + 3./2.) * exp(t));
}
double sm_vx (double t, double x, double y)
{
  if (RELEASE)
    {
//      return 0;
      if (y > 2 * M_PI)
        return 0.1;
      return 0;
    }

  return sin (x) * sin (y) * exp (t);
}
double sm_vy (double t, double x, double y)
{
  if (RELEASE)
    {
//      return 0;
      if (x < M_PI)
        return 0;
      return -0.1;
    }

  return sin (x) * sin (y) * exp (-t);
}

double dvdy (double t, double x, double y)
{
  if (RELEASE)
    return 0;

  return cos (x) * sin (y) * exp (-t);
}

double dg_dt (double t, double x, double y);
double dg_dt (double t, double x, double y)
{
  (void) t;
  (void) x;
  (void) y;
  return 1;
//  return sm_g (t, x, y);
}

double dg_dx (double t, double x, double y);
double dg_dx (double t, double x, double y)
{
  (void) t;
  return - sin(x) / (cos(x) + 1.5);
//  return - sin (x) * sin (y);
  return 2 * (- sin (2 * x)) * (sin (2 * y) + 1.5) * exp (t);
}

double dg_dy (double t, double x, double y);
double dg_dy (double t, double x, double y)
{
  (void) t;
  return cos(y) / (sin(y) + 1.5);
//  return cos (x) * cos (y);
  return 2 * (cos (2 * x) + 1.5) * (cos (2 * y)) * exp (t);
}

double du1_dt (double t, double x, double y);
double du1_dt (double t, double x, double y)
{
  return sm_vx (t, x, y);
}

double du1_dx (double t, double x, double y);
double du1_dx (double t, double x, double y)
{
  double res = cos (x) * sin (y) * exp (t);
  return res;
}

double du1_dy (double t, double x, double y);
double du1_dy (double t, double x, double y)
{
  double res = sin (x) * cos (y) * exp (t);
  return res;
}

double ddu1_dxdx (double t, double x, double y);
double ddu1_dxdx (double t, double x, double y)
{
  return - sm_vx (t, x, y);
}

double ddu1_dydy (double t, double x, double y);
double ddu1_dydy (double t, double x, double y)
{
  return - sm_vx (t, x, y);
}

double ddu1_dxdy (double t, double x, double y);
double ddu1_dxdy (double t, double x, double y)
{
  return cos (x) * cos (y) * exp (t);
}

double du1u1_dx (double t, double x, double y);
double du1u1_dx (double t, double x, double y)
{
  return 2 * sm_vx (t, x, y) * du1_dx (t, x, y);
}

double du2_dt (double t, double x, double y);
double du2_dt (double t, double x, double y)
{
  return - sm_vy (t, x, y);
}

double du2_dx (double t, double x, double y);
double du2_dx (double t, double x, double y)
{
  double res = cos (x) * sin (y) * exp (-t);
  return res;
}

double du2_dy (double t, double x, double y);
double du2_dy (double t, double x, double y)
{
  double res = sin (x) * cos (y) * exp (-t);
  return res;
}

double ddu2_dxdx (double t, double x, double y);
double ddu2_dxdx (double t, double x, double y)
{
  return - sm_vy (t, x, y);
}

double ddu2_dydy (double t, double x, double y);
double ddu2_dydy (double t, double x, double y)
{
  return - sm_vy (t, x, y);
}

double ddu2_dxdy (double t, double x, double y);
double ddu2_dxdy (double t, double x, double y)
{
  return cos (x) * cos (y) * exp (-t);
}

double du2u2_dy (double t, double x, double y);
double du2u2_dy (double t, double x, double y)
{
  return 2 * sm_vy (t, x, y) * du2_dy (t, x, y);
}

double du1g_dx (double t, double x, double y);
double du1g_dx (double t, double x, double y)
{
  return sm_vx (t, x, y) * dg_dx (t, x, y) + du1_dx (t, x, y) * sm_g (t, x, y);
}

double du2g_dy (double t, double x, double y);
double du2g_dy (double t, double x, double y)
{
  return sm_vy (t, x, y) * dg_dy (t, x, y) + du2_dy (t, x, y) * sm_g (t, x, y);
}

double du1u2_dx (double t, double x, double y);
double du1u2_dx (double t, double x, double y)
{
  return sm_vx (t, x, y) * du2_dx (t, x, y) + du1_dx (t, x, y) * sm_vy (t, x, y);
}

double du1u2_dy (double t, double x, double y);
double du1u2_dy (double t, double x, double y)
{
  return sm_vx (t, x, y) * du2_dy (t, x, y) + du1_dy (t, x, y) * sm_vy (t, x, y);
}
double Func_0 (double t, double x, double y)
{
  if (RELEASE)
    return 0;

  double tmp = 2 - sm_g (t, x, y);
  double res =
    + dg_dt (t, x, y)
    + 0.5 * (
      + sm_vx (t, x, y) * dg_dx (t, x, y)
      + du1g_dx (t, x, y)
      + tmp * du1_dx (t, x, y))
    + 0.5 * (
      + sm_vy (t, x, y) * dg_dy (t, x, y)
      + du2g_dy (t, x, y)
      + tmp * du2_dy (t, x, y));

  return res;
}

double Func_1 (double t, double x, double y, double p_rho, double mu)
{
  if (RELEASE)
    return 0;

  double res =
    + du1_dt (t, x, y)
    + (1. / 3.) * (sm_vx (t, x, y) * du1_dx (t, x, y)
                   + du1u1_dx (t, x, y))
    + (1. / 2.) * (sm_vy (t, x, y) * du1_dy (t, x, y)
                   + du1u2_dy (t, x, y)
                   - sm_vx (t, x, y) * du2_dy (t, x, y))
    + p_rho * dg_dx (t, x, y)
    - (mu / exp (sm_g (t, x, y))) * ((4. / 3.) * ddu1_dxdx (t, x, y)
                                  + ddu1_dydy (t, x, y)
                                   + (1. / 3.) * (ddu2_dxdy (t, x, y)));

  return res;
}

double Func_2 (double t, double x, double y, double p_rho, double mu)
{
  if (RELEASE)
    return 0;

  double res =
      + du2_dt (t, x, y)
      + (1. / 3.) * (sm_vy (t, x, y) * du2_dy (t, x, y)
                     + du2u2_dy (t, x ,y))
      + (1. / 2.) * (sm_vx (t, x, y) * du2_dx (t, x, y)
                     + du1u2_dx (t, x, y)
                     - sm_vy (t, x, y) * du1_dx (t, x, y))
      + p_rho * dg_dy (t, x, y)
      - (mu / exp (sm_g (t, x, y))) * ((4. / 3.) * ddu2_dydy (t, x, y)
                                         + ddu2_dxdx (t, x, y)
                                         + (1. / 3.) * (ddu1_dxdy (t, x, y)));

  return res;
}
