#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, a, b;
  cin >> N >> a >> b;
  vector<int> A(a), B(b);
  for (int i = 0; i < a; i++) cin >> A[i];
  for (int i = 0; i < b; i++) cin >> B[i];
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  reverse(A.begin(), A.end());
  reverse(B.begin(), B.end());

  stack<int> s;
  int cur = 0;
  for (int i = 0; i < min(a, N); i++) {
    s.push(A[i]);
    cur += A[i];
  }

  int bi = 0;
  while (s.size() + bi * 2 < N) cur += B[bi++];
  if (s.size() + bi * 2 > N) {
    cur -= s.top();
    s.pop();
  }

  int ans = cur;
  while (1) {
    if (bi == b || s.size() < 2) break;

    cur += B[bi++];
    for (int i = 0; i < 2; i++) {
      cur -= s.top();
      s.pop();
    }

    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
