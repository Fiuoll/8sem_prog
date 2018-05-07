// entry node
if (st[i] == 4)
{
  //G
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mm, 1);
  V_SetCmp (&b, mm, sm_g (tt, xx, yy));

  //V1
  mm++;
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv100, 1);
  V_SetCmp (&b, mm, sm_vx (tt, xx, yy));

  // V2
  mm++;
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv200, 1);
  V_SetCmp (&b, mm, 0);
}
