#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
bool vis[MAX + 1];

void quit() {
  cout << "fail\n";
  exit(0);
}

void solve() {
  int N, M; cin >> N >> M;

  int l = 0; set<int> wait;
  for (int i = 0; i < N; i++) {
    int x; cin >> x; vis[x] = 1;
    while (l < x) {
      if (!vis[l]) wait.insert(l);
      l++;
    }

    if (wait.size() < 2) quit();

    // Make togi
    wait.erase(*wait.begin());

    // Fill togi
    auto it = wait.lower_bound(x - M);
    if (it == wait.end()) quit();
    wait.erase(it);
  }

  cout << "success\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
