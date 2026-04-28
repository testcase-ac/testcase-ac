#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10, INF = 1e9 + 7;
int cost[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) cost[i][j] = INF;
    }
  }

  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    cost[a][b] = w;
  }

  int left = 1, right = 5'000'001;
  while (left < right) {
    int mid = (left + right) / 2;

    int p[n + 1];
    for (int i = 1; i <= n; i++) p[i] = i;

    bool fable = false;

    do {
      bool able = true;
      for (int i = 1; i < n; i++) {
        if (cost[p[i]][p[i + 1]] > mid) {
          able = false;
          break;
        }
      }
      able &= (cost[p[n]][p[1]] <= mid);
      if (able) {
        fable = true;
        break;
      }
    } while (next_permutation(p + 1, p + n + 1));

    if (fable) right = mid;
    else left = mid + 1;
  }

  if (left == 5'000'001) cout << "-1\n";
  else {
    cout << left << '\n';
    int p[n + 1];
    for (int i = 1; i <= n; i++) p[i] = i;

    do {
      bool able = true;
      for (int i = 1; i < n; i++) {
        if (cost[p[i]][p[i + 1]] > left) {
          able = false;
          break;
        }
      }
      able &= (cost[p[n]][p[1]] <= left);
      if (able) {
        for (int i = 1; i <= n; i++) cout << p[i] << ' ';
        cout << '\n';
        break;
      }
    } while (next_permutation(p + 1, p + n + 1));
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
