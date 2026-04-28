#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, MOD = 1e9 + 7;
int F[MAX + 1];
vector<pii> V[MAX + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= Q; i++) {
    int s, e; cin >> s >> e;
    V[s].push_back({e, i});
  }

  priority_queue<tii> W;
  for (int s = 1; s <= N; s++) {
    for (auto [e, i] : V[s]) W.push({i, s, e});

    if (W.empty()) cout << "0 ";
    else {
      int ps = get<1>(W.top());
      cout << F[s - ps + 1] << ' ';
    }

    while (!W.empty() && get<2>(W.top()) <= s) W.pop();
  }
}

int main() {
  fast_io();

  F[0] = F[1] = 1;
  for (int i = 2; i <= MAX; i++) F[i] = (F[i - 1] + F[i - 2]) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
