#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int lp[MAX + 1];
vector<int> pr;

bool is_prime(int x) {
  if (x < 2) return false;
  return lp[x] == x;
}

void solve() {
  int N; cin >> N;
  int board[N * N][N * N];

  set<int> used_pr;
  for (int i = 0; i < N * N; i++) for (int j = 0; j < N * N; j++) {
    cin >> board[i][j];
    if (is_prime(board[i][j])) used_pr.insert(board[i][j]);
  }

  for (int i = 0; i < N * N; i++) for (int j = 0; j < N * N; j++) {
    if (board[i][j] == 0) {
      while (used_pr.count(pr.back())) pr.pop_back();
      board[i][j] = pr.back(); pr.pop_back();
    }
    cout << board[i][j] << " \n"[j == N * N - 1];
  }
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
