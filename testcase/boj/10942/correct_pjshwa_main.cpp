#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int seq[2000];
bool seq_p[2000][2000];
int main() {
  fast_io();

  int n, m, s, e;

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> seq[i];
    seq_p[i][i] = true;
  }

  for (int i = 0; i < n - 1; i++) {
    seq_p[i][i + 1] = seq[i] == seq[i + 1];
  }

  for (int diff = 2; diff < n; diff++) {
    for (int i = 0; i < n - diff; i++) {
      int j = i + diff;
      seq_p[i][j] = (seq[i] == seq[j] && seq_p[i + 1][j - 1]);
    }
  }

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> s >> e;
    cout << (seq_p[s - 1][e - 1] ? "1\n" : "0\n");
  }
}
