#include "head.h"


//   _ _ _ _ _ _
//  |->         |
//  |_ _        |
//      |       |
//      |   |   |
//      |  \|/  |
//      |_ _ _ _|
///   _ _ _ _ _ _ _ _ _ _ _ _
///  |                       |
///  | ->                    |
///  | ->                    |
///  |_ _ _ _                |
///          |               |
///          |               |
///          |               |
///          |               |
///          |               |
///          |               |
///          |               |
///          |_ _ _ _ _ _ _ _|
///                  |
///                \ | /
///                 \ /
///                  V
///
///  LR 0R RR
///  L0 00 R0
///  LL 0L RL
///
int parse_command_line (int argc, char *argv[]);
int parse_command_line (int argc, char *argv[])
{
  (void) argc;
  (void) argv;
  return 0;
}
void correct_array (int n, double *a)
{
  for (int i = 0; i < n; i++)
    {
      if (fabs (a[i]) < 1e-15 )
        a[i] = 0.;
    }
}

int main(int argc, char *argv[])
{
  int it_t, it_sp;
  int it_t_max = 2, it_sp_max = 2;
  int it = 0, it_max;

  double *nc_g, *nl2_g;
  double *nc_v1, *nl2_v1;
  double *nc_v2, *nl2_v2;

  double *workspace_d;
  int *workspace_i;
  double *workspace_d_2;

  double *G, *V1, *V2, *X, *Y;
  int *st, *M0L, *M0R, *R0M, *L0M;

  P_gas p_d;
  P_she p_s;
  param_dif (&p_d);

  parse_command_line (argc, argv);

  it_max = it_sp_max * it_t_max;

  param_she_step (&p_s, &p_d, it_t_max, it_sp_max);

  workspace_d = (double*)malloc(5 * p_s.Dim * sizeof(double));
  workspace_i = (int*)malloc(5 * p_s.Dim * sizeof(int));

  if (!workspace_i || !workspace_d)
    return -1;
  G = workspace_d;
  V1 = G + p_s.Dim;
  V2 = V1 + p_s.Dim;
  X = V2 + p_s.Dim;
  Y = X + p_s.Dim;

  st = workspace_i;
  M0L = st + p_s.Dim;
  M0R = M0L + p_s.Dim;
  L0M = M0R + p_s.Dim;
  R0M = L0M + p_s.Dim;

  workspace_d_2 = (double*)malloc(6 * it_max * sizeof(double));

  nc_g = workspace_d_2;
  nl2_g = nc_g + it_max;
  nc_v1 = nl2_g + it_max;
  nl2_v1 = nc_v1 + it_max;
  nc_v2 = nl2_v1 + it_max;
  nl2_v2 = nc_v2 + it_max;

  printf ("Started\n");
  for (it_t = 0; it_t < it_t_max; it_t++)
    {
      for (it_sp = 0; it_sp < it_sp_max; it_sp++)
        {
          printf ("time it = %d, sp it = %d \n", it_t, it_sp);
          param_she_step (&p_s, &p_d, it_t, it_sp);
          printf ("Params system: hx = %f, hy = %f, tau = %f\n", p_s.h_x, p_s.h_y, p_s.tau);
          printf ("fill maps\n");
          Setka (st, X, Y, M0L, M0R, L0M, R0M, &p_s);
          printf ("Computing...\n");
          Shema (G, V1, V2, st, X, Y, M0L, M0R, &p_s, &p_d);

          correct_array (p_s.Dim, G);
          correct_array (p_s.Dim, V1);
          correct_array (p_s.Dim, V2);
          Norm_c (it, p_s.Dim, G, V1, V2, X, Y, 1, nc_g, nc_v1, nc_v2);
          Norm_l2 (it, p_s.Dim, G, V1, V2, X, Y, 1, nl2_g, nl2_v1, nl2_v2);

          printf ("Norms C: %e, %e, %e\n", nc_g[it], nc_v1[it], nc_v2[it]);
          printf ("Norms L2: %e, %e, %e\n", p_s.h_x * nl2_g[it], p_s.h_x * nl2_v1[it], p_s.h_x * nl2_v2[it]);
          it++;

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
    }

  print_to_file ("./G.txt", X, Y, G, p_s.Dim);
  print_to_file ("./V1.txt", X, Y, V1, p_s.Dim);
  print_to_file ("./V2.txt", X, Y, V2, p_s.Dim);

  print_norms_to_file ("./norms.inc", it_t_max, it_sp_max, nc_g, nc_v1, nc_v2, nl2_g, nl2_v1, nl2_v2);

  free (workspace_d);
  free (workspace_i);
  free (workspace_d_2);

  printf ("End!\n");
  return 0;
}
