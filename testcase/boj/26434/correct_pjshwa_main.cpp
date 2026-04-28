#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 4e5;
ll A[MAX + 1], P[MAX + 1], PP[MAX + 1], R[MAX + 1], ans;

void add_segment(int l, int r) {
  if (r < l) return;
  ans += PP[r] + R[l - 1] - (r + 1) * P[l - 1];
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    R[i] = R[i - 1] + i * A[i];
    P[i] = P[i - 1] + A[i];
    PP[i] = PP[i - 1] + P[i];
  }

  ans = 0;
  stack<pii> T;
  T.push({1, 0});

  for (int r = 1; r <= N + 1; r++) {
    while (!T.empty()) {
      auto [i, v] = T.top();
      if (r == N + 1 || v > P[r]) {
        add_segment(i, r - 1);
        T.pop();
      }
      else break;
    }
    if (r < N) T.push({r + 1, P[r]});
  }

  cout << ans << '\n';  
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
