// corner
if (st[i] == 7)
{
  //G
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = sm_g (tt, xx, yy);

  mm++;
  //V1
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = 0;

  mm++;
  // V2
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = 0;

  continue;
}
