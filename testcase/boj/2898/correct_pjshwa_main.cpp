#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, MAXL = 1000;
int upper[MAX][MAXL], lower[MAX][MAXL];

void solve() {
  int W, L, N;
  cin >> W >> L >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < L; j++) cin >> upper[i][j];
    for (int j = 0; j < L; j++) cin >> lower[i][j];
  }
  
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}