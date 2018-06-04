          g00 = G[i];

          xx = X_H[i];
          yy = Y_H[i];


          mmg00 = i + LASPACK;
          mmgL0 = mmg00 - 1;
          mmgR0 = mmg00 + 1;
          if (st_H[i] != 3 && st_H[i] != 5 && st[i] != 7)
            mmg0L = M0L_H[i] + LASPACK;
          if (st_H[i] != 6 && st[i] != 7)
            mmg0R = M0R_H[i] + LASPACK;

          v1s2 = (V1[j] + V1[M0R[j]]) / 2;
          v1s2R = (V1[j + 1] + V1[M0R[j] + 1]) / 2;
          v2s1 = (V2[j] + V2[j + 1]) / 2;
          v2s1T = (V2[M0R[j]] + V2[M0R[j] + 1]) / 2;



