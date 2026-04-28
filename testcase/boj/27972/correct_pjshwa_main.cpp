#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  vector<int> B; B.push_back(A[0]);
  for (int i = 1; i < N; ++i) {
    if (A[i] != A[i - 1]) B.push_back(A[i]);
  }
  N = B.size();
  if (N == 1) return cout << "1\n", []{}();

  int ans = 2, streak = 2, dir = B[0] > B[1] ? -1 : 1;
  for (int i = 2; i < N; i++) {
    if (B[i] > B[i - 1]) {
      if (dir == -1) streak = 2;
      else streak++;
    }
    else {
      if (dir == 1) streak = 2;
      else streak++;
    }
    dir = B[i - 1] > B[i] ? -1 : 1;
    ans = max(ans, streak);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
