#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 400, INF = 0x3f3f3f3f;
int A[MAX + 1], U[MAX + 1][MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 1; i <= N; i++) {
    int maxx = -INF, minx = INF;
    for (int j = i; j <= N; j++) {
      maxx = max(maxx, A[j]);
      minx = min(minx, A[j]);
      U[i][j] = maxx - minx;
    }
  }

  vector<pii> D;
  D.push_back({1, N});
  for (int i = 0; i < K - 1; i++) {
    int mi, mx = -INF;
    for (auto& [s, e] : D) {
      for (int j = s; j < e; j++) {
        int cx = U[s][e] - U[s][j] - U[j + 1][e];
        if (cx > mx) mx = cx, mi = j;
      }
    }

    vector<pii> E;
    for (auto& [s, e] : D) {
      if (s <= mi && mi < e) {
        E.push_back({s, mi});
        E.push_back({mi + 1, e});
      }
      else E.push_back({s, e});
    }
    D = E;
  }

  int ans = 0;
  for (auto& [s, e] : D) ans += U[s][e];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
