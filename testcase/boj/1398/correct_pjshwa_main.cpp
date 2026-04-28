#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 1e4;
ll pw10[19];

ll r(ll N) {
  if (N < 10) return N;

  string s = to_string(N);
  if (s.size() % 2 == 0) {
    ll pw = pw10[s.size() - 2];
    ll n1 = pw * 25, n2 = pw * 10;

    ll res = 1e18;
    if (N >= n1) res = min(res, N / n1 + r(N % n1));
    if (N >= n2) res = min(res, N / n2 + r(N % n2));
    return res;
  }
  else {
    int e = s[0] - '0';
    return e + r(stoll(s.substr(1)));
  }
}

void solve() {
  ll N;
  cin >> N;
  cout << r(N) << '\n';
}

int main() {
  fast_io();

  pw10[0] = 1;
  for (int i = 1; i < 19; i++) pw10[i] = pw10[i - 1] * 10;

  int t = 1;
  cin >> t;
  while (t--) solve();
}
