// entry node
if (st[i] == 4)
{
  //G
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = sm_g (tt, xx, yy);

  //V1
  mm++;
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = sm_vx (tt, xx, yy);

  // V2
  mm++;
  matrix[mm] = 1;
  ind[mm]    = k;
  rhs[mm] = 0;

  continue;
}
