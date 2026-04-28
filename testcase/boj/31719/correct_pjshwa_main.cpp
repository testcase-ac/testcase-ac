#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN]; deque<int> Q[2];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  // init
  for (int j = 0; j < 2; ++j) {
    while (!Q[j].empty()) Q[j].pop_back();
  }
  int tar = 1;

  for (int i = 0; i < N; ++i) {
    int f = 1;
    while (f) {
      f = 0;
      for (int j = 0; j < 2; ++j) {
        if (!Q[j].empty() && Q[j].front() == tar) {
          f = 1;
          while (!Q[j].empty()) Q[j].pop_front(), ++tar;
        }
      }
    }

    if (A[i] == tar) ++tar;
    else {
      int ok = 0;
      for (int j = 0; j < 2; ++j) {
        if (!Q[j].empty() && Q[j].back() + 1 == A[i]) {
          Q[j].push_back(A[i]);
          ok = 1;
          break;
        }
      }
      if (ok) continue;

      for (int j = 0; j < 2; ++j) {
        if (Q[j].empty()) {
          Q[j].push_back(A[i]);
          ok = 1;
          break;
        }
      }
      if (!ok) return cout << "NO\n", void();
    }
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
