#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int indegree[MAX + 1], d[MAX + 1];
int score[MAX + 1][MAX + 1];
vector<int> graph[MAX + 1], ginv[MAX + 1];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    score[a][b] = max(score[a][b], c);
    graph[a].push_back(b);
    ginv[b].push_back(a);
    indegree[b]++;
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }

  for (int i = 1; i <= n; i++) {
    int a = q.front();
    q.pop();

    for (int par : ginv[a]) {
      d[a] = max(d[a], d[par] + score[par][a]);
    }

    for (int dst : graph[a]) {
      if (!--indegree[dst]) q.push(dst);
    }
  }

  cout << *max_element(d, d + n + 1) << '\n';
}
