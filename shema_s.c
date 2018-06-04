#include "head.h"

void copy_answer_L_H (Vector *x, double *G, int n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      G[i] = V_GetCmp (x, i + 1);
    }
}

void copy_answer_L_V (Vector *x, double *V1, double *V2, int n)
{
  unsigned int k;
  int i;
  for (i = 0; i < n; i++)
    {
      k = 2 * (unsigned int)i + 1;
      V1[i] = V_GetCmp (x, k);
      V2[i] = V_GetCmp (x, k + 1);
    }
}

void Shema_S (double *G, int *st_H, double *X_H, double *Y_H, int *M0L_H, int *M0R_H,
              double *V1, double *V2, int *st, double *X, double *Y, int *M0L, int *M0R,
              P_she *p_s, P_gas *p_d)
{
  double t = 0;
  int timestep;
  int n, nz, k, nH;
  int i, j;
  QMatrix_L A, AH;
  Vector b, bH;
  Vector x, xH;
  double *matrix;
  int    *ind;
  double *rhs;
  double *d;
  double *H;
  double gamma;
#include"./include_S/perem.c"

  n = p_s->Dim;
  nH = p_s->S_DimH;
  nz = p_s->nz;
  mu = p_d->mu;
  pressure = p_d->p_ro;
  hx = p_s->h_x;
  hy = p_s->h_y;
  tau = p_s->tau;
  gamma = p_s->gamma;
if (LASPACK)
  {
    Q_Constr (&A, "A", 2 * n, False, Rowws, Normal, True);
    V_Constr (&b, "b", 2 * n, Normal, True);
    V_Constr (&x, "x", 2 * n, Normal, True);

    Q_Constr (&AH, "AH", nH, False, Rowws, Normal, True);
    V_Constr (&bH, "bH", nH, Normal, True);
    V_Constr (&xH, "xH", nH, Normal, True);

    H = (double *) malloc (nH * sizeof(double));
    SetRTCAccuracy (eps);
  }
else
  {
    printf ("Only LASPACK is supported with SOKOLOV!");
    return;
    matrix = (double *) malloc (nz * sizeof (double));
    ind    = (int *) malloc (nz * sizeof (int));
    rhs    = (double *) malloc (3 * n * sizeof (double));
    d      = (double *) malloc (7 * (3 * n) * sizeof (double));
  }

#include"./include_S/viraj.c"
#include"./include_S/nachal.c"

printf ("Computing...\n");

  for (timestep = 1; timestep < p_s->N; timestep++)
    {
      if (p_s->N > 10 && timestep % (p_s->N / 10) == 0)
        printf ("|");

      tt = timestep * tau;

      for (i = 0, j = 0; i < nH; i++, j++)
        {
#include"./include_S/nodeparam_H.c"
#include"./include_S/caseH.c"
          if (st_H[i] == 2)
            j++;

          if (LASPACK && LASResult ())
            {
              const char *fl = "LASPACK_ERR.txt";
              FILE *fp_err;
              printf ("Look %s\n", fl);
              fp_err = fopen (fl, "w");
              WriteLASErrDescr (fp_err);
              fclose (fp_err);
              return;
            }
        }

      if (LASPACK)
        {
          prepare_to_solve_system_L_H (&xH, G, nH);
          BiCGSTABIter (&AH, &xH, &bH, MAX_ITER, JacobiPrecond, 1);
          copy_answer_L_H (&xH, H, nH);
        }

      for (i = 0, j = 0; i < n; i++, j++)
        {
#include"./include_S/nodeparam_V.c"

#include"./include_S/case0_L.c"
#include"./include_S/case1_L.c"
#include"./include_S/case2_L.c"
#include"./include_S/case3_L.c"
#include"./include_S/case4_L.c"
#include"./include_S/case5_L.c"
#include"./include_S/case6_L.c"
#include"./include_S/case7_L.c"

          if (st[i] == 2)
            j--;

          if (LASPACK && LASResult ())
            {
              const char *fl = "LASPACK_ERR.txt";
              FILE *fp_err;
              printf ("Look %s\n", fl);
              fp_err = fopen (fl, "w");
              WriteLASErrDescr (fp_err);
              fclose (fp_err);
              return;
            }
        }
      if (LASPACK)
        {
          prepare_to_solve_system_L_V (&x, V1, V2, n);
          BiCGSTABIter (&A, &x, &b, MAX_ITER, JacobiPrecond, 1);
          copy_answer_L_V (&x, V1, V2, n);
          copy_answer_L_H (&xH, G, nH);
        }

      if (LASPACK && LASResult ())
        {
          const char *fl = "LASPACK_ERR.txt";
          FILE *fp_err;
          printf ("V solver failed! Look %s\n", fl);
          fp_err = fopen (fl, "w");
          WriteLASErrDescr (fp_err);
          fclose (fp_err);
          return;
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

int is_zero(double a)
{
  return fabs (a) < EPS;
}
