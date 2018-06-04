          mmg00 = 3 * i + LASPACK;
          mmv100 = mm + 1;
          mmv200 = mm + 2;


          g00 = G[i];
          v100 = V1[i];
          v200 = V2[i];

          xx = X[i];
          yy = Y[i];

          mmgL0  = -1;
          mmv1L0 = -1;
          mmv2L0 = -1;
          mmgR0  = -1;
          mmv1R0 = -1;
          mmv2R0 = -1;
          mmg0L  = -1;
          mmv10L = -1;
          mmv20L = -1;
          mmg0R  = -1;
          mmv10R = -1;
          mmv20R = -1;

          switch (st[i])
          {
            case 0:
              mmgL0 = mmg00 - 3;
              mmgR0 = mmg00 + 3;

              mmv1L0 = mmv100 - 3;
              mmv2L0 = mmv200 - 3;

              mmv1R0 = mmv100 + 3;
              mmv2R0 = mmv200 + 3;

              mmg0L = 3 * M0L[i] + LASPACK;
              mmv10L = mmg0L + 1;
              mmv20L = mmv10L + 1;

              mmg0R = 3 * M0R[i] + LASPACK;
              mmv10R = mmg0R + 1;
              mmv20R = mmv10R + 1;

              g0L = G[M0L[i]];
              v10L = V1[M0L[i]];
              v20L = V2[M0L[i]];

              g0R = G[M0R[i]];
              v10R = V1[M0R[i]];
              v20R = V2[M0R[i]];

              gR0 = G[i + 1];
              v1R0 = V1[i + 1];
              v2R0 = V2[i + 1];

              gL0 = G[i - 1];
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
              break;
            case 1:
            case 4:
              mmgR0 = mm + 3;
              mmv1R0 = mm + 4;
              mmv2R0 = mm + 5;

              gR0 = G[i + 1];
              v1R0 = V1[i + 1];
              v2R0 = V2[i + 1];

              g_2R  = G[i + 2];
              v1_2R = V1[i + 2];

              g_3R  = G[i + 3];
              v1_3R = V1[i + 3];
              break;
            case 2:
              mmgL0 = mm - 3;
              mmv1L0 = mm - 2;
              mmv2L0 = mm - 1;

              gL0 = G[i - 1];
              v1L0 = V1[i - 1];
              v2L0 = V2[i - 1];

              g_2L  = G[i - 2];
              v1_2L = V1[i - 2];

              g_3L  = G[i - 3];
              v1_3L = V1[i - 3];
              break;
            case 3:
            case 5:
              mmg0R = 3 * M0R[i] + LASPACK;
              mmv10R = mmg0R + 1;
              mmv20R = mmv10R + 1;

              g0R = G[M0R[i]];
              v10R = V1[M0R[i]];
              v20R = V2[M0R[i]];

              g_2T  = G[M0R[M0R[i]]];
              v2_2T = V2[M0R[M0R[i]]];

              g_3T  = G[M0R[M0R[M0R[i]]]];
              v2_3T = V2[M0R[M0R[M0R[i]]]];
              break;
            case 6:
              mmg0L = 3 * M0L[i] + LASPACK;
              mmv10L = mmg0L + 1;
              mmv20L = mmv10L + 1;

              g0L = G[M0L[i]];
              v10L = V1[M0L[i]];
              v20L = V2[M0L[i]];

              g_2B = G[M0L[M0L[i]]];
              v2_2B = V2[M0L[M0L[i]]];

              g_3B = G[M0L[M0L[M0L[i]]]];
              v2_3B = V2[M0L[M0L[M0L[i]]]];
              break;
            case 7:
              break;
            default:
              printf ("IMPOSSIBLE!\n");
              return ;
          }
