#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int seq[MAX];
bool seq_p[MAX][MAX];

bool is_palindrome(int s, int e) {
  return seq_p[s][e];
}

void solve() {
  int n;
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

  int start = 0, cur = 1, cnt = 0;
  while (start < n) {
    if (cur == n) return cout << "-1\n", void();
    if ((cur - start) % 2 && is_palindrome(start, cur)) {
      cnt++;
      start = cur + 1;
    }
    cur++;
  }

  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
