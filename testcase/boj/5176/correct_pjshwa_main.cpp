#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M;
  cin >> M >> N;
  vector<int> A(N + 1, 0);

  int ans = 0;
  while (M--) {
    int x;
    cin >> x;

    if (A[x]) ans++;
    else A[x] = 1;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
