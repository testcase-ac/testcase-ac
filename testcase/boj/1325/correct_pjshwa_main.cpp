#include <bits/stdc++.h>
using namespace std;

bool visited[(size_t)1e4];
int visit_count;
vector<int> graph[(size_t)1e4];

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void dfs(int v) {
  visited[v] = true;

  for (auto dst : graph[v]) {
    if (!visited[dst]) {
      visit_count++;
      dfs(dst);
    }
  }
}

int main() {
  fast_io();
  int n, m, x, y;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    cin >> x >> y;
    graph[y - 1].push_back(x - 1);
  }

  vector<int> answers;
  int max_answer = -1;
  for (int i = 0; i < n; i++) {
    memset(visited, false, sizeof(bool) * n);
    visit_count = 0;
    dfs(i);

    if (max_answer < visit_count) {
      max_answer = visit_count;
      answers.clear();
    }

    if (max_answer <= visit_count) {
      answers.push_back(i);
    }
  }

  sort(answers.begin(), answers.end());

  for (auto ans : answers) cout << ans + 1 << ' ';
  cout << '\n';
}
