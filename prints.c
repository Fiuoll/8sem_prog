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
                          double *nwg, double *nwv1, double *nwv2)
{
  FILE *fp;
  char buf[STRLEN];

  fp = fopen (filename, "w");

  if (!fp)
    {
      snprintf (buf, STRLEN, "%s: %s\n", filename, "Cannot open file!");
      return;
    }

  fprintf (fp, "\n||G||_c \n");
  print_norm_to_file (fp, n, m, ncg);
  fprintf (fp, "\n||G||_L2 \n");
  print_norm_to_file (fp, n, m, nl2g);
  fprintf (fp, "\n||G||_WL2 \n");
  print_norm_to_file (fp, n, m, nwg);

  fprintf (fp, "\n||Vx||_c \n");
  print_norm_to_file (fp, n, m, ncv1);
  fprintf (fp, "\n||Vx||_L2 \n");
  print_norm_to_file (fp, n, m, nl2v1);
  fprintf (fp, "\n||Vx||_WL2 \n");
  print_norm_to_file (fp, n, m, nwv1);

  fprintf (fp, "\n||Vy||_c \n");
  print_norm_to_file (fp, n, m, ncv2);
  fprintf (fp, "\n||Vy||_L2 \n");
  print_norm_to_file (fp, n, m, nl2v2);
  fprintf (fp, "\n||Vy||_WL2 \n");
  print_norm_to_file (fp, n, m, nwv2);

  fclose (fp);
}
