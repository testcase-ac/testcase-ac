#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  reverse(A, A + N);

  vector<int> pi(N);
  for (int i = 1, j = 0; i < N; i++) {
    while (j && A[i] != A[j]) j = pi[j - 1];
    if (A[i] == A[j]) pi[i] = ++j;
  }

  int maxp = *max_element(pi.begin(), pi.end()), ans = 0;
  for (int e : pi) ans += (e == maxp);

  if (maxp == 0) cout << "-1\n";
  else cout << maxp << ' ' << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
