#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[1001];
int indegree[1001];
int strahler[1001];
vector<int> in_strahler[1001];

int get_strahler(int i) {
  int mv = -1;
  for (int el : in_strahler[i]) mv = max(mv, el);

  int cnt = 0;
  for (int el : in_strahler[i]) {
    if (el == mv) cnt++;
  }
  return cnt == 1 ? mv : mv + 1;
}

int main() {
  fast_io();

  int t, k, n, m, a, b;
  cin >> t;
  while (t--) {
    cin >> k >> n >> m;

    memset(indegree, 0, sizeof(indegree));
    memset(strahler, 0, sizeof(strahler));
    for (int i = 1; i <= n; i++) {
      graph[i].clear();
      in_strahler[i].clear();
    }

    while (m--) {
      cin >> a >> b;
      graph[a].push_back(b);
      indegree[b]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
      if (!indegree[i]) {
        in_strahler[i].push_back(1);
        q.push(i);
      }
    }

    for (int i = 1; i <= n; i++) {
      a = q.front();
      q.pop();

      strahler[a] = get_strahler(a);

      for (int dst : graph[a]) {
        indegree[dst]--;
        in_strahler[dst].push_back(strahler[a]);
        if (!indegree[dst]) q.push(dst);
      }
    }

    int mv = -1;
    for (int i = 1; i <= n; i++) mv = max(mv, strahler[i]);
    cout << k << ' ' << mv << '\n';
  }
}
