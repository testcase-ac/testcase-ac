#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int lp[MAX + 1];

void solve() {
  ll s, e, k;
  cin >> s >> e >> k;

  for (int i = 2; i <= MAX; i++) {
    ll r = s % i;
    for (int j = r == 0 ? 0 : i - r; j <= e - s; j += i) {
      if (lp[j] == 0) lp[j] = i;
    }
  }

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i <= e - s; i++) {
    if (lp[i] > 0) pq.push(lp[i]);
  }

  ll ans = 0;
  while (k--) {
    ans += pq.top();
    pq.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}