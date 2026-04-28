#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool vis[501][501];
int main() {
  fast_io();

  int n;
  cin >> n;

  bool stop = false;
  int sv = 1;
  vis[1][n] = vis[n][1] = true;

  while (!stop) {
    cout << 'a' << sv << ' ';

    stop = true;
    for (int i = 1; i <= n; i++) {
      if (i == sv || vis[sv][i]) continue;

      stop = false;
      vis[sv][i] = vis[i][sv] = true;
      sv = i;
      break;
    }
  }

  cout << "a1\n";
}
