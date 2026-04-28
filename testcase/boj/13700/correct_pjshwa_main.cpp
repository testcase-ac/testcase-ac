#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool vis[MAX + 1];

void solve() {
  int N, S, D, F, B, K;
  cin >> N >> S >> D >> F >> B >> K;
  for (int i = 0; i < K; i++) {
    int P;
    cin >> P;
    vis[P] = 1;
  }

  queue<pii> q;
  q.push({S, 0});
  vis[S] = 1;

  while (!q.empty()) {
    auto [u, c] = q.front();
    q.pop();

    if (u == D) return cout << c << '\n', void();

    if (u + F <= N && !vis[u + F]) {
      q.push({u + F, c + 1});
      vis[u + F] = 1;
    }
    if (u - B >= 1 && !vis[u - B]) {
      q.push({u - B, c + 1});
      vis[u - B] = 1;
    }
  }

  cout << "BUG FOUND\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
