#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
deque<int> board[MAX][MAX];
queue<int> dead[MAX][MAX];
int nutri[MAX][MAX], addend[MAX][MAX];
int n;

void spring() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int l = board[i][j].size();
    for (int k = 0; k < l; k++) {
      int c_age = board[i][j].front();
      board[i][j].pop_front();

      if (nutri[i][j] >= c_age) {
        nutri[i][j] -= c_age;
        board[i][j].push_back(c_age + 1);
      }
      else dead[i][j].push(c_age);
    }
  }
}

void summer() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    while (!dead[i][j].empty()) {
      int c_age = dead[i][j].front();
      dead[i][j].pop();

      nutri[i][j] += c_age / 2;
    }
  }
}

void autumn() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int l = board[i][j].size();
    for (int k = 0; k < l; k++) {
      int c_age = board[i][j].front();
      board[i][j].pop_front();

      if (c_age % 5 == 0) {
        if (i - 1 >= 0 && j - 1 >= 0) board[i - 1][j - 1].push_front(1);
        if (i - 1 >= 0) board[i - 1][j].push_front(1);
        if (i - 1 >= 0 && j + 1 < n) board[i - 1][j + 1].push_front(1);
        if (j - 1 >= 0) board[i][j - 1].push_front(1);
        if (j + 1 < n) board[i][j + 1].push_front(1);
        if (i + 1 < n && j - 1 >= 0) board[i + 1][j - 1].push_front(1);
        if (i + 1 < n) board[i + 1][j].push_front(1);
        if (i + 1 < n && j + 1 < n) board[i + 1][j + 1].push_front(1);
      }

      board[i][j].push_back(c_age);
    }
  }
}

void winter() {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) nutri[i][j] += addend[i][j];
}

int main() {
  fast_io();

  int m, k;
  cin >> n >> m >> k;
  vector<tuple<int, int, int>> trees;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) nutri[i][j] = 5, cin >> addend[i][j];
  for (int i = 0; i < m; i++) {
    int x, y, age;
    cin >> x >> y >> age;
    trees.push_back(make_tuple(age, x - 1, y - 1));
  }
  sort(trees.begin(), trees.end());
  for (auto [age, x, y] : trees) board[x][y].push_back(age);

  while (k--) {
    spring();
    summer();
    autumn();
    winter();
  }

  int ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ans += board[i][j].size();
  cout << ans << '\n';
}
