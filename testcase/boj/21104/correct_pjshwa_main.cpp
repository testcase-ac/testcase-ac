#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 998244353;

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void solve() {
  int n, m; cin >> n >> m;
  vector<pii> A;
  for (int i = 0; i < n; ++i) {
    int l, r; cin >> l >> r;
    A.emplace_back(l, r);
  }
  vector<int> B;
  for (int j = 0; j < m; ++j) {
    int x; cin >> x;
    B.push_back(x);
  }
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  priority_queue<int, vector<int>, greater<int>> pq_old, pq_new;
  int i = 0, ans = 0;
  for (int e : B) {
    while (i < n && A[i].first <= e) pq_new.push(A[i++].second);
    while (!pq_old.empty() && pq_old.top() < e) pq_old.pop();
    while (!pq_new.empty() && pq_new.top() < e) pq_new.pop();

    int oz = pq_old.size(), tz = pq_old.size() + pq_new.size();
    ll cur = lpow(2, tz, MOD);
    cur = (cur - lpow(2, oz, MOD) + MOD) % MOD;
    ans = (ans + cur) % MOD;

    while (!pq_new.empty()) pq_old.push(pq_new.top()), pq_new.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
