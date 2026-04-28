#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int a[MAXN];

void solve() {
  int n; cin >> n;

  int maxb = -1, maxi;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (maxb < a[i]) maxb = a[i], maxi = i;
  }

  ll tar;
  if (maxi == n - 1) tar = (1LL << a[maxi]) - 1;
  else {
    int d = a[maxi] - a[maxi + 1];

    tar = (1LL << (d + 1)) - 1; int p = d + 2;
    while (__builtin_popcountll(tar) < a[maxi]) {
      tar += (1LL << p);
      p++;
    }
  }

  int ok = 1;
  for (int i = 0; i < n; ++i) {
    ll x = tar + (i - maxi);
    if (x < 0) return cout << "-1\n", void();
    ok &= __builtin_popcountll(tar + (i - maxi)) == a[i];
  }

  if (ok) cout << tar - maxi << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
