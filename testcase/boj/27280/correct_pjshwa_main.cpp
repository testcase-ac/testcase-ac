#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1000, INF = 1e18;
ll d[MAX + 1][11], S[MAX + 1][MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> A; vector<int> hs;
  for (int i = 0; i < N; i++) {
    int hi, si; cin >> hi >> si;
    A.emplace_back(hi, si);
    hs.push_back(hi);
  }
  sort(hs.begin(), hs.end());

  for (int i = 0; i < N; i++) {
    auto [hi, si] = A[i];
    int idx = lower_bound(hs.begin(), hs.end(), hi) - hs.begin();
    A[i] = {idx, si};
  }

  for (int i = 1; i <= N; i++) {
    ll l = -1, s = 0;
    for (int j = i; j <= N; j++) {
      if (A[j - 1].first > l) {
        tie(l, s) = A[j - 1];
      }
      else if (A[j - 1].first == l) {
        s += A[j - 1].second;
      }
      S[i][j] = s;
    }
  }

  for (int i = 0; i <= N; i++) fill(d[i], d[i] + M + 1, -INF);
  d[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int m = 1; m <= M; m++) {
      for (int j = i - 1; j >= 0; j--) {
        d[i][m] = max(d[i][m], d[j][m - 1] + S[j + 1][i]);
      }
    }
  }
  cout << d[N][M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
