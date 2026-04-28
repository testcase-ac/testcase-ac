#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int a[MAX], b[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> b[i];
  sort(a, a + n); reverse(a, a + n);
  sort(b, b + m);

  queue<int> aq, bq;
  for (int i = 0; i < n; i++) aq.push(a[i]);
  for (int i = 0; i < m; i++) bq.push(b[i]);

  ll ans = 0;
  while (aq.size() && bq.size()) {
    int ai = aq.front(), bi = bq.front();
    if (ai >= bi) {
      // cout << "ai: " << ai << " bi: " << bi << endl;
      ans += (ai - bi);
      aq.pop(); bq.pop();
    }
    else break;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
