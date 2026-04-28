#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int d[MAX + 1];

int tc;
void solve() {
  cout << "Data Set " << ++tc << ":\n";

  int M; string S; cin >> M >> S;
  int N = S.size();

  vector<string> O(M);
  for (int i = 0; i < M; ++i) cin >> O[i];

  fill(d, d + N + 1, INF); d[0] = 0;
  for (int i = 1; i <= N; i++) {
    for (string C : O) {
      int cz = C.size();
      if (cz > i) continue;

      bool ident = 1;
      for (int j = 1; j <= cz; ++j) {
        if (S[i - j] != C[cz - j]) {
          ident = 0;
          break;
        }
      }
      if (ident) d[i] = min(d[i], d[i - cz] + 1);
    }
  }

  if (d[N] == INF) cout << "Impossible\n";
  else cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
