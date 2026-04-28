#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int P[MAXN + 1];

void solve() {
  int N; string S; cin >> N >> S;
  for (int i = 1; i <= N; ++i) {
    P[i] = P[i - 1] + (S[i - 1] == '0');
  }

  int ans = 0, ansp = 0; vector<int> A{0};
  for (int i = 0; i < N; ++i) {
    if (S[i] == '0') continue;
    A.push_back(i + 1); ++ans;
  }

  int pmax = P[A.back()], Z = A.size();
  for (int p = 1; p <= pmax; ++p) {
    int cnt = 0, i = 0;
    while (1) {
      int l = i, r = Z;
      while (l < r) {
        int m = (l + r) / 2;
        if (P[A[m]] - P[A[i]] < p) l = m + 1;
        else r = m;
      }
      if (l == Z) break;
      ++cnt; i = l;
    }
    if (P[N] - P[A[i]] < p) --cnt;
    if (cnt == 0) break;

    int cur = (p + 1) * (cnt + 1) - 1;
    if (cur > ans) ans = cur, ansp = p;
  }

  cout << ans << '\n'; int acc = 0;
  for (int i = 0; i < ans; ++i) {
    if (acc == ansp) cout << '1', acc = 0;
    else cout << '0', ++acc;
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
