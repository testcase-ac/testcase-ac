#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1];
bool vis[1 << 20];
int n;

vector<int> ans;

void dfs(int v) {
  vis[v] = 1;
  for (int i = 1; i <= n; i++) {
    int nxt = v ^ a[i];
    if (!vis[nxt]) {
      ans.push_back(i);
      dfs(nxt);
    }
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  dfs(0);
  cout << ans.size() << '\n';
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << '\n';
  }
}
