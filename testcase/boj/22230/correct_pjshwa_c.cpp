#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
int table[MAX][MAX];

int n = 6;
int m = 36;

void print_table() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << table[i][j] << " ";
    }
    cout << endl;
  }
}

void dfs(int i, int j) {
  // cout << "i: " << i << " j: " << j << endl;
  if (i == n && j == 0) {
    for (int k = 0; k < n; k++) if (table[0][k] == 0) return;
    for (int k = 0; k < n; k++) if (table[k][0] == 0) return;

    set<string> s;

    for (int k = 0; k < n; k++) {
      string cur = "";
      for (int l = 0; l < n; l++) cur += table[k][l] + '0';
      s.insert(cur);
    }

    for (int l = 0; l < n; l++) {
      string cur = "";
      for (int k = 0; k < n; k++) cur += table[k][l] + '0';
      s.insert(cur);
    }

    string cur = "";
    for (int l = 0; l < n; l++) cur += table[l][l] + '0';
    s.insert(cur);

    cur = "";
    for (int l = 0; l < n; l++) cur += table[l][n - 1 - l] + '0';
    s.insert(cur);

    if (s.size() == 2 * n + 2) {
      for (string str : s) {
        int ir = stoi(str);
        if (ir % m) return;
      }
      print_table();
    }
    return;
  }

  for (int k = 0; k < 10; k++) {
    if ((i == 0 || j == 0) && k == 0) continue;
    table[i][j] = k;
    if (j == n - 1) {
      int s = 0, pw = 1;
      for (int l = n - 1; l >= 0; l--) {
        s += table[i][l] * pw;
        pw *= 10;
      }
      if (s % m == 0) dfs(i + 1, 0);
    }
    else dfs(i, j + 1);
    table[i][j] = -1;
  }
}

int main() {
  fast_io();

  memset(table, -1, sizeof(table));
  dfs(0, 0);
}
