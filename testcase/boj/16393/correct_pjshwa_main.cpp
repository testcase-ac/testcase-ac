#include <bits/stdc++.h>
#define pii pair<int, int>
#define pipii pair<int, pair<int, int>>
using namespace std;

vector<int> graph[2501];
int parent[2501];

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

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, d;
  cin >> n;

  for (int i = 0; i < n; i++) parent[i] = i;

  vector<pipii> ws;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> d;
      if (i >= j) continue;
      ws.push_back({d, {i, j}});
    }
  }
  sort(ws.begin(), ws.end());

  int wgt, n1, n2;
  pii pos;
  for (auto &x : ws) {
    tie(wgt, pos) = x;
    tie(n1, n2) = pos;

    if (Find(n1) != Find(n2)) {
      Union(n1, n2);
      if (n1 < n2) graph[n1].push_back(n2);
      else graph[n2].push_back(n1);
    }
  }

  for (int i = 0; i < n; i++) {
    sort(graph[i].begin(), graph[i].end());
    for (auto &el : graph[i]) cout << i + 1 << ' ' << el + 1 << '\n';
  }
}
