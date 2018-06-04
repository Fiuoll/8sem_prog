#include "head.h"
void set_str (int *st, double *X, double *Y, int *bot, int *top, P_she *p_s,
              int *i, int st_left_corner, int st_middle, int st_right_corner, int str_len,
              double x_begin, double y_begin, int str_len_top, int str_len_bot)
{
  int k = 0;

  st[*i] = st_left_corner;
  X[*i] = x_begin;
  Y[*i] = y_begin;

  top[*i] = *i + str_len_top;
  bot[*i] = *i - str_len_bot;

  *i = *i + 1;
  for (k = 1; k < str_len - 1; k++, *i += 1)
    {
      st[*i] = st_middle;
      X[*i] = x_begin + k * p_s->h_x;
      Y[*i] = y_begin;
      top[*i] = *i + str_len_top;
      bot[*i] = *i - str_len_bot;
    }

  st[*i] = st_right_corner;
  X[*i] = x_begin + k * p_s->h_x;
  Y[*i] = y_begin;

  top[*i] = *i + str_len_top;
  bot[*i] = *i - str_len_bot;

  (*i)++;
}

void fill_1 (int *x, unsigned int n)
{
  unsigned int i = 0;
  for (; i < n; i++)
    {
      x[i] = -1;
    }
}
//  7 6 6 6 6 6 7
//  4->         2
//  7 5 7   0   2
//      1       2
//      1   |   2
//      1  \|/  2
//      7 3 3 3 7

void Setka (int *st, double *X, double *Y, int *bot, int *top, P_she *p_s)
{
  int n = p_s->M_x;
  int m = p_s->M_y;
  int i = 0;
  int j = 0;

  fill_1 (st, p_s->Dim);
  fill_1 (bot, p_s->Dim);
  fill_1 (top, p_s->Dim);

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 3, 2, 2 * n - 1,
           1 * COEF, 0, 2 * n - 1, 2 * n - 1/*bot[i]<0*/);

  for (j = 1; j < 2 * m - 3; j++)
    {
      set_str (st, X, Y, bot, top, p_s,
               &i, 1, 0, 2, 2 * n - 1,
               1 * COEF, j * p_s->h_y, 2 * n - 1 , 2 * n - 1);
    }
  set_str (st, X, Y, bot, top, p_s,
           &i, 1, 0, 2, 2 * n - 1,
           1 * COEF, j * p_s->h_y, 3 * n - 2 , 2 * n - 1);

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 5, 5, n - 1,
           0, 2 * COEF, 3 * n - 2 , (3 * n - 2) * (m + 1) /*bot[i] < 0*/);

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 0, 2, 2 * n - 1,
           1 * COEF, 2 * COEF, 3 * n - 2 , 3 * n - 2);


  for (j = 1; j < m - 1; j++)
    {
      set_str (st, X, Y, bot, top, p_s,
               &i, 4, 0, 2, 3 * n - 2,
               0, 2 * COEF + j * p_s->h_y, 3 * n - 2 , 3 * n - 2);
    }

  set_str (st, X, Y, bot, top, p_s,
           &i, 7, 6, 2, 3 * n - 2,
           0, 3 * COEF, 3 * n - 2 , 3 * n - 2);

  printf ("fill maps\n");
}
