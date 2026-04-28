#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e5;
ll a[MAX];

int main() {
  fast_io();

  ll n, c;
  cin >> n >> c;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll cmin = a[0], cmax = a[0];
  int cmini = 0, cmaxi = 0;
  cout << "0 ";

  for (ll i = 1; i < n; i++) {
    cout << max(0LL, max(abs(a[i] - cmin) - c * (i - cmini), abs(a[i] - cmax) - c * (i - cmaxi))) << " ";

    if (a[i] - cmin < (i - cmini) * c) {
      cmin = a[i];
      cmini = i;
    }
    if (cmax - a[i] < (i - cmaxi) * c) {
      cmax = a[i];
      cmaxi = i;
    }
  }
  cout << '\n';
}
