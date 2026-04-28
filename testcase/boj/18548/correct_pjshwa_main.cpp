#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
int A[MAX], P[2 * MAX][2 * MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> A[i];
  for (int i = 0; i < 2 * n - 1; i++) for (int j = 0; j < 2 * n - 1; j++) {
    P[i][j] = (i + j) % n;
  }

  cout << 2 * n - 1 << '\n';
  for (int i = 0; i < 2 * n - 1; i++) {
    for (int j = 0; j < 2 * n - 1; j++) {
      cout << A[P[i][j]] << ' ';
    }
    cout << '\n';
  }

}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
