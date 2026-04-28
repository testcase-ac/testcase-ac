#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<ll> C;

void solve() {
  ll N, cnt = 0; cin >> N;
  for (auto& v : C) {
    if (N >= v) {
      cnt += N / v;
      N %= v;
    }
  }
  if (N == 0 && cnt <= 8) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();

  ll u = 0;
  for (int i = 0; i < 18; ++i) {
    u = 10 * u + 8;
    C.push_back(u);
  }
  reverse(C.begin(), C.end());

  int t = 1;
  cin >> t;
  while (t--) solve();
}
