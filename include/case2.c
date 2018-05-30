// right wall

if (st[i] == 2)
{
  //G
  tmp = 2. + thx * v100;
  matrix[mm] = tmp;
  ind[mm]    = k;

  tmp = - thx * v1L0;
  matrix[k] = tmp;
  ind[k++]  = mmgL0;

  matrix[k] = thx2;
  ind[k++]  = mmv100;

  matrix[k] = -thx2;
  ind[k++]  = mmv1L0;

  tmp = 2 * g00 + thx * g00 * (v100 - v1L0)
      - thx * (  //g00 * v100
               - 2.5 * gL0 * v1L0
               + 2 * g_2L * v1_2L
               - 0.5 * g_3L * v1_3L
               + (2 - g00) * (  v100
                              - 2.5 * v1L0
                              + 2 * v1_2L
                              - 0.5 * v1_3L))
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
