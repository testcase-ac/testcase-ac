#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, M, B;
  cin >> N >> M >> B;
  vector<pii> u, o;
  while (M--) {
    int pi, qi;
    cin >> pi >> qi;
    if (pi >= B) o.push_back({pi, qi});
    else u.push_back({pi, qi});
  }
  sort(u.begin(), u.end());

  int z = u.size();
  int li = 0, ri = z - 1;
  while (li < ri) {
    auto& [pli, qli] = u[li];
    auto& [pri, qri] = u[ri];

    if (pli + pri < B) li++;
    else {
      int use = min(qli, qri);
      o.push_back({pli + pri, use});
      qli -= use;
      qri -= use;

      if (qli == 0) li++;
      if (qri == 0) ri--;
    }
  }

  if (li == ri) {
    auto [pli, qli] = u[li];
    if (2 * pli >= B) o.push_back({2 * pli, qli / 2});
  }
  sort(o.begin(), o.end());

  ll ans = 0;
  for (auto [pi, qi] : o) {
    ll use = min(N, qi);
    ans += use * pi;
    N -= use;
  }

  if (N == 0) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
