#include "head.h"
double min (double *array, int n)
{
  double min;
  int i;

  min = array[0];
  for (i = 1; i < n; i++)
    {
      if (min > array[i])
        min = array[i];
    }
  return min;
}
void copy_answer_L (Vector *x, double *G, double *V1, double *V2, P_she *p_s)
{
  unsigned int k;
  int i;
  for (i = 0; i < p_s->Dim; i++)
    {
      k = 3 * (unsigned int)i + 1;
      G[i] = V_GetCmp (x, k);
      V1[i] = V_GetCmp (x, k + 1);
      V2[i] = V_GetCmp (x, k + 2);
    }
}
void copy_answer (double *x, double *G, double *V1, double *V2, P_she *p_s)
{
  int i;
  for (i = 0; i < p_s->Dim; i++)
    {
      G[i] = x[3 * i];
      V1[i] = x[3 * i + 1];
      V2[i] = x[3 * i + 2];
    }
}


void Shema (double *G, double *V1, double *V2, int *st, double *X, double *Y, int *M0L, int *M0R, P_she *p_s, P_gas *p_d)
{
  int timestep;
  int n, nz, k;
  int i;
  QMatrix_L A;
  Vector b;
  Vector x;
  double *matrix;
  int    *ind;
  double *rhs;
  double *d;
#include"./include/perem.c"

  n = p_s->Dim;
  nz = p_s->nz;
  mu = p_d->mu;
  pressure = p_d->p_ro;
  hx = p_s->h_x;
  hy = p_s->h_y;
  tau = p_s->tau;
if (LASPACK)
  {
    Q_Constr (&A, "A", 3 * n, False, Rowws, Normal, True);
    V_Constr (&b, "b", 3 * n, Normal, True);
    V_Constr (&x, "x", 3 * n, Normal, True);
    SetRTCAccuracy (eps);
  }
else
  {
    matrix = (double *) malloc (nz * sizeof (double));
    ind    = (int *) malloc (nz * sizeof (int));
    rhs    = (double *) malloc (3 * n * sizeof (double));
    d      = (double *) malloc (7 * (3 * n) * sizeof (double));
  }

#include"./include/viraj.c"
#include"./include/nachal.c"

printf ("Computing...\n");
if (RELEASE)
  {
    run_gnuplot (p_s, 0, X, Y, G, V1, V2);
  }

  for (timestep = 1; timestep < p_s->N; timestep++)
    {
      if (p_s->N > 10 && timestep % (p_s->N / 10) == 0)
        printf ("|");
#include"./include/mum.c"
      tt = timestep * tau;
      for (i = 0, mm = LASPACK, k = 3 * n + 1; i < n; i++, mm++)
        {
#include"./include/nodeparam.c"
          if (LASPACK)
            {
#include"./include/case0_L.c"
#include"./include/case1_L.c"
#include"./include/case2_L.c"
#include"./include/case3_L.c"
#include"./include/case4_L.c"
#include"./include/case5_L.c"
#include"./include/case6_L.c"
#include"./include/case7_L.c"
            }
          else
            {
#include"./include/case0.c"
#include"./include/case1.c"
#include"./include/case2.c"
#include"./include/case3.c"
#include"./include/case4.c"
#include"./include/case5.c"
#include"./include/case6.c"
#include"./include/case7.c"
            }
          if (LASPACK && LASResult ())
            {
              const char *fl = "LASPACK_ERR.txt";
              FILE *fp_err;
              printf ("Look %s\n", fl);
              fp_err = fopen (fl, "w");
              WriteLASErrDescr (fp_err);
              fclose (fp_err);
            }
        }
      if (LASPACK)
        {
          prepare_to_solve_system_L (&x, G, V1, V2, n);
          BiCGSTABIter (&A, &x, &b, MAX_ITER, JacobiPrecond, 1);
          copy_answer_L (&x, G, V1, V2, p_s);
        }
      else
        {
          ind[mm] = k;
//          d = new double[7 * 3 * n];
          prepare_to_solve_system (d, G, V1, V2, n);
          if (solve_system_BICGSTAB (matrix, ind, rhs, 3 * n, d))
            {
              return;
            }
        }
      if (RELEASE)
        {
          run_gnuplot (p_s, timestep, X, Y, G, V1, V2);
        }
    }
  if (LASPACK)
    {
      Q_Destr (&A);
      V_Destr (&b);
      V_Destr (&x);
    }
  else
    {
      free (matrix);
      free (rhs);
      free (ind);
      free (d);
    }
}
