#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int A[MAX];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = 0, esum = 0, osum = 0, ei = 0;
  for (int si = 0; si < N; si++) {
    while (ei < N) {
      if (A[ei] % 2 == 0) esum++, ei++;
      else if (osum < K) osum++, ei++;
      else break;
    }
    ans = max(ans, esum);
    if (A[si] % 2 == 0) esum--;
    else osum--;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
