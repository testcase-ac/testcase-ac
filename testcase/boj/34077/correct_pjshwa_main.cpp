#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int i = 1;
  for (; i < 2 * N + 1; i += 2) {
    if (S[i] == '-') break;
  }
  i += 3;
  for (; i < 2 * N + 1; i += 2) {
    if (S[i] != '0') return cout << "NO\n", void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
