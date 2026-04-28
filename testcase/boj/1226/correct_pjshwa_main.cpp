#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300, MAXV = 1e5, INF = 0x3f3f3f3f;
int A[MAX + 1], d[MAX + 1][MAXV + 1];

void solve() {
  int N;
  cin >> N;

  vector<int> A(N + 1); int sum = 0;
  for (int i = 1; i <= N; i++) cin >> A[i], sum += A[i];

  d[0][0] = INF;
  for (int i = 1; i <= N; i++) {
    for (int v = 0; v <= sum; v++) {
      d[i][v] = d[i - 1][v];
      if (v >= A[i]) d[i][v] = max(d[i][v], min(d[i - 1][v - A[i]], A[i]));
    }
  }

  int v;
  for (v = sum; v >= sum / 2 + 1; v--) {
    if (!d[N][v]) continue;
    if (v - d[N][v] >= sum / 2 + 1) continue;

    break;
  }

  // backtrace
  vector<int> ans;
  for (int i = N; i >= 1; i--) {
    if (v >= A[i] && d[i][v] == min(d[i - 1][v - A[i]], A[i])) {
      ans.push_back(i);
      v -= A[i];
    }
  }
  assert(v == 0);

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
