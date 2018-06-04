for (i = 0; i < n; i++)
{
  if (st[i] == 0)
    {
      V1[i] = sm_vx(0, X[i], Y[i]);
      V2[i] = sm_vy(0, X[i], Y[i]);
    }
  else
    {
      V1[i] = 0;
      V2[i] = 0;
    }
}
for (i = 0; i < nH; i++)
{
  G[i] = sm_g(0, X_H[i], Y_H[i]);
}
