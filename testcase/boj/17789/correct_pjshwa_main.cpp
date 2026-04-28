#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
vector<int> s[MAX + 1], o[MAX + 1];

void solve() {
  int p, v;
  cin >> p >> v;

  for (int i = 1; i <= p; i++) {
    int ai, bi;
    cin >> ai >> bi;
    if (ai > bi) swap(ai, bi);

    if (ai == bi) s[ai].push_back(i);
    else o[ai].push_back(i);
  }

  vector<pii> t;
  vector<int> ans(v);
  for (int i = 0; i < v; i++) {
    int x;
    cin >> x;
    t.push_back({x, i});
  }
  sort(t.begin(), t.end());

  for (auto [k, i] : t) {
    if (s[k].size()) {
      ans[i] = s[k].back();
      s[k].pop_back();
    }
    else if (o[k - 1].size()) {
      ans[i] = o[k - 1].back();
      o[k - 1].pop_back();
    }
    else if (o[k].size()) {
      ans[i] = o[k].back();
      o[k].pop_back();
    }
    else {
      return cout << "impossible\n", void();
    }
  }

  for (int i = 0; i < v; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
