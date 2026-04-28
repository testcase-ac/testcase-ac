#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    A[i] = A[i] == 1 ? 1 : -1;
  }

  int ans = 0;
  int max_so_far = -INF, max_ending_here = 0;
  for (int i = 0; i < N; i++) {
    max_ending_here = max_ending_here + A[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }
  ans = max(ans, max_so_far);

  max_so_far = -INF, max_ending_here = 0;
  for (int i = 0; i < N; i++) {
    max_ending_here = max_ending_here - A[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }
  ans = max(ans, max_so_far);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
