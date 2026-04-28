#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
int a[3];

void dijk(int s) {
  fill(cdist, cdist + MAX + 1, INF);
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (int di : {a[0], a[1]}) {
      int cost = 0, next = ui + di;
      if (ui + di >= a[2]) {
        cost++;
        next -= a[2];
      }
      if (cdist[next] > wi + cost) {
        cdist[next] = wi + cost;
        pq.push({wi + cost, next});
      }
    }
  }
}

void solve() {
  ll n;
  cin >> n >> a[0] >> a[1] >> a[2];
  sort(a, a + 3);

  n--;
  dijk(0);

  ll ans = 0;
  for (int rem = 0; rem < a[2]; rem++) {
    ll tot = n / a[2] + (rem <= n % a[2]);
    ans += max(0LL, tot - cdist[rem]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
