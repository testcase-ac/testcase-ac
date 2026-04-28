#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_gnumber(ll N) {
  string s = to_string(N);
  int dsum = 0;
  for (char c : s) dsum += c - '0';

  for (int i = 2; i * i <= dsum; i++) {
    if (dsum % i == 0) return false;
  }
  return true;
}

bool r(vector<ll> d) {
  ll N = 1;
  for (auto e : d) N *= e;
  if (is_gnumber(N)) return false;

  for (auto e : d) {
    vector<ll> nd;
    for (auto f : d) {
      if (e == f) continue;
      nd.push_back(f);
    }
    if (!r(nd)) return true;
  }
  return false;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll N;
  cin >> N;

  vector<ll> d;
  for (ll i = 2; i * i <= N; i++) {
    ll div = 1;
    while (N % i == 0) {
      N /= i;
      div *= i;
    }
    if (div > 1) d.push_back(div);
  }
  if (N > 1) d.push_back(N);

  if (r(d)) cout << "Laurence\n";
  else cout << "Seymour\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
