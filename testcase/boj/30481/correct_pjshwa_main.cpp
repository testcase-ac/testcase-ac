#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXQ = 1e6;

bool f(ll n, ll k) {
  vector<int> ret;
  while (n) {
    ret.push_back(n % k);
    n /= k;
  }
  auto ret2 = ret;
  reverse(ret2.begin(), ret2.end());
  return ret == ret2;
}

void solve() {
  ll N; cin >> N;

  set<ll> ans;
  for (ll i = 2; i <= min(N, MAXQ); ++i) {
    if (f(N, i)) ans.insert(i);
  }

  // check whether s * b + s == N
  for (int s = 1; s <= MAXQ; ++s) {
    if (N % s) continue;
    ll b = N / s - 1;
    if (b > s) ans.insert(b);
  }

  if (ans.empty()) cout << "*\n";
  else for (ll x : ans) cout << x << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
