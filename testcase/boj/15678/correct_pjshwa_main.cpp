#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
int a[MAX + 1];
ll dp[MAX + 1];

int main() {
  fast_io();

  int n, d;
  cin >> n >> d;
  for (int i = 0; i < n; i++) cin >> a[i];

  ll ans = -INF;
  priority_queue<pair<ll, int>> pq;

  for (int i = 0; i < n; i++) {
    while (!pq.empty() && pq.top().second < i - d) pq.pop();
    ll pqmax = pq.empty() ? 0 : max(0LL, pq.top().first);
    dp[i] = pqmax + a[i];
    ans = max(ans, dp[i]);
    pq.push({dp[i], i});
  }

  cout << ans << '\n';
}
