#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN];

void solve() {
  int N; cin >> N;

  map<int, int> tal;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    while (A[i] % 2 == 0) A[i] /= 2;
    ++tal[A[i]];
  }

  int ans = 0;
  for (auto& [_, cnt] : tal) ans = max(ans, cnt);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
