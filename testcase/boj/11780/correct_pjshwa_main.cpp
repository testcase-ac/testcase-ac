#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int cost[101][101];
int rout[101][101];
const int MAX = 1e9 + 7;
vector<int> v;

void get_route(int s, int e) {
  if (rout[s][e] == 0) {
    v.push_back(s);
    v.push_back(e);
  }
  else {
    get_route(s, rout[s][e]);
    v.pop_back();
    get_route(rout[s][e], e);
  }
}

int main() {
  fast_io();

  int n, m, a, b, c;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) cost[i][j] = MAX;
    }
  }

  while (m--) {
    cin >> a >> b >> c;
    if (c < cost[a][b]) cost[a][b] = c;
  }

  // Floyd-warshall
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (cost[i][k] + cost[k][j] < cost[i][j]) {
          cost[i][j] = cost[i][k] + cost[k][j];
          rout[i][j] = k;
        }
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (cost[i][j] == MAX) cost[i][j] = 0;
      cout << cost[i][j] << ' ';
    }
    cout << '\n';
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (cost[i][j] == 0) cout << "0\n";
      else {
        v.clear();
        get_route(i, j);

        cout << v.size() << ' ';
        for (auto ve : v) cout << ve << ' ';
        cout << '\n';
      }
    }
  }
}
