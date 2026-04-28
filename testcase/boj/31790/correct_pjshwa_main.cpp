#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int B[MAXN + 1];

void solve() {
  int N, p; cin >> N >> p;
  for (int i = 1; i <= N; ++i) cin >> B[i];
  int maxb = (N - 1) / p + 1;

  for (int i = 1; i <= N; ++i) {
    ll x = B[i];
    if (x < B[i - 1] || x > B[i - 1] + 1) return cout << "NO\n", void();
    if (i > x * p || x > maxb) return cout << "NO\n", void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
