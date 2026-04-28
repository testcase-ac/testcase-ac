#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> brc[MAX], rinv[MAX];
bool visr[MAX], visb[MAX];
set<int> indegree[MAX];
int n;

void solve() {
  int m, t;
  cin >> n >> m >> t;

  set<int> pbs;
  for (int i = 0; i < m; i++) {
    int b;
    cin >> b;
    pbs.insert(b - 1);
  }
  for (int i = 0; i < n; i++) {
    int q, x;
    cin >> q;
    while (q--) cin >> x, x--, brc[i].push_back(x);
  }
  for (int i = 0; i < n - m; i++) {
    int b, q, x;
    cin >> b >> q;
    while (q--) {
      cin >> x;
      indegree[b - 1].insert(x - 1);
      rinv[x - 1].push_back(b - 1);
    }
  }

  queue<int> q;
  set<int> ans;
  for (int b : pbs) q.push(b), ans.insert(b);

  stack<int> nxt;
  while (t--) {
    while (!q.empty()) {
      int b = q.front();
      q.pop();

      if (visb[b]) continue;
      visb[b] = true;

      for (int r : brc[b]) {
        if (visr[r]) continue;
        visr[r] = true;

        for (int s : rinv[r]) {
          indegree[s].erase(r);
          if (indegree[s].empty()) nxt.push(s), ans.insert(s);
        }
      }
    }
    while (!nxt.empty()) {
      int b = nxt.top();
      nxt.pop();
      q.push(b);
    }
  }

  cout << ans.size() << '\n';
  for (int b : ans) cout << b + 1 << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
