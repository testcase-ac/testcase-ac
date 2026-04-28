#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;
int a[101], d[101][100001];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];

  for (int i = 0; i <= n; i++) for (int w = 0; w <= 1e5; w++) d[i][w] = INF;

  d[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int w = 0; w <= 1e5; w++) {
      if (w >= a[i]) d[i][w] = min(d[i - 1][w], d[i - 1][w - a[i]] + 1);
      else d[i][w] = d[i - 1][w];
    }
  }

  int ans = d[n][k];
  cout << (ans == INF ? -1 : ans);

}
