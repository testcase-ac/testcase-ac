#include <bits/stdc++.h>
using namespace std;

bool visited[26];
vector<int> graph[26];

bool dfs(int v, int target) {
  visited[v] = true;
  bool res = false;

  for (auto dst : graph[v]) {
    if (dst == target) return true;
    if (!visited[dst]) res |= dfs(dst, target);
  }

  return res;
}

int main() {
  int n, m;
  char a, b;

  scanf("%d\n", &n);
  while (n--) {
    scanf("%c is %c\n", &a, &b);
    graph[b - 'a'].push_back(a - 'a');
  }

  scanf("%d\n", &m);
  while (m--) {
    scanf("%c is %c\n", &a, &b);
    memset(visited, false, sizeof(visited));
    printf("%c\n", dfs(b - 'a', a - 'a') ? 'T' : 'F');
  }
}
