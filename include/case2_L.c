// right wall

if (st[i] == 2)
{
  //G
  Q_SetLen (&A, mm, 3);

  Q_SetEntry (&A, mm, 0, mmg00, 2.);
  tmp = - thx * v1L0;
  Q_SetEntry (&A, mm, 1, mmgL0, tmp);
  Q_SetEntry (&A, mm, 2, mmv1L0, -thx2);

  tmp = 2 * g00 - thx * g00 * v1L0
      - thx * (  //g00 * v100
               - 2.5 * gL0 * v1L0
               + 2 * g_2L * v1_2L
               - 0.5 * g_3L * v1_3L
               + (2 - g00) * (
                              - 2.5 * v1L0
                              + 2 * v1_2L
                              - 0.5 * v1_3L))
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
