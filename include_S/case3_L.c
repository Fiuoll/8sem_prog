// exit
if (st[i] == 3)
{
  //V1
  Q_SetLen (&A, mmv100, 1);
  Q_SetEntry (&A, mmv100, 0, mmv100, 1.);
  V_SetCmp (&b, mmv100, 0.);

  //V2
  if (RELEASE && 0)
    {
      Q_SetLen (&A, mmv200, 2);
      Q_SetEntry (&A, mmv200, 0, mmv200, 1);
      Q_SetEntry (&A, mmv200, 1, mmv20R, -1);
      tmp = 0;
      V_SetCmp (&b, mmv200, tmp);

    }
  else
    {
      Q_SetLen (&A, mmv200, 1);
      Q_SetEntry (&A, mmv200, 0, mmv200, 1);
      V_SetCmp (&b, mmv200, 0);
    }

}
