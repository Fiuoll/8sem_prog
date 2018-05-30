// inner node
if (st[i] == 0)
{
  //G
  matrix[mm] = 4.;
  ind[mm]    = k;

  tmp = thx * (v100 + v1R0);
  matrix[k] = tmp;
  ind[k++]  = mmgR0;

  tmp = -thx * (v100 + v1L0);
  matrix[k] = tmp;
  ind[k++]  = mmgL0;

  tmp = thy * (v200 + v20R);
  matrix[k] = tmp;
  ind[k++]  = mmg0R;

  tmp = -thy * (v200 + v20L);
  matrix[k] = tmp;
  ind[k++]  = mmg0L;

  matrix[k] = thx2;
  ind[k++]  = mmv1R0;

  matrix[k] = thy2;
  ind[k++]  = mmv20R;

  matrix[k] = -thx2;
  ind[k++]  = mmv1L0;

  matrix[k] = -thy2;
  ind[k++]  = mmv20L;

  tmp = g00 * (4. + thx * (v1R0 - v1L0) + thy * (v20R - v20L)) + tau4 * Func_0(tt, xx, yy);
  rhs[mm] = tmp;

  mm++;
  //V1
  matrix[mm] = MUv1;
  ind[mm]    = k;

  tmp = thx * (v100 + v1R0) - MU8x;
  matrix[k] = tmp;
  ind[k++]  = mmv1R0;

  tmp = thy32 * (v200 + v20R) - MU6y;
  matrix[k] = tmp;
  ind[k++]  = mmv10R;

  tmp = Max;
  matrix[k] = -tmp;
  ind[k++]  = mmgL0;

  matrix[k] = tmp;
  ind[k++]  = mmgR0;

  tmp = -thx * (v100 + v1L0) - MU8x;
  matrix[k] = tmp;
  ind[k++]  = mmv1L0;

  tmp = -thy32 * (v200 + v20L) - MU6y;
  matrix[k] = tmp;
  ind[k++]  = mmv10L;

  tmp1 = mu * exp (-g00);
  tmp = v100 * (6. + thy32 * (v20R - v20L))
      - (MUM - tmp1) * (thxx8 * (v1R0 - 2 * v100 + v1L0) + thyy6 * (v10R - 2 * v100 + v10L))
      + thxy * (v2RR + v2LL - v2RL - v2LR) * tmp1
      + tau6 * Func_1(tt, xx, yy, p_d->p_ro, p_d->mu);
  rhs[mm] = tmp;
  mm++;
  //V2
  matrix[mm] = MUv2;
  ind[mm]    = k;

  tmp = thx32 * (v100 + v1R0) - MU6x;
  matrix[k] = tmp;
  ind[k++]  = mmv2R0;

  tmp = thy * (v200 + v20R) - MU8y;
  matrix[k] = tmp;
  ind[k++]  = mmv20R;

  tmp = May;
  matrix[k] = -tmp;
  ind[k++]  = mmg0L;

  matrix[k] = tmp;
  ind[k++]  = mmg0R;

  tmp = -thx32 * (v100 + v1L0) - MU6x;
  matrix[k] = tmp;
  ind[k++]  = mmv2L0;

  tmp = -thy * (v200 + v20L) - MU8y;
  matrix[k] = tmp;
  ind[k++]  = mmv20L;

  tmp = v200 * (6. + thx32 * (v1R0 - v1L0))
      - (MUM - tmp1) * (thxx6 * (v2R0 - 2 * v200 + v2L0) + thyy8 * (v20R - 2 * v200 + v20L))
      + thxy * (v1RR + v1LL - v1RL - v1LR) * tmp1
      + tau6 * Func_2(tt, xx, yy, p_d->p_ro, p_d->mu);
  rhs[mm] = tmp;

  continue;
}
