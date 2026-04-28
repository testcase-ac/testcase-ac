#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int parent[51];
vector<int> party[50];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int main() {
  fast_io();

  int n, m, t, s, s0;
  cin >> n >> m;
  set<int> knowers;

  cin >> t;
  for (int i = 1; i <= t; i++) {
    cin >> s;
    knowers.insert(s);
  }
  for (int i = 1; i <= n; i++) parent[i] = i;
  for (int i = 0; i < m; i++) {
    cin >> t;
    for (int j = 0; j < t; j++) {
      cin >> s;
      party[i].push_back(s);
    }

    if (t) {
      for (int j = 1; j < t; j++) Union(party[i][0], party[i][j]);
    }
  }

  int cnt = 0;
  bool spreadable;
  for (int i = 0; i < m; i++) {
    spreadable = true;
    for (auto &g: party[i]) {
      for (auto &knower : knowers) {
        if (Find(knower) == Find(g)) spreadable = false;
      }
    }

    if (spreadable) cnt++;
  }

  cout << cnt << '\n';
}
