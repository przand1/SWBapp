#include "mylib.h"

double power(float b, int e) {
  double n = 1.0;
  if (e > 0) {
    for (int i = 1; i <= e; i++) {
      n *= b;
    }
  }
  else if (e < 0) {
    for (int i = -1; i >= e; i--) {
      n /= b;
    }
  }
  return n;
}
