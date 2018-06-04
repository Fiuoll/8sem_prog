// exit
if (st[i] == 3)
{
  //G
  Q_SetLen (&A, mm, 4);

  tmp = 2. - thy * v200;
  Q_SetEntry (&A, mm, 0, mmg00, tmp);
  tmp = thy * v20R;
  Q_SetEntry (&A, mm, 1, mmg0R, tmp);
  Q_SetEntry (&A, mm, 2, mmv20R, thy2);
  Q_SetEntry (&A, mm, 3, mmv200, -thy2);

  tmp = 2 * g00 + thy * g00 * (v20R - v200)
      + thy * (g00 * v200
               - 2.5 * g0R * v20R
               + 2 * g_2T * v2_2T
               - 0.5 * g_3T * v2_3T
               + (2 - g00) * (  v200
                              - 2.5 * v20R
                              + 2 * v2_2T
                              - 0.5 * v2_3T))
      + tau2 * Func_0 (tt, xx, yy);
  V_SetCmp (&b, mm, tmp);

  mm++;
  //V1
  Q_SetLen (&A, mm, 1);
  Q_SetEntry (&A, mm, 0, mmv100, 1);
  V_SetCmp (&b, mm, 0);

  mm++;
  //V2
  if (RELEASE)
    {
      if (v20R < 0)
        {
          Q_SetLen (&A, mm, 2);
          Q_SetEntry (&A, mm, 0, mmv200, 1);
          Q_SetEntry (&A, mm, 1, mmv20R, -1);
          tmp = 0;
          V_SetCmp (&b, mm, tmp);
        }
      else
        {

          Q_SetLen (&A, mm, 1);
          Q_SetEntry (&A, mm, 0, mmv200, 1);
          V_SetCmp (&b, mm, 0);
        }
    }
  else
    {
      Q_SetLen (&A, mm, 1);
      Q_SetEntry (&A, mm, 0, mmv200, 1);
      V_SetCmp (&b, mm, 0);
    }

  continue;
}
