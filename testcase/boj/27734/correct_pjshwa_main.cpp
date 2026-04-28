#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 26;
int D[MAX][MAX];

void solve() {
  int N; cin >> N;
  vector<string> W(N);
  for (int i = 0; i < N; i++) {
    cin >> W[i]; int z = W[i].size();
    D[W[i][0] - 'A'][W[i][z - 1] - 'A']++;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
