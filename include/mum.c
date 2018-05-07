{
  MUM = exp (- min (G, n));
  MU8x = 8 * tau * MUM / hx / hx;
  MU8y = 8 * tau * MUM / hy / hy;
  MU6x = 6 * tau * MUM / hx / hx;
  MU6y = 6 * tau * MUM / hy / hy;
  MUv1 = 6. + tau * MUM * (16 / hx / hx + 12 / hy / hy);
  MUv2 = 6. + tau * MUM * (16 / hy / hy + 12 / hx / hx);
}
