#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  vector<int> G, L;
  for (int i = 0; i < n; i++) {
    string s; int x;
    cin >> s >> x;
    if (s == "G") G.push_back(x);
    else L.push_back(x);
  }
  sort(G.begin(), G.end());
  sort(L.begin(), L.end());
  reverse(G.begin(), G.end());

  int ans = n;
  for (int i = 0; i < G.size(); i++) {
    int e = G[i];
    int w = lower_bound(L.begin(), L.end(), e) - L.begin();

    ans = min(ans, w + i);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
