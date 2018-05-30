// top node
if (st[i] == 6)
{
  //G
  tmp = 2. + thy * v200;
  matrix[mm] = tmp;
  ind[mm]    = k;

  tmp = - thy * v20L;
  matrix[k] = tmp;
  ind[k++]  = mmg0L;

  matrix[k] = -thy2;
  ind[k++]  = mmv20L;

  matrix[k] = thy2;
  ind[k++]  = mmv200;

  tmp = 2 * g00 + thy * g00 * (v200 - v20L)
      - thy * (  g00 * v200
               - 2.5 * g0L * v20L
               + 2 * g_2B * v2_2B
               - 0.5 * g_3B * v2_3B
               + (2 - g00) * (  v200
                              - 2.5 * v20L
                              + 2 * v2_2B
                              - 0.5 * v2_3B))
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
