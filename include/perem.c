double hx, hy, tau,
       thx, thy, /*thx05, thy05,*/ thx2, thy2, /*thx4, thy4,*/ thx32, thy32,
       tau2, tau4, tau6, thxx8, thxx6, thyy8, thyy6, thxy, Max, May, pressure;
double mu, MUM, MU8x, MU8y, MU6x, MU6y, MUv1, MUv2;

int mm, mmg00, mmgR0, mmgL0, mmg0R, mmg0L,
    mmv100, mmv1R0, mmv10R, mmv1L0, mmv10L/*, mmv1RR, mmv1LL, mmv1RL, mmv1LR*/,
    mmv200, mmv2R0, mmv20R, mmv2L0, mmv20L/*, mmv2RR, mmv2LL, mmv2LR, mmv2RL*/;
double g00, gR0, g0R, gL0, g0L,
       v100, v1R0, v10R, v1L0, v10L, v1RR, v1LL, v1LR, v1RL,
       v200, v2R0, v20R, v2L0, v20L, v2RR, v2LL, v2LR, v2RL;
double tmp, tt, xx, yy, tmp1;

double g_2R, g_3R, v1_2R, v1_3R, /*v2_2R, v2_3R,*/
       g_2L, g_3L, v1_2L, v1_3L, /*v2_2L, v2_3L,*/
       g_2T, g_3T, /*v1_2T, v1_3T,*/ v2_2T, v2_3T,
       g_2B, g_3B, /*v1_2B, v1_3B,*/ v2_2B, v2_3B;
