#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
ll A[MAX + 1], P[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= N; i++) P[i] += P[i - 1] + A[i];

  ll s1 = 0, ans = 0;
  for (int x = 1; x <= N - 2; x++) {
    s1 += A[x];

    int y1, y2;

    // Max y s.t. A < B
    {
      int l = x + 1, r = N + 1;
      while (l < r) {
        int m = (l + r) / 2;
        if (s1 < P[N] - P[m - 1]) l = m + 1;
        else r = m;
      }
      y1 = l - 1;
    }

    // Min y s.t. B < C
    {
      int l = x + 1, r = N + 1;
      while (l < r) {
        int m = (l + r) / 2;
        if (P[m] - P[x] <= P[N] - P[m]) l = m + 1;
        else r = m;
      }
      y2 = l;
    }

    ans += max(0, y1 - y2);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
