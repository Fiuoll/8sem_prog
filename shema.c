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
  for (int i = 0; i < p_s->Dim; i++)
    {
      k = 3 * (unsigned int)i + 1;
      G[i] = V_GetCmp (x, k);
      V1[i] = V_GetCmp (x, k + 1);
      V2[i] = V_GetCmp (x, k + 2);
    }
}
void copy_answer (double *x, double *G, double *V1, double *V2, P_she *p_s)
{
  for (int i = 0; i < p_s->Dim; i++)
    {
      G[i] = x[3 * i];
      V1[i] = x[3 * i + 1];
      V2[i] = x[3 * i + 2];
    }
}
int get_safe (int i, int n);
int get_safe (int i, int n)
{
  if (i >= n || i < 0)
    return 0;
  return i;
}
void my_sleep (double c);
void my_sleep (double c)
{
  double t0, t = 0;
  t0 = clock ();
  while (t < c)
    {
      t = (clock () - t0) / CLOCKS_PER_SEC;
    }
}

void run_gnuplott (void);
void run_gnuplott (void)
{
  const char *filename_com = "com.txt";
  char path_dest [LEN];
  int res;

  sprintf (path_dest, "\"gnuplot\" %s%c\"", filename_com,'\0');

  res = system (path_dest);
  (void) res;

  my_sleep (1e-3);
}
void fill_command_file (const char *val_name, P_she *p_s, int time_step,
                        const char *val_path);
void fill_command_file (const char *val_name, P_she *p_s, int time_step,
                        const char *val_path)
{
  const char *filename_com = "com.txt";
  double t = time_step * p_s->tau;

  FILE *f_com;
  f_com = fopen (filename_com, "w");

  fprintf (f_com, "set terminal png size 1024, 768\n");
  fprintf (f_com, "set output '%s/%d.png'\n", val_name, time_step);
  fprintf (f_com, "set xlabel \"t = %.4f\" font \"Times-Roman,30\"\n", t);
  fprintf (f_com, "set xrange [0:3*pi]; set yrange [0:2*pi]\n");
  fprintf (f_com, "%s\n", val_path);

  fclose (f_com);
}
void print_paint_pm3d_command (char *path, const char *fname);
void print_paint_pm3d_command (char *path, const char *fname)
{
  const char *palette = "set palette rgbformulae 34,35,36";
  const char *map = "set pm3d map";
  sprintf (path, "%s; %s; splot '%s' with pm3d%c",
           palette, map, fname, '\0');
}
void print_paint_vectors_command (char *path, const char *fname);
void print_paint_vectors_command (char *path, const char *fname)
{
  sprintf (path, "plot '%s' using 1:2:3:4 with vectors filled head lw 3%c",
           fname, '\0');
}
void print_values_X_order_exp (P_she *p_s, double *X, double *Y, int n, double *val, FILE *fp);
void print_values_X_order_exp (P_she *p_s, double *X, double *Y, int n, double *val, FILE *fp)
{
  double x = 0;
  double h = p_s->h_x;
  int M = p_s->M_x;
  int print_count = 0;

  int top = 3 * M + 1;
  for (int i = 0; i < top; i++, x += h)
    {
      for (int j = 0; j < n; j++)
        {
          if (fabs (x - X[j]) > 1e-12)
            continue;

          fprintf (fp, "%e %e %e\n", X[j], Y[j], exp (val[j]));
          print_count++;
        }
      fprintf (fp, "\n");
    }

  if (print_count != n)
    printf ("Error in print_values_X_order\n");
}
void run_gnuplot (P_she *p_s, int time_step, double *X, double *Y, double *G);
void run_gnuplot (P_she *p_s, int time_step, double *X, double *Y, double *G)
{
  char path_g [LEN];
  char path_u1 [LEN];
  //char path_u2 [LEN];
  FILE *fp = fopen ("G.txt", "w");
  print_values_X_order_exp (p_s, X, Y, p_s->Dim, G, fp);
  fclose (fp);
  print_paint_pm3d_command (path_g, "G.txt");
  print_paint_vectors_command (path_u1, "V1.txt");
  //print_paint_command (path_u2, FNAME_U2);

  // GNUPLOT
  fill_command_file ("g",  p_s, time_step, path_g);
  run_gnuplott ();
  fill_command_file ("u1", p_s, time_step, path_u1);
  run_gnuplott ();
  //fill_command_file ("u2", p_s, time_step, path_u2);
  //run_gnuplot ();

}
void Shema (double *G, double *V1, double *V2, int *st, double *X, double *Y, int *M0L, int *M0R, P_she *p_s, P_gas *p_d)
{
  double t = 0;
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
  for (timestep = 0; timestep < p_s->N; timestep++, t += p_s->tau)
    {
#include"./include/mum.c"
      tt = timestep * tau;
      for (i = 0, mm = LASPACK, k = p_s->Dim + 1; i < n; i++, mm++)
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
          BiCGSTABIter (&A, &x, &b, MAX_ITER, JacobiPrecond, 1);
          copy_answer_L (&x, G, V1, V2, p_s);
        }
      else
        {
          ind[mm] = k;
//          d = new double[7 * 3 * n];
          prepare_to_solve_system (d, G, V1, V2, n);
          if (solve_system_BICGSTAB_wiki (matrix, ind, rhs, 3 * n, d))
            {
              return;
            }
        }
//      run_gnuplot (p_s, timestep, X, Y, G);
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
