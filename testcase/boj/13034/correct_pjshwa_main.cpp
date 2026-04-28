#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int G[MAX + 1];

void solve() {
  int N;
  cin >> N;

  if (G[N - 1] == 0) cout << "2\n";
  else cout << "1\n";
}
 
int main() {
  fast_io();

  G[0] = 0;
  G[1] = G[2] = 1;
  for (int i = 3; i <= MAX; i++) {
    set<int> u;
    u.insert(G[i - 2]);

    for (int j = 0;; j++) {
      if (j > i - 3 - j) break;
      u.insert(G[j] ^ G[i - 3 - j]);
    }

    int mex = 0;
    while (u.count(mex)) mex++;

    G[i] = mex;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
