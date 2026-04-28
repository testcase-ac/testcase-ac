#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, MAXK = 1e3;
int S[MAX + 1];

// d[i] = max score if grouping ends at index i
int d[MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> S[i];

  for (int i = 1; i <= N; i++) {
    int run = S[i];
    for (int j = 1; j <= K; j++) {
      if (i - j < 0) break;
      d[i] = max(d[i], d[i - j] + run * j);
      run = max(run, S[i - j]);
    }
  }

  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
