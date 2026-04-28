#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1.5e5;
ll A[MAXN + 1], B[MAXN + 1], P[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i], B[i] = A[i];
  sort(B + 1, B + N + 1);

  ll sum = 0;
  for (int i = 1; i <= N; ++i) {
    sum += i * B[i];
    P[i] = P[i - 1] + B[i];
  }

  int Q; cin >> Q;
  while (Q--) {
    ll ai, nw; cin >> ai >> nw;

    int i = lower_bound(B + 1, B + N + 1, A[ai]) - B;
    ll pw = B[i];

    // calculate ni
    int lo = 1, hi = N + 1;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (B[mid] < nw) lo = mid + 1;
      else hi = mid;
    }
    int ni = lo;
    if (pw < nw) --ni;

    ll cur = sum - i * pw + ni * nw, add;
    if (i > ni) add = P[i - 1] - P[ni - 1];
    else add = P[i] - P[ni];
    cout << cur + add << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
