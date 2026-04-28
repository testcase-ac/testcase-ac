#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[32001];
int indegree[32001];
int main() {
  fast_io();

  int n, m, a, b;
  cin >> n >> m;

  while (m--) {
    cin >> a >> b;
    graph[a].push_back(b);
    indegree[b]++;
  }

  priority_queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(-i);
  }

  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    a = -q.top();
    q.pop();
    ans.push_back(a);

    for (int dst : graph[a]) {
      indegree[dst]--;
      if (!indegree[dst]) q.push(-dst);
    }
  }

  for (int el : ans) cout << el << ' ';
}
