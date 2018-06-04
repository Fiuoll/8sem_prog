// bot node
if (st[i] == 5)
{
  //V1
  Q_SetLen (&A, mmv100, 1);
  Q_SetEntry (&A, mmv100, 0, mmv100, 1.);
  V_SetCmp (&b, mmv100, 0.);

  //V2
  Q_SetLen (&A, mmv200, 1);
  Q_SetEntry (&A, mmv200, 0, mmv200, 1.);
  V_SetCmp (&b, mmv200, 0.);
}
