#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int> &v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

void solve() {
  int N; cin >> N;
  vector<int> pos, neg, all;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    pos.push_back(x - y); neg.push_back(x + y);
    all.push_back(x - y); all.push_back(x + y);
  }
  compress(pos); compress(neg); compress(all);

  ll ans = all.size();
  for (int& x : pos) {
    int cnt = neg.end() - upper_bound(neg.begin(), neg.end(), x);
    ans += cnt;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
