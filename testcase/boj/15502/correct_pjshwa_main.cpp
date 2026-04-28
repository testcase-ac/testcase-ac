#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int parent[1001];

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

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) parent[i] = i;

  while (m--) {
    int li, ri, ki;
    cin >> li >> ri >> ki;
    for (int i = li; i + ki <= ri; i++) Union(i, i + ki);
  }

  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    if (Find(i) == i) ans = (ans * 2) % 1000000007;
  }
  cout << ans << '\n';
}
