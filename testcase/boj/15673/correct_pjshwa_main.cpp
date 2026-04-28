#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int A[MAX], dl[2][MAX], dr[2][MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  int max_so_far = A[0], max_ending_here = max(0, A[0]);
  int min_so_far = A[0], min_ending_here = min(0, A[0]);
  dl[0][0] = dl[1][0] = A[0];
  for (int i = 1; i < N; i++) {
    max_ending_here = max_ending_here + A[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;

    min_ending_here = min_ending_here + A[i];
    if (min_so_far > min_ending_here) min_so_far = min_ending_here;
    if (min_ending_here > 0) min_ending_here = 0;

    dl[0][i] = max_so_far;
    dl[1][i] = min_so_far;
  }

  max_so_far = A[N - 1], max_ending_here = max(0, A[N - 1]);
  min_so_far = A[N - 1], min_ending_here = min(0, A[N - 1]);
  dr[0][N - 1] = dr[1][N - 1] = A[N - 1];
  for (int i = N - 2; i >= 0; i--) {
    max_ending_here = max_ending_here + A[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;

    min_ending_here = min_ending_here + A[i];
    if (min_so_far > min_ending_here) min_so_far = min_ending_here;
    if (min_ending_here > 0) min_ending_here = 0;

    dr[0][i] = max_so_far;
    dr[1][i] = min_so_far;
  }

  ll ans = -1e18;
  for (int i = 0; i < N - 1; i++) {
    ans = max(ans, (ll)dl[0][i] * dr[0][i + 1]);
    ans = max(ans, (ll)dl[0][i] * dr[1][i + 1]);
    ans = max(ans, (ll)dl[1][i] * dr[0][i + 1]);
    ans = max(ans, (ll)dl[1][i] * dr[1][i + 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
