#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN + 1];
vector<int> B[MAXN + 1];

void solve() {
  int N, M, K, Q; cin >> N >> M >> K >> Q;
  for (int i = 1; i <= M; ++i) cin >> A[i];
  for (int i = 1; i <= K; ++i) {
    int x; cin >> x;
    B[x].push_back(i);
  }

  vector<int> ans(K + 2);
  for (int i = 1; i <= Q; ++i) {
    int x, y, k; cin >> x >> y >> k;

    int l = 0, r = K + 1;
    while (l < r) {
      int m = (l + r) / 2;
      int cnt_x = upper_bound(B[x].begin(), B[x].end(), m) - B[x].begin();
      int cnt_y = upper_bound(B[y].begin(), B[y].end(), m) - B[y].begin();

      if (cnt_x + cnt_y >= A[k]) r = m;
      else l = m + 1;
    }
    ++ans[l];
  }

  for (int i = 1; i <= K; ++i) {
    ans[i] += ans[i - 1];
    cout << ans[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
