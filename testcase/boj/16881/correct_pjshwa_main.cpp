#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, sum = 0; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    vector<int> A; int x;
    for (int j = 0; j < M; ++j) {
      cin >> x; A.push_back(x);
    }

    int lg = A.back(); A.pop_back();
    while (!A.empty()) {
      int e = A.back(); A.pop_back();
      if (e <= lg) lg = e - 1;
      else lg = e;
    }
    sum ^= lg;
  }

  if (sum == 0) cout << "cubelover\n";
  else cout << "koosaga\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
