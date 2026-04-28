#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 1];

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    if (A[i] == i) {
      ++ans;
      if (i == 1) A[i] = 2;
      else A[i] = 1;
    }
  }

  cout << ans << '\n';
  for (int i = 1; i <= N; ++i) cout << A[i] << ' ';
  cout << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
