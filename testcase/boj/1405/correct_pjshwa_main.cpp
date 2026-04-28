#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int bias = 15;
int n;
long double pr[4], ans;
bool vis[32][32];
vector<int> current;

void dfs(int i, int j) {
  if (vis[i + bias][j + bias]) return;
  if (current.size() == n) {
    long double cp = 1;
    for (int k : current) cp *= pr[k];
    ans += cp;
    return;
  }

  vis[i + bias][j + bias] = 1;
  for (int k = 0; k < 4; k++) {
    current.push_back(k);
    if (k == 0) dfs(i, j + 1);
    if (k == 1) dfs(i, j - 1);
    if (k == 2) dfs(i + 1, j);
    if (k == 3) dfs(i - 1, j);
    current.pop_back();
  }
  vis[i + bias][j + bias] = 0;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < 4; i++) {
    cin >> pr[i];
    pr[i] /= 100;
  }

  dfs(0, 0);
  cout << fixed << setprecision(10) << ans;
}
