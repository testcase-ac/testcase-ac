#include <cstdio>
using namespace std;

int add(int x, int y) {
  // sadly, the C++ standard does NOT define overflow for signed integers
  // the way one would expect: it is not guaranteed that (2^31 - 1) + 1 gives -2^31
  // hence we use 64-bit integers to guarantee this behavior of our code

  long long sum = (long long) x + (long long) y;
  long long MAX_INT = (1LL << 31) - 1;
  long long MIN_INT = - (1LL << 31);
  while (sum > MAX_INT) sum -= 1LL << 32;
  while (sum < MIN_INT) sum += 1LL << 32;
  return (int) sum;
}

bool is_prime(long long x) {
  if (x <= 1) return false;
  for (long long d = 2; d * d <= x; ++d) {
    if (x % d == 0) return false;
  }
  return true;
}

bool magic(int x) {
  if (x <= 1) return true;
  return is_prime(x);
}

int main() {

  // for (int x = -10; x <= 10; ++x) {
  //   printf("%d: %d\n", x, magic(x));
  // }

  int mmax = 2147483647;
  for (int b = 28; b <= 28; ++b) {
    int start = 2e9;
    for (int s = 1900000000; s >= 1879048192; --s) {

      printf("s = %d, b = %d\n", s, b);
      
      int where = s;
      int step = -(1LL << b);
      int best = where;
      while (step) {
        where = add(where,step);
        // printf("%d\n",where);
        if (where < best) { best=where; printf("*\n"); }
        if (!magic(where)) break;
      }

    }
  }

}
