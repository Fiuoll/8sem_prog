 // left node (gamma1-)
// | 0R RR
// | 00 R0
// | 0L RL

if (st[i] == 1)
{
  //G
  Q_SetLen (&A, mm, 3);

  Q_SetEntry (&A, mm, 0, mmg00, 2.);
  tmp = thx * v1R0;
  Q_SetEntry (&A, mm, 1, mmgR0, tmp);
  Q_SetEntry (&A, mm, 2, mmv1R0, thx2);

  tmp = 2 * g00 + thx * g00 * v1R0
      + thx * (
               - 2.5 * gR0 * v1R0
               + 2 * g_2R * v1_2R
               - 0.5 * g_3R * v1_3R
               + (2 - g00) * (
                              - 2.5 * v1R0
                              + 2 * v1_2R
                              - 0.5 * v1_3R))
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
