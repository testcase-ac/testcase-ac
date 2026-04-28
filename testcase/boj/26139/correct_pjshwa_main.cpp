#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj_m[MAXN + 1];
vector<pii> adj_s[MAXN + 1];
pii adj_r[MAXN + 1];
int S[MAXN + 1], indegree[MAXN + 1];

void solve() {
  int m, n, q; cin >> m >> n >> q;
  for (int i = 0; i < n; ++i) {
    string op; int x, y, z; cin >> op >> x >> y >> z;
    if (op == "S") {
      adj_s[x].emplace_back(y, z);
      adj_r[y] = {-1, x};
      adj_r[z] = {-2, x};
      ++indegree[y]; ++indegree[z];
    }
    else {
      adj_m[x].emplace_back(z);
      adj_m[y].emplace_back(z);
      adj_r[z] = {x, y};
      indegree[z] += 2;
    }
  }

  S[1] = m;
  queue<int> Q; Q.push(1);
  while (!Q.empty()) {
    int v = Q.front(); Q.pop();

    int h = S[v] / 2;
    for (auto& [u1, u2] : adj_s[v]) {
      S[u2] = h;
      S[u1] = S[v] - h;
      if (--indegree[u1] == 0) Q.push(u1);
      if (--indegree[u2] == 0) Q.push(u2);
    }

    for (auto& u : adj_m[v]) {
      S[u] += S[v];
      if (--indegree[u] == 0) Q.push(u);
    }
  }

  while (q--) {
    int x, k; cin >> x >> k;
    if (S[x] < k) {
      cout << "none\n";
      continue;
    }

    while (x > 1) {
      auto [u1, u2] = adj_r[x];
      if (u1 == -1) x = u2, k = 2 * k - 1;
      else if (u1 == -2) x = u2, k = 2 * k;
      else if (S[u1] > S[u2]) {
        if (k <= 2 * S[u2]) {
          if (k & 1) x = u1;
          else x = u2;
          k = (k + 1) / 2;
        }
        else {
          k -= S[u2];
          x = u1;
        }
      }
      else {
        if (k <= 2 * S[u1]) {
          if (k & 1) x = u1;
          else x = u2;
          k = (k + 1) / 2;
        }
        else {
          k -= S[u1];
          x = u2;
        }
      }
    }

    cout << k << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
