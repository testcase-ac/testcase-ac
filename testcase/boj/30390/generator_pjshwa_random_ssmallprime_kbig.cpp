#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using ll = long long;

bool is_prime(ll n) {
  if (n <= 1) return false;
  for (ll f = 2; f * f <= n; ++f) {
    if (n % f == 0) return false;
  }
  return true;
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  ll S = rnd.next(1LL, (ll)1e3);
  while (!is_prime(S)) --S;

  ll A = rnd.next(1LL, S - 1);
  ll B = S - A;

  ll K = rnd.next(1LL, (ll)1e3);

  cout << A << ' ' << B << ' ' << K << '\n';
}
