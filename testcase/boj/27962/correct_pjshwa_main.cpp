#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  for (int l = 1; l <= N; l++) {
    int s1 = 0, s2 = N - l, dif = 0;
    for (int i = 0; i < l; i++) {
      if (S[s1 + i] != S[s2 + i]) dif++;
    }
    if (dif == 1) return cout << "YES\n", []{}();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
