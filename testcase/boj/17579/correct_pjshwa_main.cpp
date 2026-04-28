#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
ll w[MAX], s[MAX];
unordered_set<ll> ps;
ll csum;
int n, m;

void dfs(int i) {
  if (i == m) {
    ps.insert(abs(csum));
    return;
  }
  csum += s[i];
  dfs(i + 1);
  csum -= s[i];
  csum -= s[i];
  dfs(i + 1);
  csum += s[i];
  dfs(i + 1);
}

void solve() {
  for (int i = 0; i < n; i++) cin >> w[i];
  for (int i = 0; i < m; i++) cin >> s[i];

  ps.clear();
  csum = 0;
  dfs(0);

  bool first = true;
  unordered_set<ll> sdiff;
  for (int i = 0; i < n; i++) {
    if (ps.count(w[i])) continue;

    if (first) {
      for (ll e : ps) {
        sdiff.insert(abs(w[i] - e));
        sdiff.insert(abs(w[i] + e));
      }
      first = false;
    }
    else {
      unordered_set<ll> ndiff;
      for (ll e : ps) {
        if (sdiff.count(abs(w[i] - e))) ndiff.insert(abs(w[i] - e));
        if (sdiff.count(abs(w[i] + e))) ndiff.insert(abs(w[i] + e));
      }
      sdiff = ndiff;
    }
  }

  if (first) cout << "0\n";
  else if (sdiff.empty()) cout << "-1\n";
  else cout << *min_element(sdiff.begin(), sdiff.end()) << "\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
