#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, C, p;
  cin >> A >> B >> C >> p;

  int cnt = 0;
  if (A % p == 0) cnt++;
  if (B % p == 0) cnt++;
  if (C % p == 0) cnt++;

  if (cnt >= 2) cout << "1\n";
  else cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
