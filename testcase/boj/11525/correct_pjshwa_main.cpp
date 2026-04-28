#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll phi(ll n) {
  ll result = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int d[MAX + 1];

int main() {
  fast_io();

  d[1] = 2;
  for (int i = 2; i <= MAX; i++) d[i] = d[i - 1] + phi(i);

  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    int tc, n;
    cin >> tc >> n;
    cout << tc << ' ' << d[n] << '\n';
  }
}
