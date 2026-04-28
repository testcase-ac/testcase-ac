#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 16;
int A[MAX];
double d[1 << MAX][10];
int i, N;

double r(int state, int p) {
  if (d[state][p] != -1) return d[state][p];
  if (state == 0) return d[state][p] = p == 0;
  
  int c = __builtin_popcount(state);
  double res = 0;
  for (int j = 0; j < N; j++) {
    if (!(state & (1 << j))) continue;
    res += r(state ^ (1 << j), (10 * p + A[j]) % A[i]) / c;
  }
  return d[state][p] = res;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  
  int mask = (1 << N) - 1;
  double ans = 0;
  for (i = 0; i < N; i++) {
    for (int i = 0; i < (1 << N); i++) for (int j = 0; j < 10; j++) d[i][j] = -1;
    ans += r(mask ^ (1 << i), A[i]) / N;
  }
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
