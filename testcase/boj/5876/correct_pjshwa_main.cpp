#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5;
bool vis[MAX][MAX];
char board[MAX + 1][MAX + 1];
int n, ans = 0, cur = 0;

void dfs(int i, int j, int mode, int rem) {
  if (mode == 1 && rem == 0) {
    ans = max(ans, cur);
    return;
  }
  
  if (i > 0 && !vis[i - 1][j]) {
    if (mode == 0) {
      vis[i - 1][j] = true;
      cur++;
      if (board[i - 1][j] == '(') dfs(i - 1, j, 0, rem + 1);
      else dfs(i - 1, j, 1, rem - 1);
      cur--;
      vis[i - 1][j] = false;
    }
    else if (board[i - 1][j] == ')') {
      vis[i - 1][j] = true;
      cur++;
      dfs(i - 1, j, 1, rem - 1);
      cur--;
      vis[i - 1][j] = false;
    }
  }

  if (j > 0 && !vis[i][j - 1]) {
    if (mode == 0) {
      vis[i][j - 1] = true;
      cur++;
      if (board[i][j - 1] == '(') dfs(i, j - 1, 0, rem + 1);
      else dfs(i, j - 1, 1, rem - 1);
      cur--;
      vis[i][j - 1] = false;
    }
    else if (board[i][j - 1] == ')') {
      vis[i][j - 1] = true;
      cur++;
      dfs(i, j - 1, 1, rem - 1);
      cur--;
      vis[i][j - 1] = false;
    }
  }

  if (i < n - 1 && !vis[i + 1][j]) {
    if (mode == 0) {
      vis[i + 1][j] = true;
      cur++;
      if (board[i + 1][j] == '(') dfs(i + 1, j, 0, rem + 1);
      else dfs(i + 1, j, 1, rem - 1);
      cur--;
      vis[i + 1][j] = false;
    }
    else if (board[i + 1][j] == ')') {
      vis[i + 1][j] = true;
      cur++;
      dfs(i + 1, j, 1, rem - 1);
      cur--;
      vis[i + 1][j] = false;
    }
  }

  if (j < n - 1 && !vis[i][j + 1]) {
    if (mode == 0) {
      vis[i][j + 1] = true;
      cur++;
      if (board[i][j + 1] == '(') dfs(i, j + 1, 0, rem + 1);
      else dfs(i, j + 1, 1, rem - 1);
      cur--;
      vis[i][j + 1] = false;
    }
    else if (board[i][j + 1] == ')') {
      vis[i][j + 1] = true;
      cur++;
      dfs(i, j + 1, 1, rem - 1);
      cur--;
      vis[i][j + 1] = false;
    }
  }

}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];
  if (board[0][0] == '(') {
    cur++;
    vis[0][0] = true;
    dfs(0, 0, 0, 1);
  }
  cout << ans << '\n';
}
