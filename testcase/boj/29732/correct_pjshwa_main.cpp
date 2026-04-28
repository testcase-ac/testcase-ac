#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K; string S; cin >> N >> M >> K >> S;

  int dt[N + 1]{};
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'R') {
      int l = max(0, i - K), r = min(N, i + K + 1);
      ++dt[l]; --dt[r];
    }
  }

  int run = 0, cnt = 0;
  for (int i = 0; i < N; ++i) {
    run += dt[i];
    cnt += run > 0;
  }

  if (cnt <= M) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
