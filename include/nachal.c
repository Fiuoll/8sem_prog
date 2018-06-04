for (i = 0; i < n; i++)
{
  if (st[i] == 0 || !RELEASE)
    {
      G[i] = sm_g(0, X[i], Y[i]);
      V1[i] = sm_vx(0, X[i], Y[i]);
      V2[i] = sm_vy(0, X[i], Y[i]);
    }
  else
    {
      G[i]  = 1;
      V1[i] = 0;
      V2[i] = 0;
    }

  if (st[i] == 4)
    {
      G[i] = inv_g(0);
      V1[i] = inv_v1(0);
      V2[i] = 0;
    }
}
