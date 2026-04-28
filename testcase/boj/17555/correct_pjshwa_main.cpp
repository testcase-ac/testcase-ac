#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int S[MAXN], E[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> S[i] >> E[i];

  // start BSing at 4 corner points
  int ans = 0;
  for (int i = 0; i < N; ++i) {

    // Upper left
    {
      int l = 1, r = E[i] - S[i] + 2;
      while (l < r) {
        int m = (l + r) / 2;

        int len = m - 1, ok = 0;
        if (i + len < N) {
          ok = S[i + len] <= S[i];
          ok &= E[i + len] >= S[i] + len;
        }

        if (ok) l = m + 1;
        else r = m;
      }
      ans = max(ans, l - 1);
    }

    // Upper right
    {
      int l = 1, r = E[i] - S[i] + 2;
      while (l < r) {
        int m = (l + r) / 2;

        int len = m - 1, ok = 0;
        if (i + len < N) {
          ok = E[i + len] >= E[i];
          ok &= S[i + len] <= E[i] - len;
        }

        if (ok) l = m + 1;
        else r = m;
      }
      ans = max(ans, l - 1);
    }
  }

  for (int i = N - 1; i >= 0; --i) {

    // Lower left
    {
      int l = 1, r = E[i] - S[i] + 2;
      while (l < r) {
        int m = (l + r) / 2;

        int len = m - 1, ok = 0;
        if (i - len >= 0) {
          ok = S[i - len] <= S[i];
          ok &= E[i - len] >= S[i] + len;
        }

        if (ok) l = m + 1;
        else r = m;
      }
      ans = max(ans, l - 1);
    }

    // Lower right
    {
      int l = 1, r = E[i] - S[i] + 2;
      while (l < r) {
        int m = (l + r) / 2;

        int len = m - 1, ok = 0;
        if (i - len >= 0) {
          ok = E[i - len] >= E[i];
          ok &= S[i - len] <= E[i] - len;
        }

        if (ok) l = m + 1;
        else r = m;
      }
      ans = max(ans, l - 1);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
