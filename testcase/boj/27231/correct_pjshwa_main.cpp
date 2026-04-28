#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int LIM = 1e9;

void solve() {
  string s; cin >> s;
  int n = s.size(), zc = 0, oc = 0;
  for (char c : s) {
    if (c == '0') zc++;
    if (c == '1') oc++;
  }
  if (zc + oc == n) return cout << "Hello, BOJ 2023!\n", void();

  set<int> p;
  for (int m = 1;; m++) {
    ll cur = 0;
    for (int i = 0; i < n; i++) {
      ll c = 1;
      for (int j = 0; j < m; j++) c *= s[i] - '0';
      cur += c;
    }

    if (cur > LIM) break;
    p.insert(cur);
  }

  set<int> q;
  for (int u = 0; u < (1 << (n - 1)); u++) {
    int c = s[0] - '0', acc = 0;
    for (int i = 0; i < n - 1; i++) {
      if (u & (1 << i)) {
        acc += c;
        c = s[i + 1] - '0';
      }
      else {
        c = c * 10 + s[i + 1] - '0';
      }
    }
    acc += c;
    q.insert(acc);
  }

  int ans = 0;
  for (int e : q) {
    if (p.count(e)) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
