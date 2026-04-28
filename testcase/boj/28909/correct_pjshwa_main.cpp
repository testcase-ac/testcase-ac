#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN + 1], V[MAXN + 1];

void solve() {
  int n, m, k; cin >> n >> m >> k;
  for (int i = 1; i <= n; ++i) cin >> A[i];

  auto edist = [&](int x) {
    if (x <= k) return k - x;
    else return x - k - 1;
  };

  while (m--) {
    int x; cin >> x;
    vector<int> candidates;
    for (int i = n; i >= 1; --i) {
      if (A[i] == x && !V[i]) candidates.push_back(i);
    }
    if (candidates.size()) {
      int mdist = n + 1, mpos = -1;
      for (int c : candidates) {
        int cdist = edist(c);
        if (cdist <= mdist) mdist = cdist, mpos = c;
      }
      cout << mpos << ' ';
      V[mpos] = 1;
      continue;
    }

    for (int i = n; i >= 1; --i) {
      if (A[i] > x && !V[i]) candidates.push_back(i);
    }
    if (candidates.size()) {
      int mdist = n + 1, mpos = -1;
      for (int c : candidates) {
        int cdist = edist(c);
        if (cdist <= mdist) mdist = cdist, mpos = c;
      }
      cout << mpos << ' ';
      V[mpos] = 1;
    }
    else cout << "-1 ";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
