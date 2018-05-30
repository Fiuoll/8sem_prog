// bot node
if (st[i] == 5)
{
  //G
  Q_SetLen (&A, mm, 3);

  tmp = 2. - thy * v200;
  Q_SetEntry (&A, mm, 0, mmg00, tmp);
  tmp = thy * v20R;
  Q_SetEntry (&A, mm, 1, mmg0R, tmp);
  Q_SetEntry (&A, mm, 2, mmv20R, thy2);

  tmp = 2 * g00 + thy * g00 * (v20R - v200)
      + thy * (
               - 2.5 * g0R * v20R
               + 2 * g_2T * v2_2T
               - 0.5 * g_3T * v2_3T
               + (2 - g00) * (
                              - 2.5 * v20R
                              + 2 * v2_2T
                              - 0.5 * v2_3T))
      + tau2 * Func_0 (tt, xx, yy);
  V_SetCmp (&b, mm, tmp);

  // V1
  mm++;
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv100, 1);
  V_SetCmp (&b, mm, 0);

  // V2
  mm++;
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv200, 1);
  V_SetCmp (&b, mm, 0);

  continue;
}
