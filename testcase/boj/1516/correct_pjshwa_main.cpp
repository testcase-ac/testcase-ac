#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[501];
int indegree[501];
int duration[501];
int result[501];
int main() {
  fast_io();

  int n, a, b;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> a;
    duration[i] = a;

    cin >> b;
    while (b != -1) {
      graph[b].push_back(i);
      indegree[i]++;
      cin >> b;
    }
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) {
      result[i] = duration[i];
      q.push(i);
    }
  }

  for (int i = 1; i <= n; i++) {
    a = q.front();
    q.pop();

    for (int dst : graph[a]) {
      result[dst] = max(result[dst], result[a] + duration[dst]);

      indegree[dst]--;
      if (!indegree[dst]) q.push(dst);
    }
  }

  for (int i = 1; i <= n; i++) cout << result[i] << '\n';
}
