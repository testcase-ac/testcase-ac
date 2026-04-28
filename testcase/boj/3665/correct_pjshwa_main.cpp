#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int indegree[501];
int adj[501][501];
vector<int> graph[501];
int main() {
  fast_io();

  int t, n, m, ai, bi;
  cin >> t;

  while (t--) {
    cin >> n;

    memset(adj, 0, sizeof(adj));
    memset(indegree, 0, sizeof(indegree));
    for (int i = 1; i <= n; i++) graph[i].clear();

    vector<int> input;
    for (int i = 1; i <= n; i++) {
      cin >> m;
      input.push_back(m);
    }

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        indegree[input[j]]++;
        adj[input[i]][input[j]] = 1;
      }
    }

    cin >> m;
    for (int i = 1; i <= m; i++) {
      cin >> ai >> bi;
      if (adj[bi][ai]) swap(ai, bi);

      adj[ai][bi] = 0;
      adj[bi][ai] = 1;
      indegree[bi]--;
      indegree[ai]++;
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (adj[i][j]) graph[i].push_back(j);
      }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
      if (!indegree[i]) q.push(i);
    }

    bool flag = true;
    vector<int> ans;
    int a;
    for (int i = 1; i <= n; i++) {
      if (q.empty()) {
        flag = false;
        break;
      }

      a = q.front();
      q.pop();

      ans.push_back(a);
      for (int d : graph[a]) {
        if (!--indegree[d]) q.push(d);
      }
    }

    if (flag) {
      for (int el : ans) cout << el << ' ';
    }
    else cout << "IMPOSSIBLE";
    cout << '\n';
  }
}
