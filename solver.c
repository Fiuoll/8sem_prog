#include "head.h"

void prepare_to_solve_system (double *d, double *G, double *V1, double *V2, int n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      d[3 * i + 0] = G[i];
      d[3 * i + 1] = V1[i];
      d[3 * i + 2] = V2[i];
    }
}
void prepare_to_solve_system_L (Vector *d, double *G, double *V1, double *V2, int n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      V_SetCmp (d, 3 * i + 1,  G[i]);
      V_SetCmp (d, 3 * i + 2, V1[i]);
      V_SetCmp (d, 3 * i + 3, V2[i]);
    }
}
void prepare_to_solve_system_L_V (Vector *d, double *V1, double *V2, int n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      V_SetCmp (d, 2 * i + 1, V1[i]);
      V_SetCmp (d, 2 * i + 2, V2[i]);
    }
}
void prepare_to_solve_system_L_H (Vector *d, double *G, int n)
{
  int i;
  for (i = 0; i < n; i++)
    V_SetCmp (d, i + 1, G[i]);
}
/////////////////////////////////////////////////////////////////////////////
// preconditioner Jacobi
int precond_matrix (int n, double *A, int * I)
{
  double a;
  int i;
  int l;
  int j;
  int ii = I[0];
  int ii2;
  for (i = 0; i < n; i++)
    {
      a = A[i];
      if (fabs (a) < eps)
        {
          printf ("Error! Diagonal element is zero! (%e)\n", a);
          return -1;
        }
      ii2 = I[i + 1];
      l = ii2 - ii;

      for (j = 0; j < l; j++)
        {
          A[ii + j] /= a;
        }
      ii = ii2;
      A[i] = 1;
    }
  return 0;
}
int precond_vector (int n, double *A, double *b, double *res)
{
  double a;
  int i;
  for (i = 0; i < n; i++)
    {
      a = A[i];
      if (fabs (a) < eps)
        {
          printf ("Error! Diagonal element is zero! (%e)\n", a);
          return -1;
        }
      res[i] = b[i] / a;
    }
  return 0;
}
// preconditioner Jacobi
////////////////////////////////////////////////////////////////////////////
int solve_system_BICGSTAB (double *A, int *I, double *b, int n, double *x)
{
  double alpha;
  double omega;
  double denum;
  double beta;
  double resid;
  double b_norm;
  int j = 0;

  double *r = x + n;
  double *p = r + n;
  double *z = p + n;
  double *u = z + n;
  double *s = u + n;
  double *As = s + n;

//  precond_matrix (n, A, I);
//  precond_vector(n, A, b, b);

  b_norm = sqrt (scalar (n, b, b));
  linear_combination (n, A, I, b, x, r, 1);
  copy_vector (n, r, p);

  resid = sqrt (scalar (n, r, r));
  printf ("RESIDUAL %e\n", resid);
  if (resid < eps)
    {
      printf ("Converge! it = %d\n Residual = %e\n", j, resid);
      return 0;
    }

  set_z (n, z);

  for (j = 0; j < MAX_ITER; j++)
    {
      mult_matrix_vector (n, A, I, p, u);
      denum = scalar (n, u, z);
      if (fabs (denum) < EPS)
        {
          printf ("Error: scalar product is zero! 1 (%e)\n", denum);
          return -1;
        }
      alpha = scalar (n, r, z) / denum;
      linear_combination (n, A, I, r, p, s, alpha);

      mult_matrix_vector (n, A, I, s, As);

      denum = scalar (n, As, As);
      if (fabs (denum) < EPS)
        {
          printf ("Error: scalar product is zero! 2 (%e)\n", denum);
          return -1;
        }

      omega = scalar (n, s, As) / denum;

      linear_combination_2 (n, x, alpha, p, omega, s, x);

      denum = scalar (n, r, z);
      if (fabs (denum) < EPS)
        {
          printf ("Error: scalar product is zero! 3 (%e)\n", denum);
          return -1;
        }

      linear_combination (n, A, I, s, s, r, omega);

      resid = sqrt (scalar (n, r, r));
      printf ("RESIDUAL %e\n", resid);
      if (resid / b_norm < eps)
        {
          printf ("Converge! it = %d\n Residual = %e\n", j, resid);
          return 0;
        }

      beta = scalar (n, r, z);

      if (fabs (omega) < EPS)
        {
          printf ("Error: scalar product is zero! 4 (%e)\n", omega);
          return -1;
        }

      beta = beta / denum * alpha / omega;

      linear_combination (n, A, I, p, p, u, omega);

      linear_combination (n, A, I, r, u, p, -beta);

    }

  return 0;
}
void set_zero (int n, double *a)
{
  int i;
  for (i = 0; i < n; i++)
    a[i] = 0.;
}

int solve_system_BICGSTAB_wiki (double *A, int *I, double *b, int n, double *x)
{
  double alpha;
  double omega;
  double beta;
  double rho;
  double rho_k;
  double resid;
  double b_norm;
  int j = 0;

  double *r = x + n;
  double *r_ = r + n;
  double *v = r_ + n;
  double *p = v + n;
  double *s = p + n;
  double *t = s + n;

//  precond_matrix (n, A, I);
//  precond_vector(n, A, b, b);

  b_norm = sqrt (scalar (n, b, b));
  linear_combination (n, A, I, b, x, r, 1);
  copy_vector (n, r, r_);
  rho = alpha = omega = 1;

  resid = sqrt (scalar (n, r, r));
  printf ("RESIDUAL %e\n", resid);
  if (resid < eps)
    {
      printf ("Converge! it = %d\n Residual = %e\n", j, resid);
      return 0;
    }

  set_zero (n, v);
  set_zero (n, p);

  for (j = 0; j < MAX_ITER; j++)
    {
      rho_k = scalar (n, r, r_);

      beta = rho_k / rho * alpha / omega;

      linear_combination_2 (n, p, -omega, v, 0., v, s);
      linear_combination_2 (n, r, beta, s, 0., s, p);

      mult_matrix_vector (n, A, I, p, v);

      alpha = rho_k / (scalar (n, r_, v));

      linear_combination_2 (n, r, -alpha, v, 0., v, s);

      mult_matrix_vector (n, A, I, s, t);

      omega = scalar (n, t, s) / scalar (n, t, t);

      if (omega < 1e-6)
        {
          return j;
        }
      linear_combination_2 (n, x, omega, s, alpha, p, x);
      linear_combination_2 (n, s, -omega, t, 0., t, r);

      resid = sqrt (scalar (n, r, r));
      printf ("RESIDUAL %e\n", resid);
      if (resid / b_norm < eps)
        {
          printf ("Converge! it = %d\n Residual = %e\n", j, resid);
          return 0;
        }
    }

  return 0;
}
////////////////////////////////////////////////////////////////////////////
double scalar (int n, double *a, double *b)
{
  int i;
  double sum = 0.;
  for (i = 0; i < n; i++)
    {
      sum += a[i] * b[i];
    }
  return sum;
}
/////////////////////////////////////////////////////////////////////////////
void mult_matrix_vector (int n, double *A, int *I, double *x, double *res)
{
  int i;
  int j;
  int l;
  int m;
  double sum;

  for (i = 0; i < n; i++)
    {
      m = I[i];
      l = I[i + 1] - m;

      sum = x[i] * A[i];
      for (j = 0; j < l; j++)
        {
          sum += x[I[m + j]] * A[m + j];
          if (fabs (sum) > 1e100)
            {
              printf ("WATAFAK?\n");
            }
        }
      res[i] = sum;
    }
}
///////////////////////////////////////////////////////////////////////////////
void copy_vector (int n, const double *from, double *to)
{
  int i;
  for (i = 0; i < n; i++)
    {
      to[i] = from[i];
    }
}
////////////////////////////////////////////////////////////////////////////////
// res = b - omega * A * c
void linear_combination (int n, double *A, int *I, double *b, double *c, double *res, double omega)
{
  int i;
  int j;
  int l;
  int m;
  double sum;

  for (i = 0; i < n; i++)
    {
      m = I[i];
      l = I[i + 1] - m;

      sum = c[i] * A[i];
      for (j = 0; j < l; j++)
        {
          sum += c[I[m + j]] * A[m + j];
        }
      res[i] = b[i] - omega * sum;
      if (fabs (res[i]) > 1e-15)
        {
          printf ("Problems\n");
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
void set_z (int n, double *z)
{
  int i;
  double q;
  q = sqrt (n);
  for (i = 0; i < n; i++)
    {
        z[i] = 1. / q;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// res = a + alpha * b + omega * c
void linear_combination_2 (int n, double *a, double alpha, double *b, double omega, double *c, double *res)
{
  int i;
  for (i = 0; i < n; i++)
    {
      res[i] = a[i] + alpha * b[i] + omega * c[i];
    }
}
