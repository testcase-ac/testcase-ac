#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k; cin >> n >> k;

  map<int, int> t; vector<pii> a(n);
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    a[i] = {x, i};

    t[x]++;
    if (t[x] > n / 2) return cout << "-1\n", []{}();
  }

  for (int l = 0; l < n / 2; l++) {
    vector<tuple<int, int, int, int>> C;
    for (int i = 0; i < a.size() - 1; i++) {
      auto [ax, ai] = a[i]; auto [bx, bi] = a[i + 1];
      if (ax == bx) continue;

      int av = t[ax], bv = t[bx];
      if (av < bv) swap(av, bv);

      C.push_back({av, bv, ai, bi});
    }
    sort(C.begin(), C.end(), greater<>());

    auto [av, bv, ai, bi] = C[0];
    cout << ai + 1 << ' ' << bi + 1 << '\n';

    vector<pii> na;
    for (int i = 0; i < a.size(); i++) {
      auto [x, j] = a[i];
      if (j == ai || j == bi) t[x]--;
      else na.push_back(a[i]);
    }
    a = na;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
