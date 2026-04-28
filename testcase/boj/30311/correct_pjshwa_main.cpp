#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int S[MAXN + 1];

void solve() {
  int n, k, x; cin >> n >> k;
  while (k--) {
    for (int i = 1; i <= n; ++i) cin >> x, S[x] += i;
  }
  vector<pii> V;
  for (int i = 1; i <= n; ++i) V.emplace_back(S[i], i);
  sort(V.begin(), V.end());
  for (auto& p : V) cout << p.second << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
