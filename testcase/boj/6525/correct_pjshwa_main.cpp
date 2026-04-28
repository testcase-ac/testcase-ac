#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX][MAX];

int N;
void solve() {
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (A[i][j] + A[0][0] != A[i][0] + A[0][j]) {
      return cout << "not homogeneous\n", void();
    }
  }
  cout << "homogeneous\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
