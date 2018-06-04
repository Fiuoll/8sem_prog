#include "head.h"

void my_sleep (double c)
{
  double t0, t = 0;
  t0 = clock ();
  while (t < c)
    {
      t = (clock () - t0) / CLOCKS_PER_SEC;
    }
}

void run_gnuplott (void)
{
  const char *filename_com = FILE_COMMAND;
  char path_dest [LEN];
  int res;

  sprintf (path_dest, "\"gnuplot\" %s%c\"", filename_com,'\0');

  res = system (path_dest);
  (void) res;

  my_sleep (1e-3);
}
void fill_command_file (const char *val_name, P_she *p_s, int time_step,
                        const char *val_path)
{
  const char *filename_com = FILE_COMMAND;
  double t = time_step * p_s->tau;

  FILE *f_com;
  f_com = fopen (filename_com, "w");

  fprintf (f_com, "set terminal png size 1024, 768\n");
  fprintf (f_com, "set output '%s/%d.png'\n", val_name, time_step);
  fprintf (f_com, "set xlabel \"t = %.4f\" font \"Times-Roman,30\"\n", t);
  fprintf (f_com, "set xrange [0:3*pi]; set yrange [0:3*pi]\n");
  fprintf (f_com, "%s\n", val_path);

  fclose (f_com);
}
void print_paint_pm3d_command (char *path, const char *fname)
{
  const char *palette = "set palette rgbformulae 34,35,36";
  const char *map = "set pm3d map";
  sprintf (path, "%s; %s; splot '%s' with pm3d%c",
           palette, map, fname, '\0');
}
void print_paint_vectors_command (char *path, const char *fname)
{
  sprintf (path, "plot '%s' using 1:2:3:4 with vectors filled head lw 3%c",
           fname, '\0');
}
void print_G_to_file (P_she *p_s, double *X, double *Y, int n, double *G, FILE *fp)
{
  double x = 0;
  double h = p_s->h_x;
  int M = p_s->M_x;
  int i, j;

  int top = 3 * M;
  for (i = 0; i < top; i++, x += h)
    {
      for (j = n - 1; j > -1; j--)
        {
          if (fabs (x - X[j]) > 1e-12)
            continue;

          fprintf (fp, "%e %e %e\n", X[j], Y[j], exp (G[j]));
        }
      fprintf (fp, "\n");
    }
}
void print_V_to_file (P_she *p_s, double *X, double *Y, int n, double *V1, double *V2, FILE *fp)
{
  double x = 0;
  double h = p_s->h_x;
  int M = p_s->M_x;
  int i, j;

  int top = 3 * M;
  for (i = 0; i < top; i++, x += h)
    {
      for (j = n - 1; j > -1; j--)
        {
          if (fabs (x - X[j]) > 1e-12)
            continue;

          fprintf (fp, "%e %e %e %e\n", X[j], Y[j], get_V_x (V1[j], V2[j], h), get_V_y (V1[j], V2[j], h));
        }
      fprintf (fp, "\n");
    }
}
double get_V_x (double x, double y, double h)
{
    double d = sqrt (x * x + y * y);
    if (d < 1e-16)
        return 0;
    d /= h;
    return x / d;
}
double get_V_y (double x, double y, double h)
{
    double d = sqrt (x * x + y * y);
    if (d < 1e-16)
        return 0;
    d /= h;
    return y / d;
}
void run_gnuplot (P_she *p_s, int time_step, double *X, double *Y, double *G, double *V1, double *V2)
{
  char path_g [LEN];
  char path_u1 [LEN];

  FILE *fg = fopen (FILE_G, "w");
  FILE *fv = fopen (FILE_V, "w");
  print_G_to_file (p_s, X, Y, p_s->Dim, G, fg);
  print_V_to_file (p_s, X, Y, p_s->Dim, V1, V2, fv);
  fclose (fg);
  fclose (fv);
  print_paint_pm3d_command (path_g, FILE_G);
  print_paint_vectors_command (path_u1, FILE_V);

  // GNUPLOT
  fill_command_file ("G",  p_s, time_step, path_g);
  run_gnuplott ();
  fill_command_file ("V", p_s, time_step, path_u1);
  run_gnuplott ();
}

void clean_png (const char *path)
{
    char path_dest [LEN];

    sprintf (path_dest, "rm -rf %s\\/*.png%c\"", path,'\0');

    int res = system (path_dest);
    (void) res;

    usleep(100);
}
