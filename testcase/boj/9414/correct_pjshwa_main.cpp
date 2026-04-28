#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int LIM = 5e6;

void solve() {
  vector<int> L;
  while (1) {
    int x; cin >> x;
    if (x == 0) break;
    L.push_back(x);
  }

  int N = L.size();
  sort(L.begin(), L.end(), greater<int>());

  ll ans = 0;
  for (int i = 0; i < N; i++) {
    ll x = L[i], cur = 2;
    for (int j = 0; j <= i; j++) {
      cur *= x;
      if (cur > LIM) break;
    }
    ans += cur;
    if (ans > LIM) break;
  }

  if (ans > LIM) cout << "Too expensive\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
