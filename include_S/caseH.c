


if (st[i] == 7)
{
  Q_SetLen(&AH, mmg00, 1);
  Q_SetEntry (&AH, mmg00, 0, mmg00, 1);
  V_SetCmp (&bH, mmg00, g00);
}
else
{
  k = 1;
  if (v1s2 < 0)
  {
   if (!is_zero (v1s2R))
     k++;
  }
 else if (!is_zero (v1s2))
     k++;

  if (v2s1 < 0)
  {
    if (!is_zero (v2s1T))
      k++;
  }
 else if (!is_zero (v2s1))
     k++;

  Q_SetLen(&AH, mmg00, k);
  tmp = 1;

  k = 1;

  if (v1s2 < 0)
   {
    if (!is_zero (v1s2R))
      Q_SetEntry (&AH, mmg00, k++, mmgR0, thx * v1s2R);
    tmp += -thx * v1s2;
   }
  else
   {
     if (!is_zero (v1s2))
       Q_SetEntry (&AH, mmg00, k++, mmgL0, -thx * v1s2);
    tmp += thx * v1s2R;

    if (st_H[i] == 4 && RELEASE)
      tmp += inv_g (tt);
   }

  if (v2s1 < 0)
   {
     if (!is_zero (v2s1T))
       Q_SetEntry (&AH, mmg00, k++, mmg0R, thy * v2s1T);
    tmp += -thy * v2s1;
   }
  else
   {
    if (!is_zero (v2s1))
      Q_SetEntry (&AH, mmg00, k++, mmg0L, -thy * v2s1);
    tmp += thy * v2s1T;
   }
  Q_SetEntry (&AH, mmg00, 0, mmg00, tmp + tau * Func_0 (tt, xx, yy));

  V_SetCmp (&bH, mmg00, g00);
}
