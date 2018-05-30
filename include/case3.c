// exit
if (st[i] == 3)
{
  //G
  tmp = 2. - thy * v200;
  matrix[mm] = tmp;
  ind[mm]    = k;

  tmp = thy * v20R;
  matrix[k] = tmp;
  ind[k++]  = mmg0R;

  matrix[k] = thy2;
  ind[k++]  = mmv20R;

  matrix[k] = -thy2;
  ind[k++]  = mmv200;

  tmp = 2 * g00 + thy * g00 * (v20R - v200)
      + thy * (//g00 * v200
               - 2.5 * g0R * v20R
               + 2 * g_2T * v2_2T
               - 0.5 * g_3T * v2_3T
               + (2 - g00) * (  v200
                              - 2.5 * v20R
                              + 2 * v2_2T
                              - 0.5 * v2_3T))
      + tau2 * Func_0 (tt, xx, yy);
  rhs[mm] = tmp;

  mm++;
  //V1
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm]    = 0.;

  mm++;
  //V2
  matrix[mm] = 1;
  ind[mm]    = k;

  matrix[k] = -1;
  ind[k++]  = mmv20R;
  // V1_M = V1_(M-1) + dv2_dy * hy
  tmp = hy * dvdy (tt, xx, yy);
  rhs[mm] = tmp;

  continue;
}
