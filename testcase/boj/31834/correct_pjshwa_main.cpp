#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, S, E; cin >> N >> S >> E;
  if (S < E) {
    if (S == 1 && E == N) cout << "0\n";
    else if (S == 1 || E == S + 1) cout << "1\n";
    else cout << "2\n";
  }
  else {
    if (S == N && E == 1) cout << "0\n";
    else if (S == N || E == S - 1) cout << "1\n";
    else cout << "2\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
