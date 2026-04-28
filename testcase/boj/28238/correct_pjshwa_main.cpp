#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int t[MAX];

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (int i = 0; i < n; i++) {
    int x;
    for (int j = 0; j < 5; j++) {
      cin >> x;
      A[i] = A[i] * 2 + x;
    }
  }

  int mmax = 0;
  for (int i = 4; i >= 0; i--) for (int j = i - 1; j >= 0; j--) {
    int cnt = 0;
    for (int s : A) {
      int x = s & (1 << i);
      int y = s & (1 << j);
      if (x && y) cnt++;
    }
    mmax = max(mmax, cnt);
  }

  cout << mmax << '\n';
  for (int i = 4; i >= 0; i--) for (int j = i - 1; j >= 0; j--) {
    int cnt = 0;
    for (int s : A) {
      int x = s & (1 << i);
      int y = s & (1 << j);
      if (x && y) cnt++;
    }
    if (cnt == mmax) {
      for (int k = 4; k >= 0; k--) {
        if (k == i || k == j) cout << "1 ";
        else cout << "0 ";
      }
      cout << '\n';
      exit(0);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
