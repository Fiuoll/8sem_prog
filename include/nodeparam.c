//          mmg00 = mm;
          mmv100 = mm + 1;
          mmv200 = mm + 2;

          mmgL0 = mm - 3;
          mmv1L0 = mm - 2;
          mmv2L0 = mm - 1;
          mmgR0 = mm + 3;
          mmv1R0 = mm + 4;
          mmv2R0 = mm + 5;
          mmg0L = 3 * M0L[i] + LASPACK;
          mmv10L = mmg0L + 1;
          mmv20L = mmv10L + 1;
          mmg0R = 3 * M0R[i] + LASPACK;
          mmv10R = mmg0R + 1;
          mmv20R = mmv10R + 1;

          g00 = G[i];
          gL0 = G[get_safe (i - 1, n)];
          gR0 = G[get_safe (i + 1, n)];
          g0L = G[get_safe (M0L[i], n)];
          g0R = G[get_safe (M0R[i], n)];
//          gLL = G[get_safe (M0L[i] - 1, n)];
//          gRL = G[get_safe (M0L[i] + 1, n)];
//          gLR = G[get_safe (M0R[i] - 1, n)];
//          gRR = G[get_safe (M0R[i] + 1, n)];

          v100 = V1[i];
          v1L0 = V1[get_safe (i - 1, n)];
          v1R0 = V1[get_safe (i + 1, n)];
          v10L = V1[get_safe(M0L[i], n)];
          v10R = V1[get_safe (M0R[i], n)];
          v1LL = V1[get_safe (M0L[i] - 1, n)];
          v1RL = V1[get_safe (M0L[i] + 1, n)];
          v1LR = V1[get_safe (M0R[i] - 1, n)];
          v1RR = V1[get_safe (M0R[i] + 1, n)];

          v200 = V2[i];
          v2L0 = V2[get_safe (i - 1, n)];
          v2R0 = V2[get_safe (i + 1, n)];
          v20L = V2[get_safe (M0L[i], n)];
          v20R = V2[get_safe (M0R[i], n)];
          v2LL = V2[get_safe (M0L[i] - 1, n)];
          v2RL = V2[get_safe (M0L[i] + 1, n)];
          v2LR = V2[get_safe (M0R[i] - 1, n)];
          v2RR = V2[get_safe (M0R[i] + 1, n)];

          g_2R = G[get_safe (i + 2, n)];
          g_3R = G[get_safe (i + 3, n)];
          v1_2R = V1[get_safe (i + 2, n)];
          v1_3R = V1[get_safe (i + 3, n)];
//          v2_2R = V2[get_safe (i + 2, n)];
//          v2_3R = V2[get_safe (i + 3, n)];

          g_2L = G[get_safe (i - 2, n)];
          g_3L = G[get_safe (i - 3, n)];
          v1_2L = V1[get_safe (i - 2, n)];
          v1_3L = V1[get_safe (i - 3, n)];
//          v2_2L = V2[get_safe (i - 2, n)];
//          v2_3L = V2[get_safe (i - 3, n)];

          g_2T = G[get_safe (M0R[get_safe (M0R[i], n)], n)];
          g_3T = G[get_safe (M0R[get_safe (M0R[get_safe(M0R[i], n)], n)], n)];
//          v1_2T = V1[get_safe (M0R[M0R[i]], n)];
//          v1_3T = V1[get_safe (M0R[M0R[M0R[i]]], n)];
          v2_2T = V2[get_safe (M0R[get_safe (M0R[i], n)], n)];
          v2_3T = V2[get_safe (M0R[get_safe (M0R[get_safe(M0R[i], n)], n)], n)];

          g_2B = G[get_safe (M0L[get_safe (M0L[i], n)], n)];
          g_3B = G[get_safe (M0L[get_safe (M0L[get_safe(M0L[i], n)], n)], n)];
//          v1_2B = V1[get_safe (M0L[M0L[i]], n)];
//          v1_3B = V1[get_safe (M0L[M0L[M0L[i]]], n)];
          v2_2B = V2[get_safe (M0L[get_safe (M0L[i], n)], n)];
          v2_3B = V2[get_safe (M0L[get_safe (M0L[get_safe(M0L[i], n)], n)], n)];

          xx = X[i];
          yy = Y[i];
