#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
pll v[MAX];
bool ej[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) cin >> v[i].first >> v[i].second;

  vector<tll> stops;
  for (int i = 0; i < m; i++) {
    auto [a, b] = v[i];
    if (a > b) b += n;
    stops.push_back({a, b, i});
  }
  for (int i = 0; i < m; i++) {
    auto [a, b] = v[i];
    if (a > b) b += n;
    stops.push_back({(ll)a + n, (ll)b + n, i});
  }
  sort(stops.begin(), stops.end(), [] (tll a, tll b) {
    auto& [ax, ay, ai] = a;
    auto& [bx, by, bi] = b;
    if (ax == bx) return ay > by;
    else return ax < bx;
  });

  stack<pll> s;
  for (auto& [a, b, i] : stops) {
    if (!s.empty()) {
      auto& [ta, tb] = s.top();
      if (ta <= a && b <= tb) {
        ej[i] = true;
        continue;
      }
      else s.push({a, b});
    }
    else s.push({a, b});
  }

  for (int i = 0; i < m; i++) {
    if (ej[i]) continue;
    cout << i + 1 << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
