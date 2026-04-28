#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll P[MAXN + 1];

void solve() {
  int N; ll R; cin >> N >> R;
  for (int i = 1; i <= N; ++i) {
    cin >> P[i]; P[i] += P[i - 1];
  }

  vector<int> ans;
  for (int i = 1; i <= N; ++i) {
    int l = 0, r = N;
    while (l < r) {
      int m = (l + r) / 2;
      int cr = min(N, i + m), cl = max(0, i - m - 1);

      int oob_b = i + m > N && i - m - 1 < 0;
      if (oob_b || P[cr] - P[cl] > R) r = m;
      else l = m + 1;
    }
    ans.push_back(l - 1);
  }

  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
