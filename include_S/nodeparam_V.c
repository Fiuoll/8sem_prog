

          mmv100 = 2 * i + LASPACK;
          mmv200 = mmv100 + 1;

          v100 = V1[i];
          v200 = V2[i];

          xx = X[i];
          yy = Y[i];

          if (st[i] == 0)
          {
            mmv1L0 = mmv100 - 2;
            mmv2L0 = mmv200 - 2;

            mmv1R0 = mmv100 + 2;
            mmv2R0 = mmv200 + 2;

            mmv10L = 2 * M0L[i] + LASPACK;
            mmv20L = mmv10L + 1;

            mmv10R = 2 * M0R[i] + LASPACK;
            mmv20R = mmv10R + 1;

            v10L = V1[M0L[i]];
            v20L = V2[M0L[i]];

            v10R = V1[M0R[i]];
            v20R = V2[M0R[i]];

            v1R0 = V1[i + 1];
            v2R0 = V2[i + 1];

            v1L0 = V1[i - 1];
            v2L0 = V2[i - 1];

            v1LL = V1[M0L[i] - 1];
            v2LL = V2[M0L[i] - 1];

            v1RL = V1[M0L[i] + 1];
            v2RL = V2[M0L[i] + 1];

            v1LR = V1[M0R[i] - 1];
            v2LR = V2[M0R[i] - 1];

            v1RR = V1[M0R[i] + 1];
            v2RR = V2[M0R[i] + 1];

            hss  = (G[j] + G[j - 1] + G[M0L_H[j]] + G[M0L_H[j - 1]]) / 4;
            hss_ = (H[j] + H[j - 1] + H[M0L_H[j]] + H[M0L_H[j - 1]]) / 4;
            hs2  = (H[j] + H[M0L_H[j]]) / 2;
            if (!is_zero (v1R0) && !is_zero (v2R0))
                hs2R = (H[j + 1] + H[M0L_H[j + 1]]) / 2;
            hs2L = (H[j - 1] + H[M0L_H[j - 1]]) / 2;
            hs1  = (H[j] + H[j - 1]) / 2;
            hs1B = (H[M0L_H[j]] + H[M0L_H[j - 1]]) / 2;
            if (!is_zero (v10R) && !is_zero (v20R))
              hs1T = (H[M0R_H[j]] + H[M0R_H[j - 1]]) / 2;

            if (fabs (v10L) < EPS)
              hs1BB = 0;
            else
              hs1BB = (H[M0L_H[M0L_H[j]]] + H[M0L_H[M0L_H[j]]]) / 2;

            if (fabs (v1L0) < EPS)
              hs2LL = 0;
            else
              hs2LL = (H[j - 2] + H[j - 2]) / 2;
          }
