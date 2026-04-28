#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int pfo[405][405], pfr[405][405];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> pfo[i][j];
  for (int i = 1; i <= n; i++) for (int j = n; j >= 1; j--) pfr[i][j] = pfo[i][j] + pfr[i - 1][j + 1];
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) pfo[i][j] += pfo[i - 1][j - 1];

  int mv = 0;
  for (int s = 2; s <= n; s++) {
    for (int i = s; i <= n; i++) for (int j = s; j <= n; j++) {
      mv = max(mv, pfo[i][j] - pfo[i - s][j - s] - pfr[i][j - s + 1] + pfr[i - s][j + 1]);
    }
  }
  cout << mv;
}
