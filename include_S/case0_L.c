// inner node
if (st[i] == 0)
{
  //V1
  if (is_zero (hss_))
    {
      Q_SetLen (&A, mmv100, 1);
      Q_SetEntry (&A, mmv100, 0, mmv100, 1.);
      V_SetCmp (&b, mmv100, 0.);

      Q_SetLen (&A, mmv200, 1);
      Q_SetEntry (&A, mmv200, 0, mmv200, 1.);
      V_SetCmp (&b, mmv200, 0.);

    }
  else
    {
      Q_SetLen(&A, mmv100, 7);
      tmp = hss_ + 2. * mu * (4. / 3. * thxx + thyy);

      if (v100 < 0)
        {
          //V1
          tmp += - thx05 * (v100 * hs2 + hs2L * v1L0);
          Q_SetEntry (&A, mmv100, 0, mmv100, tmp);
          //V2
          Q_SetEntry (&A, mmv100, 1, mmv200, -thy05 * (v100 * hs1 + v10L * hs1B));
          //V2T
          Q_SetEntry (&A, mmv100, 2, mmv20R, thy05 * (v10R * hs1T + hs1 * v100));
          //V1R
          Q_SetEntry (&A, mmv100, 3, mmv1R0, thx05 * (v1R0 * hs2R + hs2 * v100) - 4. / 3. * mu * thxx);
          //V1L
          Q_SetEntry (&A, mmv100, 4, mmv1L0, - 4. / 3. * mu * thxx);
          //V1T
          Q_SetEntry (&A, mmv100, 5, mmv10R, - mu * thyy);
          //V1B
          Q_SetEntry (&A, mmv100, 6, mmv10L, - mu * thyy);
          //V1
        }
      else
        {
          //V1
          tmp += thx05 * (v1R0 * hs2 + hs2L * v100);
          Q_SetEntry (&A, mmv100, 0, mmv100, tmp);
          //V2
          Q_SetEntry (&A, mmv100, 1, mmv200, thy05 * (v100 * hs1B + v10R * hs1));
          //V2B
          Q_SetEntry (&A, mmv100, 2, mmv20L, -thy05 * (v10L * hs1BB + hs1B * v100));
          //V1R
          Q_SetEntry (&A, mmv100, 3, mmv1R0, - 4. / 3. * mu * thxx);
          //V1L
          Q_SetEntry (&A, mmv100, 4, mmv1L0, - thx05 * (v100 * hs2L + v1L0 * hs2LL) - 4. / 3. * mu * thxx);
          //V1T
          Q_SetEntry (&A, mmv100, 5, mmv10R, - mu * thyy);
          //V1B
          Q_SetEntry (&A, mmv100, 6, mmv10L, - mu * thyy);
        }

      tmp = hss * v100 - gamma / (gamma - 1) * hss_ * thx * (pow (hs2, gamma - 1) - pow (hs2L, gamma - 1))
          + mu / 12. * thxy * (v2RR - v2RL - v2LR + v2LL)
          + Func_1 (tt, xx, yy, pressure, mu) * hss_ * tau;
      V_SetCmp (&b, mmv100, tmp);

      //V2
      Q_SetLen(&A, mmv200, 7);
      tmp = hss_ + 2. * mu * (thxx + 4. / 3. * thyy);
      if (v200 < 0)
        {
          //V2
          tmp += - thy05 * (v200 * hs1 + hs1B * v20L);
          Q_SetEntry (&A, mmv200, 0, mmv200, tmp);
          //V1
          Q_SetEntry (&A, mmv200, 1, mmv100, -thx05 * (v200 * hs2 + v2L0 * hs2L));
          //V1R
          Q_SetEntry (&A, mmv200, 2, mmv1R0, thx05 * (v2R0 * hs2R + hs2 * v200));
          //V2R
          Q_SetEntry (&A, mmv200, 3, mmv2R0, - mu * thxx);
          //V2L
          Q_SetEntry (&A, mmv200, 4, mmv2L0, - mu * thxx);
          //V2T
          Q_SetEntry (&A, mmv200, 5, mmv20R, thy05 * (v20R * hs1T + v200 * hs1) - 4. / 3. * mu * thyy);
          //V2B
          Q_SetEntry (&A, mmv200, 6, mmv20L, - 4. / 3. * mu * thyy);
        }
      else
        {
          //V2
          tmp += thy05 * (v20R * hs1 + hs1B * v200);
          Q_SetEntry (&A, mmv200, 0, mmv200, tmp);
          //V1
          Q_SetEntry (&A, mmv200, 1, mmv100, thx05 * (v200 * hs2L + v2R0 * hs2));
          //V1L
          Q_SetEntry (&A, mmv200, 2, mmv1L0, -thx05 * (v2L0 * hs2LL + hs2L * v200));
          //V2R
          Q_SetEntry (&A, mmv200, 3, mmv2R0, - mu * thxx);
          //V2L
          Q_SetEntry (&A, mmv200, 4, mmv2L0, - mu * thxx);
          //V2T
          Q_SetEntry (&A, mmv200, 5, mmv20R, - 4. / 3. * mu * thyy);
          //V2B
          Q_SetEntry (&A, mmv200, 6, mmv20L, - thy05 * (v20L * hs1BB + v200 * hs1B) - 4. / 3. * mu * thyy);
        }

      tmp = hss * v200 - gamma / (gamma - 1) * hss_ * thy * (pow (hs1, gamma - 1) - pow (hs1B, gamma - 1))
          + mu / 12. * thxy * (v1RR - v1RL - v1LR + v1LL)
          + Func_2 (tt, xx, yy, pressure, mu) * hss_ * tau;
      V_SetCmp (&b, mmv200, tmp);
    }


}
