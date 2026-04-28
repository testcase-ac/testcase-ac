#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX], G[500];

void solve() {
}

int main() {
  fast_io();

  G[0] = 0, G[1] = 1, G[2] = 2;
  for (int v = 3; v <= 50; v++) {
    set<int> gs;
    for (int x = 0; x < v; x++) gs.insert(G[x]);
    for (int x = 1; x <= v; x++) for (int y = 1; y <= v; y++) {
      int z = v - (x + y);
      if (z < 1) continue;

      gs.insert(G[x] ^ G[y] ^ G[z]);
    }

    int mex = 0;
    while (gs.count(mex)) mex++;

    G[v] = mex;

    cout << "v = " << v << ", mex = " << mex << endl;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
