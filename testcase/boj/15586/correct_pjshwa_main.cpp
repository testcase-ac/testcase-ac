#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int ss[MAX + 1];
int parent[MAX + 1];
int ans[MAX];

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

  int n, q;
  cin >> n >> q;

  vector<tuple<int, int, int>> edges;
  vector<tuple<int, int, int>> queries;

  for (int i = 0; i < n - 1; i++) {
    int pi, qi, ri;
    cin >> pi >> qi >> ri;
    edges.emplace_back(-ri, pi, qi);
  }
  sort(edges.begin(), edges.end());

  for (int i = 0; i < q; i++) {
    int ki, vi;
    cin >> ki >> vi;
    queries.emplace_back(-ki, vi, i);
  }
  sort(queries.begin(), queries.end());

  for (int i = 1; i <= n; i++) parent[i] = i, ss[i] = 1;

  int p = 0;
  for (auto [ki, vi, opos] : queries) {
    ki = -ki;
    while (p < n && -get<0>(edges[p]) >= ki) {
      int x = get<1>(edges[p]), y = get<2>(edges[p]);
      ss[Find(x)] += ss[Find(y)];
      Union(x, y);
      p++;
    }
    ans[opos] = ss[Find(vi)] - 1;
  }

  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
}
