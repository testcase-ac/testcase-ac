#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5 + 1;
vector<int> graph[MAX];
int color[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  while (m--) {
    int x, y;
    cin >> x >> y;
    if (x > y) swap(x, y);
    graph[y].push_back(x);
  }

  color[1] = 1;
  for (int i = 2; i <= n; i++) {
    set<int> used;
    for (int j : graph[i]) {
      if (color[j] == 0) continue;
      used.insert(color[j]);
    }
    int c = 1;
    while (1) {
      if (!used.count(c)) break;
      c++;
    }
    color[i] = c;
  }

  for (int i = 1; i <= n; i++) {
    cout << color[i] << ' ';
  }
}
