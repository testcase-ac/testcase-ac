#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50, INF = 0x3f3f3f3f;
int d[MAX + 1];

void solve() {
  string S; int M; cin >> S >> M;
  int N = S.size();

  map<string, vector<string>> P;
  for (int i = 0; i < M; i++) {
    string T; cin >> T;
    string U = T; sort(U.begin(), U.end());
    P[U].push_back(T);
  }

  fill(d, d + MAX + 1, INF); d[0] = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < i; j++) {
      string T = S.substr(j, i - j);
      string U = T; sort(U.begin(), U.end());

      for (auto& V : P[U]) {
        int z = V.size(), cost = 0;
        for (int k = 0; k < z; k++) cost += (T[k] != V[k]);
        d[i] = min(d[i], d[j] + cost);
      }
    }
  }

  if (d[N] == INF) cout << "-1\n";
  else cout << d[N] << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
