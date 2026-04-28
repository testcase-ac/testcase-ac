#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[51][51];
int n, m;

void toggleColumn(int j) {
  for (int k = 0; k < n; k++) {
    if (board[k][j] == '0') board[k][j] = '1';
    else board[k][j] = '0';
  }
}

bool rowOn(int i) {
  bool on = true;
  for (int j = 0; j < m; j++) on &= (board[i][j] == '1');
  return on;
}

int main() {
  fast_io();

  int K;
  cin >> n >> m;

  for (int i = 0; i < n; i++) cin >> board[i];
  cin >> K;

  set<int> toggled;
  int cnt, mv = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (board[i][j] == '0') {
        toggled.insert(j);
        toggleColumn(j);
      }
    }

    if (toggled.size() <= K && (K - toggled.size()) % 2 == 0) {
      cnt = 0;
      for (int k = 0; k < n; k++) {
        if (rowOn(k)) cnt++;
      }
      mv = max(mv, cnt);
    }

    for (int j : toggled) toggleColumn(j);

    toggled.clear();
  }

  cout << mv;
}
