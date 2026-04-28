#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
int C[MAXN + 1], D[MAXN + 1];

void solve() {
  int N, maxl = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int l; cin >> l;
    maxl = max(maxl, l);
    ++C[l];
  }

  ll cur = 1, ans = C[maxl];
  deque<ll> Q, nQ;
  for (int i = 0; i < C[maxl]; ++i) Q.push_back(1);

  for (int l = maxl; l >= 1; --l) {
    assert(!Q.empty() && Q.size() % 2 == 0);

    for (int i = 0; i < C[l - 1]; ++i) nQ.push_back(cur), ans += cur;
    while (!Q.empty()) {
      ll a = Q.front(); Q.pop_front();
      ll b = Q.front(); Q.pop_front();
      nQ.push_back(a + b);
    }
    cur = nQ.back();
    swap(Q, nQ);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
