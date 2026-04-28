#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 70, INF = 1e9 + 7;
int a[MAX], d[MAX][2];
int L;

int r(int i, int carry) {
  if (i == L) return carry == 0 ? 0 : -INF;
  if (d[i][carry] != -1) return d[i][carry];

  int res = -INF;
  if (carry == a[i]) {
    res = max(res, r(i + 1, 0));
    res = max(res, r(i + 1, 1) + 2);
  }
  else res = max(res, r(i + 1, carry) + 1);

  return d[i][carry] = res;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll N;
  cin >> N;
  for (int i = 0; i < MAX; i++) {
    if (N == 0) {
      L = i;
      break;
    }
    a[i] = N % 2;
    N /= 2;
  }

  memset(d, -1, sizeof(d));
  cout << r(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
