#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[1001];
int indegree[1001];
int main() {
  fast_io();

  int n, m, a, b, c;
  cin >> n >> m;

  while (m--) {
    cin >> a;
    cin >> b;

    while (--a) {
      cin >> c;
      graph[b].push_back(c);
      indegree[c]++;
      b = c;
    }
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }

  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (q.empty()) {
      cout << "0\n";
      return 0;
    }

    a = q.front();
    q.pop();
    ans.push_back(a);

    for (int dst : graph[a]) {
      indegree[dst]--;
      if (!indegree[dst]) q.push(dst);
    }
  }

  for (int el : ans) cout << el << '\n';
}
