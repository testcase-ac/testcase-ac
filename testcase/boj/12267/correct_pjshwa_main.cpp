#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 36;
int B[MAXN][MAXN], N, Nq;

bool validate_set(set<int>& s) {
  for (int e : s) {
    if (e <= 0 || e > Nq) return false;
  }
  return (int)s.size() == Nq;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  cin >> N; Nq = N * N;
  for (int i = 0; i < Nq; ++i) for (int j = 0; j < Nq; ++j) cin >> B[i][j];

  for (int i = 0; i < Nq; ++i) {
    set<int> set_r, set_c;
    for (int j = 0; j < Nq; ++j) {
      set_r.insert(B[i][j]);
      set_c.insert(B[j][i]);
    }
    if (!validate_set(set_r) || !validate_set(set_c)) {
      cout << "No\n";
      return;
    }
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    set<int> set_q;
    for (int ii = i * N; ii < i * N + N; ++ii) {
      for (int jj = j * N; jj < j * N + N; ++jj) {
        set_q.insert(B[ii][jj]);
      }
    }
    if (!validate_set(set_q)) {
      cout << "No\n";
      return;
    }
  }

  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
