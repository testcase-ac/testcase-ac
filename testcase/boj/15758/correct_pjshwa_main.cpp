#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int n, m;
vector<vector<int>> obs;

bool check_tsortable(int to) {
  vector<int> graph[n + 1];
  int indegree[n + 1] = {0};

  for (int i = 0; i < min(to, m); i++) {
    int sz = obs[i].size();

    for (int j = 0; j < sz - 1; j++) {
      graph[obs[i][j]].push_back(obs[i][j + 1]);
      indegree[obs[i][j + 1]]++;
    }
  }

  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }

  int a;
  for (int i = 1; i <= n; i++) {
    if (q.empty()) return false;

    a = q.front();
    q.pop();

    for (int dst : graph[a]) if (!--indegree[dst]) q.push(dst);
  }

  return true;
}

int main() {
  fast_io();

  cin >> n >> m;
  obs.resize(m);
  for (int i = 0; i < m; i++) {
    int mi, xi;
    cin >> mi;
    for (int j = 0; j < mi; j++) cin >> xi, obs[i].push_back(xi);
  }

  int left = 0, right = m + 1;
  int mid = (left + right) / 2;

  while (left < right) {
    if (check_tsortable(mid)) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  vector<int> graph[n + 1];
  int indegree[n + 1] = {0};

  for (int i = 0; i < mid - 1; i++) {
    int sz = obs[i].size();

    for (int j = 0; j < sz - 1; j++) {
      graph[obs[i][j]].push_back(obs[i][j + 1]);
      indegree[obs[i][j + 1]]++;
    }
  }

  priority_queue<int, vector<int>, greater<int>> q;
  for (int i = 1; i <= n; i++) {
    if (!indegree[i]) q.push(i);
  }

  int a;
  for (int i = 1; i <= n; i++) {
    a = q.top();
    cout << a << ' ';
    q.pop();

    for (int dst : graph[a]) if (!--indegree[dst]) q.push(dst);
  }
}
