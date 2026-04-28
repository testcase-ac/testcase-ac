#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int N = 26;
int P[N], vis[N], C[N + 1];

void solve() {
  string S; cin >> S;
  for (int i = 0; i < N; ++i) P[i] = S[i] - 'A', vis[i] = 0;

  fill(C, C + N + 1, 0);
  for (int i = 0; i < N; ++i) {
    if (vis[i]) continue;
    int cnt = 0;
    for (int j = i; !vis[j]; j = P[j]) {
      vis[j] = 1;
      ++cnt;
    }
    C[cnt] ^= 1;
  }

  for (int i = 2; i <= 26; i += 2) if (C[i]) return cout << "No\n", void();
  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
