#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

vector<int> graph[123457];
vector<int> rgraph[123457];
long long sp[123457];
priority_queue<pii> pq_depth;

void dfs_depth_check(int node, int cd) {
  pq_depth.push({cd, node});
  for (auto el : rgraph[node]) dfs_depth_check(el, cd + 1);
}

int main() {
  int n;
  cin >> n;

  char kind;
  int ai, pi;
  for (int i = 2; i <= n; i++) {
    cin >> kind >> ai >> pi;
    if (kind == 'W') sp[i] -= ai;
    else sp[i] += ai;

    graph[i].push_back(pi);
    rgraph[pi].push_back(i);
  }
  dfs_depth_check(1, 0);

  while (1) {
    auto cv = pq_depth.top().second;
    pq_depth.pop();

    if (cv == 1) {
      cout << sp[1] << '\n';
      break;
    }

    auto dst = graph[cv][0];
    if (sp[cv] > 0) {
      sp[dst] += sp[cv];
      sp[cv] = 0;
    }
  }
}
