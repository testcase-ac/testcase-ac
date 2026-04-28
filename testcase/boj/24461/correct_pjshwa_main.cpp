#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX];
int indegree[MAX];
bool vis[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
    indegree[b]++;
    indegree[a]++;
  }

  queue<int> q;
  for (int i = 0; i < n; i++) {
    if (indegree[i] == 1) q.push(i);
  }

  while (1) {
    queue<int> nq;
    if (q.size() <= 2) break;

    while (!q.empty()) {
      int f = q.front();
      q.pop();

      vis[f] = 1;
      for (int d : graph[f]) {
        indegree[d]--;
        if (indegree[d] == 1) nq.push(d);
      }
    }
    q = nq;
  }

  for (int i = 0; i < n; i++) if (!vis[i]) cout << i << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
