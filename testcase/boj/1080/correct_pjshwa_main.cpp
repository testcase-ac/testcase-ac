#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char sboard[51][51], dboard[51][51];

int cnt = 0;
void filp_dboard(int x, int y) {
  cnt++;
  for (int i = x; i < x + 3; i++) {
    for (int j = y; j < y + 3; j++) {
      if (dboard[i][j] == '0') dboard[i][j] = '1';
      else dboard[i][j] = '0';
    }
  }
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> sboard[i];
  for (int i = 0; i < n; i++) cin >> dboard[i];

  for (int i = 0; i < n - 2; i++) {
    for (int j = 0; j < m - 2; j++) {
      if (sboard[i][j] != dboard[i][j]) filp_dboard(i, j);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (sboard[i][j] != dboard[i][j]) {
        cout << -1;
        return 0;
      }
    }
  }
  cout << cnt;
}
