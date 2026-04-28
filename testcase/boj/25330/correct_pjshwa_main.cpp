#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int A[MAX], P[MAX];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> P[i];

  int ans = 0;
  for (int state = 0; state < (1 << N); state++) {
    vector<int> c;
    int cur = 0;

    for (int i = 0; i < N; i++) {
      if (!(state & (1 << i))) continue;
      c.push_back(A[i]);
      cur += P[i];
    }
    sort(c.begin(), c.end());

    int need = 0, prev = 0;
    for (int e : c) {
      prev += e;
      need += prev;
    }

    if (need <= K) ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
