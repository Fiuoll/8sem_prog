#include "head.h"
void Norm_c (int it, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
             double *res_G, double *res_V1, double *res_V2)
{
  int i;
  double max_G = 0;
  double max_V1 = 0;
  double max_V2 = 0;
  for (i = 0; i < n; i++)
    {
      if (fabs (G[i] - sm_g (t, X[i], Y[i])) > max_G)
        max_G = fabs(G[i] - sm_g (t, X[i], Y[i]));
      if (fabs (V1[i] - sm_vx (t, X[i], Y[i])) > max_V1)
        max_V1 = fabs(V1[i] - sm_vx (t, X[i], Y[i]));
      if (fabs (V2[i] - sm_vy (t, X[i], Y[i])) > max_V2)
        max_V2 = fabs(V2[i] - sm_vy (t, X[i], Y[i]));
    }
  res_G[it] = max_G;
  res_V1[it] = max_V1;
  res_V2[it] = max_V2;
}

void Norm_l2 (int it, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
              double *res_G, double *res_V1, double *res_V2, double h, int *st)
{
  int i;
  double sum_G = 0.;
  double sum_V1 = 0.;
  double sum_V2 = 0.;
  double tmp;
  for (i = 0; i < n; i++)
    {
      if (st[i] == 0)
        {
          tmp = G[i] - sm_g (t, X[i], Y[i]);
          sum_G += tmp * tmp;
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          sum_V1 += tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          sum_V2 += tmp * tmp;
        }
      else
        {
          tmp = G[i] - sm_g (t, X[i], Y[i]);
          if (st[i] == 7 && tmp > 1e-8)
            {
              printf ("it is problem");
            }
          sum_G += 0.5 * tmp * tmp;
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          if (st[i] == 7 && tmp > 1e-8)
            {
              printf ("it is problem");
            }
          sum_V1 += 0.5 * tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          if (st[i] == 7 && tmp > 1e-8)
            {
              printf ("it is problem");
            }
          sum_V2 += 0.5 * tmp * tmp;
        }

    }

  sum_G  *= h * h;
  sum_V1 *= h * h;
  sum_V2 *= h * h;

  res_G[it] = sqrt (sum_G);
  res_V1[it] = sqrt (sum_V1);
  res_V2[it] = sqrt (sum_V2);
}

void Norm_Wl2 (int it, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
               double *res_G, double *res_V1, double *res_V2, double h, int *st, int *M0L)
{
  int i;
  double sum_G = 0.;
  double sum_V1 = 0.;
  double sum_V2 = 0.;
  double tmp;

  for (i = 0; i < n; i++)
    {
      if (st[i] == 0)
        {
          tmp = G[i] - sm_g (t, X[i], Y[i]);
          sum_G += tmp * tmp;
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          sum_V1 += tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          sum_V2 += tmp * tmp;
        }
      else
        {
          tmp = G[i] - sm_g (t, X[i], Y[i]);
          sum_G += 0.5 * tmp * tmp;
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          sum_V1 += 0.5 * tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          sum_V2 += 0.5 * tmp * tmp;
        }

      if (st[i] == 1 || st[i] == 4)
        {
          tmp = (G[i + 1] - G[i]) / (X[i + 1] - X[i]);
          sum_G += tmp * tmp;
          tmp = (V1[i + 1] - V1[i]) / (X[i + 1] - X[i]);
          sum_V1 += tmp * tmp;
          tmp = (V2[i + 1] - V2[i]) / (X[i + 1] - X[i]);
          sum_V2 += tmp * tmp;
        }

      if (st[i] == 6)
        {
          tmp = (G[M0L[i]] - G[i]) / (Y[M0L[i]] - Y[i]);
          sum_G += tmp * tmp;
          tmp = (V1[M0L[i]] - V1[i]) / (Y[M0L[i]] - Y[i]);
          sum_V1 += tmp * tmp;
          tmp = (V2[M0L[i]] - V2[i]) / (Y[M0L[i]] - Y[i]);
          sum_V2 += tmp * tmp;
        }
    }

  sum_G  *= h * h;
  sum_V1 *= h * h;
  sum_V2 *= h * h;

  res_G[it] = sqrt (sum_G);
  res_V1[it] = sqrt (sum_V1);
  res_V2[it] = sqrt (sum_V2);
}
