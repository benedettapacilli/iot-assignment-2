#include "utilities.h"

//Source: https://forum.arduino.cc/t/some-experiments-with-fast-greatest-common-denominator-algorithms/697475
unsigned int gcd_ctz(unsigned int u, unsigned int v) {
  int shift;
  if (u == 0) return v;
  if (v == 0) return u;
  shift = __builtin_ctzl(u | v);
  u >>= __builtin_ctzl(u);
  do {
    v >>= __builtin_ctzl(v);
    if (u > v) {
      unsigned int t = v;
      v = u;
      u = t;
    }
    v = v - u;
  } while  (v != 0);
  return u << shift;
}