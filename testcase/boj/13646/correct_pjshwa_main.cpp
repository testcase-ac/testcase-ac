#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll phi(ll n) {
  ll result = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0)
        n /= i;
      result -= result / i;
    }
  }
  if (n > 1)
    result -= result / n;
  return result;
}

int main() {
  ll n;
  while (scanf("%lld", &n) == 1) printf("%lld\n", phi(n) / 2);
}
