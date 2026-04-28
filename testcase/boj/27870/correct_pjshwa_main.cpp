#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int B2[MAX + 1], B3[MAX + 1], B4[MAX + 1];
int C2[MAX + 1], C3[MAX + 1], C4[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  vector<tuple<int, int, int, int>> D;
  for (int i = 0; i < M; i++) {
    int p, x, q, y; cin >> p >> x >> q >> y;
    D.emplace_back(p, q, x, y);
  }
  sort(D.begin(), D.end());

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    memset(B2, 0, sizeof(B2)); memset(C2, 0, sizeof(C2));
    memset(B3, 0, sizeof(B3)); memset(C3, 0, sizeof(C3));
    memset(B4, 0, sizeof(B4)); memset(C4, 0, sizeof(C4));

    for (auto& [p, q, x, y] : D) {
      if (p == 1 && x == i) {
        if (q == 2) B2[y] = 1;
        if (q == 3) B3[y] = 1;
        if (q == 4) B4[y] = 1;
      }
    }

    vector<pii> D23, D24, D34;
    for (auto& [p, q, x, y] : D) {
      if (p == 2 && q == 3) {
        if (B2[x] || B3[y]) continue;
        D23.emplace_back(x, y);
      }
      if (p == 2 && q == 4) {
        if (B2[x] || B4[y]) continue;
        D24.emplace_back(x, y);
      }
      if (p == 3 && q == 4) {
        if (B3[x] || B4[y]) continue;
        D34.emplace_back(x, y);
      }
    }

    ll z2 = N, z3 = N, z4 = N;
    for (int j = 1; j <= N; j++) {
      if (B2[j]) z2--;
      if (B3[j]) z3--;
      if (B4[j]) z4--;
    }

    ans += z2 * z3 * z4;
    
    for (auto& [x, y] : D23) {
      ans -= z4;
      C2[x]++; C3[y]++;
    }

    for (auto& [x, y] : D24) {
      ans -= z3 - C2[x];
      C4[y]++;
    }

    for (auto& [x, y] : D34) {
      ans -= z2 - C3[x] - C4[y];
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
