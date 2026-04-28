#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
vector<int> rinv[MAX];
int targets[MAX];
bool visb[MAX];
set<int> indegree[MAX];
int n;

void solve() {
  int m, l;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int b, q, x;
    cin >> q;
    while (q--) {
      cin >> x;
      indegree[i].insert(x - 1);
      rinv[x - 1].push_back(i);
    }
    cin >> b;
    targets[i] = b - 1;
  }

  cin >> l;
  set<int> pbs;
  for (int i = 0; i < l; i++) {
    int b;
    cin >> b;
    pbs.insert(b - 1);
  }

  queue<int> q;
  for (int b : pbs) q.push(b);

  stack<int> nxt;
  while (!q.empty()) {
    int b = q.front();
    q.pop();

    if (visb[b]) continue;
    visb[b] = true;

    for (int ri : rinv[b]) {
      indegree[ri].erase(b);
      if (indegree[ri].empty()) q.push(targets[ri]);
    }
  }

  cout << accumulate(visb, visb + n, 0) << '\n';
  for (int i = 0; i < n; i++) if (visb[i]) cout << i + 1 << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
