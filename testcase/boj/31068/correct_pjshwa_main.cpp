#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
pii A[MAXN + 1];

void solve() {
  int N; cin >> N;

  multiset<int> ys;
  for (int i = 1; i <= N; ++i) {
    int x, y; cin >> x >> y;
    A[i] = {x, y}; ys.insert(y);
  }
  sort(A + 1, A + N + 1);

  vector<int> P; int ymax = 0;
  for (int i = 1; i < N; ++i) {
    auto [x, y] = A[i];
    ymax = max(ymax, y);

    // erase one y from ys
    auto it = ys.find(y);
    ys.erase(it);

    // remaining should all be ge than ymax
    if (x != A[i + 1].first && *ys.begin() > ymax) P.push_back(i);
  }

  if (P.size() <= 1) return cout << "-1\n", void();

  auto f = [&](int i, int j) {
    int a = P[i], b = P[j] - P[i], c = N - P[j];
    return max({a, b, c}) - min({a, b, c});
  };

  int ans = N, j = 1, Z = P.size();
  for (int i = 0; i < Z; ++i) {
    while (j < Z - 1 && f(i, j) >= f(i, j + 1)) ++j;
    ans = min(ans, f(i, j));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
