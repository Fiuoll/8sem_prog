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
  int j = 0;

  double *r = x + n;
  double *p = r + n;
  double *z = p + n;
  double *u = z + n;
  double *s = u + n;
  double *As = s + n;

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
      if (resid < eps)
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
  double sum;

  for (i = 0; i < n; i++)
    {
      l = I[i + 1] - I[i];

      sum = 0.;
      for (j = 0; j < l; j++)
        {
          sum += x[i] * A[I[I[i] + j]];
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
  double sum;

  for (i = 0; i < n; i++)
    {
      l = I[i + 1] - I[i];

      sum = 0.;
      for (j = 0; j < l; j++)
        {
          sum += c[i] * A[I[I[i] + j]];
        }
      res[i] = b[i] - omega * sum;
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
