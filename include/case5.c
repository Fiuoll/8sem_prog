// bot node
if (st[i] == 5)
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
      + thy * (g00 * v200 - 2.5 * g0R * v20R
               + 2 * g_2T * v2_2T
               - 0.5 * g_3T * v2_3T
               + (2 - g00) * (  v200
                              - 2.5 * v20R
                              + 2 * v2_2T
                              - 0.5 * v2_3T))
      + tau2 * Func_0 (tt, xx, yy);
  rhs[mm] = tmp;

  // V1
  mm++;
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = 0;

  // V2
  mm++;
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = 0;

  continue;
}
