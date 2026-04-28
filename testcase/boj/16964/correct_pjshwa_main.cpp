#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e5 + 1;
vector<int> edge[MAX];
int parent[MAX];
bool vis[MAX];

void dfs(int node) {
  vis[node] = true;

  for (auto dst : edge[node]) {
    if (!vis[dst]) {
      parent[dst] = node;
      dfs(dst);
    }
  }
}

int main() {
  fast_io();

  int n, a, b, c;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b;
    edge[a].push_back(b);
    edge[b].push_back(a);
  }
  dfs(1);

  cin >> c;
  if (c != 1) {
    cout << "0\n";
    return 0;
  }

  stack<int> trav;
  trav.push(1);

  for (int i = 0; i < n - 1; i++) {
    cin >> c;
    while (!trav.empty() && parent[c] != trav.top()) trav.pop();
    if (trav.empty()) {
      cout << "0\n";
      return 0;
    }
    trav.push(c);
  }

  cout << "1\n";
}
