#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; string T;
  cin >> N >> K >> T;

  for (int i = 1; i <= K - 1; i++) cout << T[i - 1];
  for (int i = K; i <= N; i++) {
    if ('A' <= T[i - 1] && T[i - 1] <= 'Z') cout << (char)(T[i - 1] + 'a' - 'A');
    else cout << (char)(T[i - 1] + 'A' - 'a');
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
