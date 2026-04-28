#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
bool O[MAX + 2];
int ans1[MAX + 1][MAX + 1], ans2[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll N, K;
  cin >> N >> K;
  cout << ans1[N][K] << ' ' << ans2[N][K] << '\n';
}

int main() {
  fast_io();

  for (int N = 1; N <= 1000; N++) {
    memset(O, 0, sizeof(O));
    O[0] = O[N + 1] = true;

    for (int i = 1; i <= N; i++) {
      int cm = 0, cx = 0, ci = INF;
      for (int p = 1; p <= N; p++) {
        if (O[p]) continue;

        int ls = 0, rs = 0;
        while (!O[p - ls - 1]) ls++;
        while (!O[p + rs + 1]) rs++;

        int m = min(ls, rs), x = max(ls, rs);
        if (m > cm) {
          cm = m;
          cx = x;
          ci = p;
        }
        else if (m == cm && x > cx) {
          cx = x;
          ci = p;
        }
        else if (m == cm && x == cx && p < ci) {
          ci = p;
        }
      }

      O[ci] = true;
      ans1[N][i] = cx, ans2[N][i] = cm;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
