#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> children[(size_t)1e5];
int scores[(size_t)1e5];

void dfs(int node) {
  for (int &dst : children[node]) {
    scores[dst] += scores[node];
    dfs(dst);
  }
}

int main() {
  fast_io();

  int n, m, ii, w;
  cin >> n >> m;

  cin >> w; // boss
  for (int i = 1; i < n; i++) {
    cin >> w;
    children[w - 1].push_back(i);
  }

  for (int i = 0; i < m; i++) {
    cin >> ii >> w;
    scores[ii - 1] += w;
  }

  dfs(0);

  for (int i = 0; i < n; i++) cout << scores[i] << ' ';
  cout << '\n';
}
