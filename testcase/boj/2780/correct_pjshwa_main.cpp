#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000, MOD = 1234567;
int d[MAX + 1][10];

bool p(int a, int b) {
  if (a > b) swap(a, b);

  if (a == 0) return b == 7;
  if (a == 1) return b == 2 || b == 4;
  if (a == 2) return b == 3 || b == 5;
  if (a == 3) return b == 6;
  if (a == 4) return b == 5 || b == 7;
  if (a == 5) return b == 6 || b == 8;
  if (a == 6) return b == 9;
  if (a == 7) return b == 8;
  if (a == 8) return b == 9;
  return false;
}

void solve() {
  int N;
  cin >> N;

  int ans = 0;
  for (int j = 0; j < 10; j++) ans = (ans + d[N][j]) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int j = 0; j < 10; j++) d[1][j] = 1;
  for (int i = 2; i <= MAX; i++) for (int pj = 0; pj < 10; pj++) for (int j = 0; j < 10; j++) {
    if (p(pj, j)) d[i][j] = (d[i][j] + d[i - 1][pj]) % MOD;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
