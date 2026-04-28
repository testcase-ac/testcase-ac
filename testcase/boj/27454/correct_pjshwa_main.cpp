#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
ll A[MAXN + 1], P[MAXN + 1];

void solve() {
  int N, K, Y; cin >> N >> K >> Y; --K;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1);
  for (int i = 1; i <= N; ++i) P[i] = P[i - 1] + A[i];

  ll ans = 1e18;
  for (int i = 1; i <= N - K + 1; ++i) {
    int H = K / 2;
    if (K & 1) {
      ll med = A[i + H];
      ll pre = med * H - (P[i + H - 1] - P[i - 1]);
      ll post = P[i + K - 1] - P[i + H] - med * (K - H - 1);
      ans = min(ans, pre + post + abs(Y - med));
    }
    else {
      if (Y < A[i + H - 1]) {
        ll med = A[i + H - 1];
        ll pre = med * H - (P[i + H - 1] - P[i - 1]);
        ll post = P[i + K - 1] - P[i + H - 1] - med * (K - H);
        ans = min(ans, pre + post + abs(Y - med));
      }
      else if (Y > A[i + H]) {
        ll med = A[i + H];
        ll pre = med * H - (P[i + H - 1] - P[i - 1]);
        ll post = P[i + K - 1] - P[i + H] - med * (K - H - 1);
        ans = min(ans, pre + post + abs(Y - med));
      }
      else {
        ll med = Y;
        ll pre = med * H - (P[i + H - 1] - P[i - 1]);
        ll post = P[i + K - 1] - P[i + H - 1] - med * (K - H);
        ans = min(ans, pre + post);
      }
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
