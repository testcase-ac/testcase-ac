#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, X; cin >> N >> X;
  if (N <= 2) return cout << "-1\n", void();

  vector<int> F, B;
  for (int i = 1; i <= N - 2; i++) {
    int h = N - i - 1;
    if (X >= h) X -= h, F.push_back(i);
    else B.push_back(i);
  }
  sort(B.begin(), B.end(), greater<int>());

  if (X) return cout << "-1\n", void();

  cout << N << ' ';
  for (int e : F) cout << e << ' ';
  cout << N - 1 << ' ';
  for (int e : B) cout << e << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
