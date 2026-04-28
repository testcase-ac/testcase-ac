#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int oc[61];

map<int, ll> bcount_2k(int k) {
  ll c = 1;
  map<int, ll> ans;
  for (int i = 0; i <= k; i++) {
    ans[i] = c;
    c *= (k - i);
    c /= (i + 1);
  }
  return ans;
}

ll count_upto(ll n, int x) {
  if (x == 0) return 1;

  map<int, ll> tc;
  tc[__builtin_popcountll(n)]++;

  stack<int> s;
  while (n) {
    s.push(n & 1);
    n >>= 1;
  }

  int ccnt = 0;
  while (!s.empty()) {
    if (s.top()) {
      auto ret = bcount_2k(s.size() - 1);
      for (auto [c, v] : ret) tc[c + ccnt] += v;
      ccnt++;
    }
    s.pop();
  }

  ll ans = 0;
  for (auto [c, v] : tc) {
    if (oc[c] == x - 1) ans += v;
  }
  if (x == 1) ans--;
  return ans;
}

void solve(ll lo, ll hi, int x) {
  ll ans = count_upto(hi, x);
  if (lo > 1) ans -= count_upto(lo - 1, x);
  cout << ans << '\n';
}

int main() {
  fast_io();

  oc[0] = -100;
  for (int i = 1; i <= 60; i++) {
    int k = i, cnt = 0;
    while (k != 1) {
      k = __builtin_popcount(k);
      cnt++;
    }
    oc[i] = cnt;
  }

  ll a, b, c;
  while (1) {
    cin >> a >> b >> c;
    if (a == 0 && b == 0 && c == 0) break;
    solve(a, b, c);
  }
}
