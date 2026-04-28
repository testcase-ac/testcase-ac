#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  vector<int> A;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    A.push_back(x);
  }

  int ans = 0;
  for (int b = 19; b >= 0; --b) {
    int cnt = 0; 
    for (int e : A) {
      if (e & (1 << b)) ++cnt;
    }

    if (cnt >= K) {
      ans |= (1 << b);

      vector<int> NA;
      for (int e : A) {
        if (e & (1 << b)) NA.push_back(e);
      }
      A = NA;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
