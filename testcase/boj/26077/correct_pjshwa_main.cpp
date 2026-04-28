#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e6;
int a[MAX + 1];
int parent[MAX + 1], usz[MAX + 1], lp[MAX + 1];
vector<int> pr;

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

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], usz[a[i]]++;
  for (int i = 2; i <= MAX; i++) parent[i] = i;

  for (int i = 1; i <= n; i++) {
    int x = a[i];
    while (x > 1) {
      Union(lp[x], a[i]);
      x /= lp[x];
    }
  }

  int ans = 0;
  for (int i = 2; i <= MAX; i++) ans = max(ans, usz[Find(i)]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
