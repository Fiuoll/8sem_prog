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
              double *res_G, double *res_V1, double *res_V2)
{
  int i;
  double sum_G = 0.;
  double sum_V1 = 0.;
  double sum_V2 = 0.;
  double tmp;
  for (i = 0; i < n; i++)
    {
      tmp = G[i] - sm_g (t, X[i], Y[i]);
      sum_G += tmp * tmp;
      tmp = V1[i] - sm_vx (t, X[i], Y[i]);
      sum_V1 += tmp * tmp;
      tmp = V2[i] - sm_vy (t, X[i], Y[i]);
      sum_V2 += tmp * tmp;
    }
  res_G[it] = sqrt (sum_G);
  res_V1[it] = sqrt (sum_V1);
  res_V2[it] = sqrt (sum_V2);
}
