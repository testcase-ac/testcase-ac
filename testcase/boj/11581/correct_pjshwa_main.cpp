#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
vector<int> graph[MAX + 1];
int vis[MAX + 1];

bool dfs(int here) {
  if (vis[here]) return vis[here] == -1;
  
  vis[here] = -1;
  for (int there : graph[here]) {
    if (dfs(there)) return true;
  }
  vis[here] = 1;
  return false;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N - 1; i++) {
    int Mi;
    cin >> Mi;
    while (Mi--) {
      int Ci;
      cin >> Ci;
      graph[i].push_back(Ci);
    }
  }

  if (dfs(1)) cout << "CYCLE\n";
  else cout << "NO CYCLE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
