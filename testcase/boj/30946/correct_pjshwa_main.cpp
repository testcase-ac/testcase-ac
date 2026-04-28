#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

double dist(pii a, pii b) {
  int dx = a.first - b.first, dy = a.second - b.second;
  return sqrt(dx * dx + dy * dy);
}

void solve() {
  int N; string S; cin >> N >> S;

  vector<pii> B, G;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    if (S[i] == 'B') B.emplace_back(x, y);
    else G.emplace_back(x, y);
  }

  int Z1 = B.size(), Z2 = G.size();
  assert(Z1 % 2 == 0 && Z2 % 2 == 0);

  double ans = 0;
  for (int i = 0; i < Z1; ++i) ans += dist(B[i], B[(i + Z1 / 2) % Z1]);
  for (int i = 0; i < Z2; ++i) ans += dist(G[i], G[(i + Z2 / 2) % Z2]);
  cout << fixed << setprecision(10) << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
