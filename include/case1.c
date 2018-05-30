 // left node (gamma1-)
// | 0R RR
// | 00 R0
// | 0L RL

if (st[i] == 1)
{
  //G
  tmp = 2. - thx * v100;
  matrix[mm] = tmp;
  ind[mm]    = k;

  tmp = thx * v1R0;
  matrix[k] = tmp;
  ind[k++]  = mmgR0;

  matrix[k] = thx2;
  ind[k++]  = mmv1R0;

  matrix[k] = -thx2;
  ind[k++]  = mmv100;

  tmp = 2 * g00 + thx * g00 * (v1R0 - v100)
      + thx * ( //g00 * v100
               - 2.5 * gR0 * v1R0
               + 2 * g_2R * v1_2R
               - 0.5 * g_3R * v1_3R
               + (2 - g00) * (  v100
                              - 2.5 * v1R0
                              + 2 * v1_2R
                              - 0.5 * v1_3R))
      + tau2 * Func_0 (tt, xx, yy);
  rhs[mm] = tmp;

  // V1
  mm++;
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm]    = 0.;

  // V2
  mm++;
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm]    = 0.;

  continue;
}
