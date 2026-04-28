#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int d[1 << 17];
int w[17][17];
const int MAX = 1e9;
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cin >> w[i][j];
  }

  for (int i = 0; i < (1 << n); i++) d[i] = MAX;

  string s;
  cin >> s;

  int p;
  cin >> p;

  int ycnt = 0;
  for (int j = 0; j < n; j++) {
    if (s[j] == 'Y') ycnt++;
  }

  if (ycnt >= p) {
    cout << "0\n";
    return 0;
  }
  if (!ycnt) {
    cout << "-1\n";
    return 0;
  }

  d[0] = 0;
  for (int i = 0; i < (1 << n); i++)
    for (int j = 0; j < n; j++)
      if (s[j] == 'Y') d[i | (1 << j)] = d[i];

  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < n; j++) {
      if (!(i & (1 << j))) {
        for (int k = 0; k < n; k++) {
          if (k == j) continue;
          if (!(i & (1 << k))) continue;

          d[i | (1 << j)] = min(d[i | (1 << j)], d[i] + w[k][j]);
        }
      }
    }
  }

  int ans = MAX;
  for (int i = 0; i < (1 << n); i++) {
    int j = ((1 << n) - 1) & i;
    int cnt = 0;
    while (j) {
      if (j & 1) cnt++;
      j >>= 1;
    }

    if (cnt >= p) ans = min(ans, d[i]);
  }

  cout << ans << '\n';
}
