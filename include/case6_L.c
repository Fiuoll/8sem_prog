// top node
if (st[i] == 6)
{
  //G
  Q_SetLen (&A, mm, 3);

  tmp = 2. + thy * v200;
  Q_SetEntry (&A, mm, 0, mmg00, tmp);
  tmp = - thy * v20L;
  Q_SetEntry (&A, mm, 1, mmg0L, tmp);
  Q_SetEntry (&A, mm, 2, mmv20L, -thy2);

  tmp = 2 * g00 - thy * g00 * v20L
      - thy * (
               - 2.5 * g0L * v20L
               + 2 * g_2B * v2_2B
               - 0.5 * g_3B * v2_3B
               + (2 - g00) * (
                              - 2.5 * v20L
                              + 2 * v2_2B
                              - 0.5 * v2_3B))
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
