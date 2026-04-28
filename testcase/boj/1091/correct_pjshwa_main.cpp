#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 48;
int p[MAX], s[MAX], cs[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> p[i];
  for (int i = 0; i < n; i++) cin >> s[i];
  for (int i = 0; i < n; i++) cs[i] = i;

  int it = 6e5, cnt = 0;
  while (it--) {
    bool found = true;
    for (int i = 0; i < n; i++) {
      if (i % 3 != p[cs[i]]) found = false;
    }
    if (found) return cout << cnt << '\n', void();

    int ns[n];
    cnt++;
    for (int i = 0; i < n; i++) ns[s[i]] = cs[i];
    for (int i = 0; i < n; i++) cs[i] = ns[i];
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
