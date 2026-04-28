#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
bool t[MAX];

void solve() {
  int n, k;
  cin >> n >> k;

  int e = 900;
  for (int i = 1; i <= 1000; i++) {
    t[e] = t[e + 180] = t[e + 360] = true;
    e += (1440 + k);
  }

  vector<int> ans;
  for (int i = n * 1440; i < (n + 1) * 1440; i++) {
    if (t[i]) ans.push_back(i % 1440);
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << setfill('0') << setw(2) << e / 60 << ':' << setw(2) << e % 60 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
