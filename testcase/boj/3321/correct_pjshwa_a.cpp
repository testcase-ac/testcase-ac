#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[15000][1501];
int heights[1500];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  queue<int> order, zwl;
  for (int j = 0; j < m; j++) order.push(j);

  int o, c, mv = 0;
  for (int i = 0; i < n; i++) {
    c = 0;
    for (int j = 0; j < m; j++) {
      o = order.front();
      order.pop();
      if (board[i][o] == '1') {
        heights[o]++;
        mv = max(mv, heights[o] * ++c);
        order.push(o);
      }
      else {
        heights[o] = 0;
        zwl.push(o);
      }
    }

    while (!zwl.empty()) {
      order.push(zwl.front());
      zwl.pop();
    }
  }

  cout << mv << '\n';
}
