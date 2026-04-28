#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4000, BIAS = 2000;
int parent[MAX + 1];

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

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= MAX; i++) parent[i] = i;

  while (M--) {
    int a, b;
    cin >> a >> b;

    if (Find(a) == Find(b)) return cout << "0\n", void();
    Union(a, b + BIAS);
    Union(b, a + BIAS);
  }

  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
