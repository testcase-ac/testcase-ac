#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int> &a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

void solve() {
  int N; cin >> N;

  vector<int> ss, es, xs;
  for (int i = 0; i < N; i++) {
    int s, e; cin >> s >> e;
    ss.push_back(s); es.push_back(e);
    xs.push_back(s); xs.push_back(e);
  }
  sort(ss.begin(), ss.end());
  sort(es.begin(), es.end());
  compress(xs);

  auto S = [&](int x) {
    return upper_bound(ss.begin(), ss.end(), x) - lower_bound(ss.begin(), ss.end(), x);
  };
  auto E = [&](int x) {
    return upper_bound(es.begin(), es.end(), x) - lower_bound(es.begin(), es.end(), x);
  };

  int ans = 0, cur = 0;
  for (int x : xs) {
    cur += S(x) - E(x);
    ans = max(ans, cur);
  }

  cout << ans << '\n';
  cur = 0; int f = 0;
  for (int x : xs) {
    cur += S(x) - E(x);
    if (cur == ans) {
      if (!f) cout << x << ' ';
      f = 1;
    }
    else if (f) {
      cout << x << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
