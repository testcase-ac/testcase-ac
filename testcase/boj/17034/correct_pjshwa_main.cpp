#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> S[MAX + 1];

void solve() {
  int N; cin >> N;

  int popi = 0, maxi = 0, maxpop = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (x < maxpop) return cout << i << '\n', void();

    int l = 0, r = maxi + 1;
    while (l < r) {
      int m = (l + r) / 2;
      if (S[m].empty() || S[m][0] < x) l = m + 1;
      else r = m;
    }

    int pushi = l; maxi = max(maxi, pushi);
    while (!S[pushi].empty() && S[pushi].back() < x) {
      if (S[popi].empty()) popi++;
      maxpop = max(maxpop, S[popi].back()); S[popi].pop_back();
    }

    assert(S[pushi].empty() || S[pushi].back() >= x);
    S[pushi].push_back(x);
  }

  cout << N << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
