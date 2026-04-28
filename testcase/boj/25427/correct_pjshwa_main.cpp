#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll p[4];

void solve() {
  int N; string S;
  cin >> N >> S;

  for (int i = 0; i < N; i++) {
    if (S[i] == 'D') p[0]++;
    if (S[i] == 'K') p[1] += p[0];
    if (S[i] == 'S') p[2] += p[1];
    if (S[i] == 'H') p[3] += p[2];
  }

  cout << p[3] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
