#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  if (N == 1) return cout << "1\n", void();

  int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
  while (N % 2 == 0) N /= 2, c2++;
  while (N % 3 == 0) N /= 3, c3++;
  while (N % 5 == 0) N /= 5, c5++;
  while (N % 7 == 0) N /= 7, c7++;

  if (N > 1) return cout << "-1\n", void();
  
  int ans = c5 + c7;
  ans += c3 / 2; c3 %= 2;
  ans += c2 / 3; c2 %= 3;

  if (c2 == 0) ans += c3;
  if (c2 == 1) ans += 1;
  if (c2 == 2) {
    if (c3 == 1) ans += 2;
    else ans += 1;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
