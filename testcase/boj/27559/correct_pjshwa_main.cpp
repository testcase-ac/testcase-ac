#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1500;
int B[MAX][MAX], C[MAX], R[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    for (int j = 0; j < N; ++j) B[i][j] = S[j] == 'R';
    cin >> C[i];
  }
  for (int i = 0; i < N; ++i) cin >> R[i];

  int Q; cin >> Q;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
