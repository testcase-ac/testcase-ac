#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXM = 1e5;
int A[MAXM];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < M; ++i) cin >> A[i];

  vector<pii> pre, nxt;
  pre.emplace_back(1, N);
  for (int i = 0; i < M; ++i) {
    vector<pii> nxt;
    for (int j = 0; j < A[i] / 2; ++j) {
      int s, e, ok = 0; cin >> s >> e;

      // check if two segments intersect
      for (auto& [ps, pe] : pre) {
        if (max(ps, s) <= min(pe, e)) ok = 1;
      }
      if (ok) nxt.emplace_back(s, e);
    }
    swap(pre, nxt); nxt.clear();
  }

  if (pre.size()) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
