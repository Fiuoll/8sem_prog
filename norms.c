#include "head.h"
void Norm_c (int it, int nh, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
             double *res_G, double *res_V1, double *res_V2, double *X_H, double *Y_H)
{
  int i;
  double max_G = 0;
  double max_V1 = 0;
  double max_V2 = 0;

  if (nh < 1)
    {
      nh = n;
      X_H = X;
      Y_H = Y;
    }

  for (i = 0; i < nh; i++)
    {
      if (fabs (G[i] - sm_g (t, X_H[i], Y_H[i])) > max_G)
        max_G = fabs(G[i] - sm_g (t, X_H[i], Y_H[i]));
    }
  for (i = 0; i < n; i++)
    {
      if (fabs (V1[i] - sm_vx (t, X[i], Y[i])) > max_V1)
        max_V1 = fabs(V1[i] - sm_vx (t, X[i], Y[i]));
      if (fabs (V2[i] - sm_vy (t, X[i], Y[i])) > max_V2)
        max_V2 = fabs(V2[i] - sm_vy (t, X[i], Y[i]));
    }
  res_G[it] = max_G;
  res_V1[it] = max_V1;
  res_V2[it] = max_V2;
}

void Norm_l2 (int it, int nh, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
              double *res_G, double *res_V1, double *res_V2, double h, int *st, double *X_H, double *Y_H)
{
  int i;
  double sum_G = 0.;
  double sum_V1 = 0.;
  double sum_V2 = 0.;
  double tmp;

  if (nh < 1)
    {
      nh = n;
      X_H = X;
      Y_H = Y;
    }
  for (i = 0; i < nh; i++)
    {
      if (st[i] == 0)
        {
          tmp = G[i] - sm_g (t, X_H[i], Y_H[i]);
          sum_G += tmp * tmp;
        }
      else
        {
          tmp = G[i] - sm_g (t, X_H[i], Y_H[i]);
          sum_G += 0.5 * tmp * tmp;
        }
    }
  for (i = 0; i < n; i++)
    {
      if (st[i] == 0)
        {
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          sum_V1 += tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          sum_V2 += tmp * tmp;
        }
      else
        {
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

void Norm_Wl2 (int it, int nh, int n, double *G, double *V1, double *V2, double *X, double *Y, double t,
               double *res_G, double *res_V1, double *res_V2, double h, int *st, int *sth, int *M0L, double *X_H, double *Y_H, int *M0L_H)
{
  int i;
  double sum_G = 0.;
  double sum_V1 = 0.;
  double sum_V2 = 0.;
  double tmp;

  if (nh < 1)
    {
      nh = n;
      X_H = X;
      Y_H = Y;
      sth = st;
      M0L_H = M0L;
    }

  for (i = 0; i < nh; i++)
    {
      if (sth[i] == 0)
        {
          tmp = G[i] - sm_g (t, X_H[i], Y_H[i]);
          sum_G += tmp * tmp;
        }
      else
        {
          tmp = G[i] - sm_g (t, X_H[i], Y_H[i]);
          sum_G += 0.5 * tmp * tmp;
        }

      if (sth[i] == 1 || sth[i] == 4)
        {
          tmp = (G[i + 1] - G[i]) / h;
          sum_G += tmp * tmp;
        }

      if (sth[i] == 6)
        {
          tmp = (G[M0L_H[i]] - G[i]) / h;
          sum_G += tmp * tmp;
        }
    }

  for (i = 0; i < n; i++)
    {
      if (st[i] == 0)
        {
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          sum_V1 += tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          sum_V2 += tmp * tmp;
        }
      else
        {
          tmp = V1[i] - sm_vx (t, X[i], Y[i]);
          sum_V1 += 0.5 * tmp * tmp;
          tmp = V2[i] - sm_vy (t, X[i], Y[i]);
          sum_V2 += 0.5 * tmp * tmp;
        }

      if (st[i] == 1 || st[i] == 4)
        {
          tmp = (V1[i + 1] - V1[i]) / h;
          sum_V1 += tmp * tmp;
          tmp = (V2[i + 1] - V2[i]) / h;
          sum_V2 += tmp * tmp;
        }

      if (st[i] == 6)
        {
          tmp = (V1[M0L[i]] - V1[i]) / h;
          sum_V1 += tmp * tmp;
          tmp = (V2[M0L[i]] - V2[i]) / h;
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
