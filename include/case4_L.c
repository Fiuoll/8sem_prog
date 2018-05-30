// entry node
if (st[i] == 4)
{
  //G
  Q_SetLen (&A, mm, 4);

  tmp = 2. - thx * v100;
  Q_SetEntry (&A, mm, 0, mmg00, tmp);
  tmp = thx * v1R0;
  Q_SetEntry (&A, mm, 1, mmgR0, tmp);
  Q_SetEntry (&A, mm, 2, mmv1R0, thx2);
  Q_SetEntry (&A, mm, 3, mmv100, -thx2);

  tmp = 2 * g00 + thx * g00 * (v1R0 - v100)
      + thx * ( g00 * v100
               - 2.5 * gR0 * v1R0
               + 2 * g_2R * v1_2R
               - 0.5 * g_3R * v1_3R
               + (2 - g00) * (  v100
                              - 2.5 * v1R0
                              + 2 * v1_2R
                              - 0.5 * v1_3R))
      + tau2 * Func_0 (tt, xx, yy);
  V_SetCmp (&b, mm, tmp);

//  Q_SetLen (&A, mm, 1);
//  Q_SetEntry (&A, mm, 0, mm, 1);
//  V_SetCmp (&b, mm, sm_g (tt, xx, yy));

  //V1
  mm++;
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv100, 1);
  V_SetCmp (&b, mm, 0.);//sm_vx (tt, xx, yy));

  // V2
  mm++;
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv200, 1);
  V_SetCmp (&b, mm, 0);
}
