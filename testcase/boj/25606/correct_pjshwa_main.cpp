#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
ll A[MAX + 1];
vector<ll> idepl[MAX + 1];

void solve() {
  ll N, M, Q;
  cin >> N >> M >> Q;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];

    // Last day before it becomes 0
    ll depl = i + (A[i] - 1) / M;
    if (depl <= N) idepl[depl].push_back(i);
  }

  vector<ll> ans1(N + 1), ans2(N + 1); int cnt;

  cnt = 0;
  for (int i = 1; i <= N; i++) {
    ll val = A[i] - M * (N - i);
    if (val <= 0) continue;

    cnt++;
    ans1[N] += val;
  }

  for (int i = N - 1; i >= 1; i--) {
    ans1[i] = ans1[i + 1] - A[i + 1];
    cnt--;
    ans1[i] += M * cnt;

    for (int v : idepl[i]) {
      ll rem = A[v] % M;
      if (rem == 0) rem = M;

      ans1[i] += rem;
      cnt++;
    }
  }

  cnt = 0;
  for (int i = 1; i <= N; i++) {
    cnt++;
    for (int v : idepl[i]) {
      ll rem = A[v] % M;
      if (rem == 0) rem = M;
      ans2[i] += rem;
      cnt--;
    }
    ans2[i] += M * cnt;
  }

  while (Q--) {
    int op, t;
    cin >> op >> t;
    if (op == 1) cout << ans1[t] << '\n';
    if (op == 2) {
      if (t == 1) cout << "0\n";
      else cout << ans2[t - 1] << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
