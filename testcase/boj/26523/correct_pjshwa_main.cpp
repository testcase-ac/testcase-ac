#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N = 5000;
  int C[10]{};
  for (int i = 0; i < N; i++) {
    double x;
    cin >> x;
    C[(int)(x * 10)]++;
  }

  if (400 <= C[0] && 400 <= C[9]) cout << "A\n";
  else cout << "B\n";
}

int main() {
  fast_io();

  int t = 100;
  // cin >> t;
  while (t--) solve();
}
