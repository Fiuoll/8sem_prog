#include "head.h"

//  7 6 6 6 6 6 7
//  4->         2
//  7 5 7   0   2
//      1       2
//      1   |   2
//      1  \|/  2
//      7 3 3 3 7

void Setka_S (int *st, double *X, double *Y, int *bot, int *top, P_she *p_s)
{
  int n = p_s->M_x - 1;
  int m = p_s->M_y - 1;
  int i = 0;
  int j = 0;
  double hx2 = p_s->h_x / 2;
  double hy2 = p_s->h_y / 2;

  fill_1 (st, p_s->S_DimH);
  fill_1 (bot, p_s->S_DimH);
  fill_1 (top, p_s->S_DimH);

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 3, 2, 2 * n,
           1 * COEF + hx2, hy2, 2 * n, 2 * n /*bot[i]<0*/);

  for (j = 1; j < 2 * m - 1; j++)
    {
      set_str (st, X, Y, bot, top, p_s,
               &i, 1, 0, 2, 2 * n,
               1 * COEF + hx2, j * p_s->h_y + hy2, 2 * n , 2 * n);
    }
  set_str (st, X, Y, bot, top, p_s,
           &i, 1, 0, 2, 2 * n,
           1 * COEF + hx2, j * p_s->h_y + hy2, 3 * n, 2 * n);

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 5, 5, n,
           hx2, 2 * COEF + hy2, 3 * n, 5 * n * m /*bot[i] < 0*/);

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 0, 2, 2 * n,
           1 * COEF + hx2, 2 * COEF + hy2, 3 * n , 3 * n);


  for (j = 1; j < m - 1; j++)
    {
      set_str (st, X, Y, bot, top, p_s,
               &i, 4, 0, 2, 3 * n,
               hx2, 2 * COEF + j * p_s->h_y + hy2, 3 * n , 3 * n);
    }

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 6, 7, 3 * n,
           hx2, 3 * COEF + hy2, 3 * n, 3 * n);
}
