// corner
if (st[i] == 7)
{
  //G
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mm, 1);
  V_SetCmp (&b, mm, sm_g (tt, xx, yy));

  mm++;
  //V1
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mm, 1);
  V_SetCmp (&b, mm, 0);

  mm++;
  // V2
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mm, 1);
  V_SetCmp (&b, mm, 0);

  continue;
}
