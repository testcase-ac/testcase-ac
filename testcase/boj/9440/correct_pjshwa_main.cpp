#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  while (cin >> N) {
    if (N == 0) break;

    vector<int> A; int z = 0;
    for (int i = 0; i < N; i++) {
      int x; cin >> x;
      if (x == 0) z++;
      else A.push_back(x);
    }
    sort(A.begin(), A.end(), greater<int>());

    int f1 = A.back(); A.pop_back();
    int f2 = A.back(); A.pop_back();
    while (z--) A.push_back(0);

    while (1) {
      if (A.empty()) break;
      else f1 *= 10, f1 += A.back(), A.pop_back();

      if (A.empty()) break;
      else f2 *= 10, f2 += A.back(), A.pop_back();
    }
    cout << f1 + f2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
