#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve() {
  vector<tuple<string, int, int>> A;
  for (int i = 0; i < N; ++i) {
    string name; int p, a, b, c, d, e, f, s, m;
    cin >> name >> p >> a >> b >> c >> d >> e >> f >> s >> m;
    int time = a + b + c + m * (d + e);
    int profit = f * s * m - p;
    A.emplace_back(name, time, profit);
  }

  // sort by (profit / time)
  sort(A.begin(), A.end(), [&](auto &a, auto &b) {
    auto [na, ta, pa] = a; auto [nb, tb, pb] = b;
    ll lhs = (ll)pa * tb, rhs = (ll)pb * ta;
    if (lhs != rhs) return lhs > rhs;
    return na < nb;
  });
  for (auto& [name, _time, _profit] : A) cout << name << '\n';
  cout << "#\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
