#include "head.h"

void print_to_file (const char * filename, double *X, double*Y, double * data, int size)
{
  FILE *fp;
  char buf[STRLEN];
  int i;

  fp = fopen (filename, "w");

  if (!fp)
    {
      snprintf (buf, STRLEN, "%s: %s\n", filename, "Cannot open file!");
      return;
    }

  for (i = 0; i < size; i++)
    {
      fprintf (fp, "%e %e %e \n", X[i], Y[i], data[i]);
    }

  fclose (fp);
}
void print_to_file_both (const char * filename, double *X, double*Y, double *data1, double *data2, int size);
void print_to_file_both (const char * filename, double *X, double*Y, double *data1, double *data2, int size)
{
  FILE *fp;
  char buf[STRLEN];
  int i;

  fp = fopen (filename, "w");

  if (!fp)
    {
      snprintf (buf, STRLEN, "%s: %s\n", filename, "Cannot open file!");
      return;
    }

  for (i = 0; i < size; i++)
    {
      fprintf (fp, "%e %e %e %e\n", X[i], Y[i], data1[i], data2[i]);
    }

  fclose (fp);
}
void print_table (FILE *fp, const char *table_name, int n, int m, double *a)
{
  int i, j;
  fprintf (fp, "\\begin{center}\n");
  fprintf (fp, "%s\n", table_name);

  fprintf (fp, "\\begin{tabular}{|c|");
  for (i = 0; i < n; i++)
    fprintf (fp, "c|");
  fprintf (fp, "}\n");
  fprintf (fp, "\\hline \n");
  fprintf (fp, "N  M");
  for (i = 0;i < n; i++)
    fprintf (fp, "& %d", INIT_X * (1 << i));
  fprintf (fp, "\\\\ \n");
  fprintf (fp, "\\hline \n");
  for (i =  0; i < n; i++)
    {
      fprintf (fp, "%d ", INIT_T * (1 << i));
      for (j = 0; j < m; j++)
        {
          fprintf (fp, "& %e ", a[i * m + j]);
        }
      fprintf(fp, "\\\\ \\hline \n");
    }
  fprintf (fp, "\\hline \n");
  fprintf (fp, "\\end{tabular} \n");
  fprintf (fp, "\\end{center} \n");
}

void print_norm_to_file (FILE *fp, int n, int m, double *array)
{
  int i;
  int j;
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < m; j++)
        {
          fprintf (fp, "%e |", array[i * m + j]);
        }
      fprintf (fp, "\n");
    }
}

void print_norms_to_file (const char * filename, int n, int m,
                          double *ncg, double *ncv1, double *ncv2,
                          double *nl2g, double *nl2v1, double *nl2v2,
                          double *nwg, double *nwv1, double *nwv2, double *time)
{
  FILE *fp;
  char buf[STRLEN];

  fp = fopen (filename, "w");

  if (!fp)
    {
      snprintf (buf, STRLEN, "%s: %s\n", filename, "Cannot open file!");
      return;
    }
  print_table (fp, "$||G - g||_c$", n, m, ncg);
  print_table (fp, "$||G - g||_{L2}$", n, m, nl2g);
  print_table (fp, "$||G - g||_{2}^1$", n, m, nwg);


  print_table (fp, "$||V1 - u1||_c$", n, m, ncv1);
  print_table (fp, "$||V1 - u1||_{L2}$", n, m, nl2v1);
  print_table (fp, "$||V1 - u1||_{2}^1$", n, m, nwv1);

  print_table (fp, "$||V2 - u2||_c$", n, m, ncv2);
  print_table (fp, "$||V2 - u2||_{L2}$", n, m, nl2v2);
  print_table (fp, "$||V2 - u2||_{2}^1$", n, m, nwv2);

  print_table (fp, "TIME", n, m, time);

  fclose (fp);
}
