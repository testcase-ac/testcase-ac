#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 1e6;

void solve() {
  int N, M; string S, T;
  cin >> N >> S >> M >> T;

  int ans = 0, i = N - 1;
  for (int j = 0; j < M; j++) {
    i = (i + 1) % N;
    ans++;

    while (ans < INF && S[i] != T[j]) {
      i = (i + 1) % N;
      ans++;
    }
  }

  if (ans >= INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
