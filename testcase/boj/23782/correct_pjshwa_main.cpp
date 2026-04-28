#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<ll> factors(ll N) {
  vector<ll> ret;
  for (ll i = 1; i * i <= N; i++) {
    if (N % i == 0) {
      ret.push_back(i);
      if (i * i != N) ret.push_back(N / i);
    }
  }
  sort(ret.begin(), ret.end());
  return ret;
}

void solve() {
  ll N;
  cin >> N;

  vector<ll> F = factors(N); ll S = 0;
  for (ll f : F) {
    if (S + 1 < f) return cout << "No\n", void();
    S += f;
  }
  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
