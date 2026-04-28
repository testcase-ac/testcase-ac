#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll N;
bool check(ll l) {
  ll acc = 0;
  for (int i = 0; i < 7; i++) acc += max(0LL, l - i);
  return acc >= N;
}

void solve() {
  cin >> N;

  ll left = 1, right = N + 1;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (check(mid)) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
