#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int val[MAX + 1], wgt[MAX + 1], d[MAX + 1][1000001];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> wgt[i] >> val[i];

  for (int i = 1; i <= n; i++) {
    for (int l = 1; l <= 1e6; l++) {
      if (wgt[i - 1] <= l) d[i][l] = max(val[i - 1] + d[i - 1][l - wgt[i - 1]], d[i - 1][l]);
      else d[i][l] = d[i - 1][l];
    }
  }

  ll max_val = -1, max_wgt = 1;
  int max_idx = -1;
  for (int i = 1; i <= m; i++) {
    int w;
    cin >> w;
    if (max_wgt * d[n][w] > max_val * w) {
      max_val = d[n][w];
      max_wgt = w;
      max_idx = i;
    }
  }

  cout << max_idx << '\n';
}
