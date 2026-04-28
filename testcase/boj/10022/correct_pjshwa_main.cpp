#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 400;
int grass[MAX + 1][MAX + 1], pf[MAX + 1][MAX + 1];

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> grass[i][j];
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) pf[i][j] = pf[i][j - 1] + grass[i][j];

  int mgrass = 0;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    int cgrass = 0;
    for (int l = 0; l < k; l++) {
      if (i - k + l <= 0) continue;
      cgrass += pf[i - k + l][min(n, j + l)] - pf[i - k + l][max(0, j - l - 1)];
    }
    for (int l = 0; l < k; l++) {
      if (i + k - l > n) continue;
      cgrass += pf[i + k - l][min(n, j + l)] - pf[i + k - l][max(0, j - l - 1)];
    }
    cgrass += pf[i][min(n, j + k)] - pf[i][max(0, j - k - 1)];
    mgrass = max(mgrass, cgrass);
  }

  cout << mgrass << '\n';
}
