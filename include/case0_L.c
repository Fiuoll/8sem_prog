// inner node
if (st[i] == 0)
{
  //G
  Q_SetLen(&A, mm, 9);
  Q_SetEntry (&A, mm, 0, mm, 4.);
  tmp = thx * (v100 + v1R0);
  Q_SetEntry (&A, mm, 1, mmgR0, tmp);
  tmp = -thx * (v100 + v1L0);
  Q_SetEntry (&A, mm, 2, mmgL0, tmp);
  tmp = thy * (v200 + v20R);
  Q_SetEntry (&A, mm, 3, mmg0R, tmp);
  tmp = -thy * (v200 + v20L);
  Q_SetEntry (&A, mm, 4, mmg0L, tmp);
  Q_SetEntry (&A, mm, 5, mmv1R0, thx2);
  Q_SetEntry (&A, mm, 6, mmv20R, thy2);
  Q_SetEntry (&A, mm, 7, mmv1L0, -thx2);
  Q_SetEntry (&A, mm, 8, mmv20L, -thy2);

  tmp = g00 * (4. + thx * (v1R0 - v1L0) + thy * (v20R - v20L))
      + tau4 * Func_0(tt, xx, yy);
  V_SetCmp (&b, mm, tmp);

  mm++;
  //V1
  Q_SetLen (&A, mm, 7);
  Q_SetEntry (&A, mm, 0, mm, MUv1);
  tmp = thx * (v100 + v1R0) - MU8x;
  Q_SetEntry (&A, mm, 1, mmv1R0, tmp);
  tmp = thy32 * (v200 + v20R) - MU6y;
  Q_SetEntry (&A, mm, 2, mmv10R, tmp);
  tmp = Max;
  Q_SetEntry (&A, mm, 3, mmgL0, -tmp);
  Q_SetEntry (&A, mm, 4, mmgR0, tmp);
  tmp = -thx * (v100 + v1L0) - MU8x;
  Q_SetEntry (&A, mm, 5, mmv1L0, tmp);
  tmp = -thy32 * (v200 + v20L) - MU6y;
  Q_SetEntry (&A, mm, 6, mmv10L, tmp);

  tmp1 = mu * exp (-g00);
  tmp = v100 * (6. + thy32 * (v20R - v20L))
      - (MUM - tmp1) * (thxx8 * (v1R0 - 2 * v100 + v1L0) + thyy6 * (v10R - 2 * v100 + v10L))
      + thxy * (v2RR + v2LL - v2RL - v2LR) * tmp1
      + tau6 * Func_1(tt, xx, yy, pressure, mu);
  V_SetCmp (&b, mm, tmp);

  mm++;
  //V2
  Q_SetLen (&A, mm, 7);
  Q_SetEntry (&A, mm, 0, mm, MUv2);
  tmp = thx32 * (v100 + v1R0) - MU6x;
  Q_SetEntry (&A, mm, 1, mmv2R0, tmp);
  tmp = thy * (v200 + v20R) - MU8y;
  Q_SetEntry (&A, mm, 2, mmv20R, tmp);
  tmp = May;
  Q_SetEntry (&A, mm, 3, mmg0L, -tmp);
  Q_SetEntry (&A, mm, 4, mmg0R, tmp);
  tmp = -thx32 * (v100 + v1L0) - MU6x;
  Q_SetEntry (&A, mm, 5, mmv2L0, tmp);
  tmp = -thy * (v200 + v20L) - MU8y;
  Q_SetEntry (&A, mm, 6, mmv20L, tmp);

  tmp = v200 * (6. + thx32 * (v1R0 - v1L0))
      - (MUM - tmp1) * (thxx6 * (v2R0 - 2 * v200 + v2L0) + thyy8 * (v20R - 2 * v200 + v20L))
      + thxy * (v1RR + v1LL - v1RL - v1LR) * tmp1
      + tau6 * Func_2(tt, xx, yy, pressure, mu);
  V_SetCmp (&b, mm, tmp);

  continue;
}
