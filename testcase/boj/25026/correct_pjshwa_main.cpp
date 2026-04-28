#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
ll pw2[MAX + 1];

void solve() {
  int n;
  cin >> n;

  vector<pii> a;
  for (int i = 0; i < n; i++) {
    int si, ei;
    cin >> si >> ei;
    if (si >= ei) continue;
    a.emplace_back(si, ei);
  }
  sort(all(a));
  n = a.size();

  vector<pii> m;
  for (int i = 0; i < n; i++) {
    auto [si, ei] = a[i];
    m.push_back({si, 1});
    m.push_back({ei, -1});
  }
  sort(all(m));

  ll dt = 0, tlen = 0, msz = m.size();
  for (int i = 0; i < msz - 1; i++) {
    auto [v1, d1] = m[i];
    auto [v2, d2] = m[i + 1];
    dt += d1;

    ll ways = (pw2[dt] + MOD - 1) % MOD;
    tlen = (tlen + (v2 - v1) * ways) % MOD;
  }

  ll tcnt = 0, pre = 0;
  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 0; i < n; i++) {
    if (!pq.empty() && pq.top() <= a[i].first) {
      tcnt = (tcnt + pw2[pq.size()] + MOD - pw2[pre]) % MOD;
      pre = pq.size();

      while (!pq.empty() && pq.top() <= a[i].first) {
        pre--;
        pq.pop();
      }
    }
    pq.push(a[i].second);
  }
  tcnt = (tcnt + pw2[pq.size()] + MOD - pw2[pre]) % MOD;

  cout << tlen << ' ' << tcnt << '\n';
}

int main() {
  fast_io();

  pw2[0] = 1;
  for (int i = 1; i <= MAX; i++) pw2[i] = (pw2[i - 1] * 2) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
