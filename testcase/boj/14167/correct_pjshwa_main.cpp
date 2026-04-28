#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
ll parent[MAX + 1], usz[MAX + 1], Xs[MAX + 1], Ys[MAX + 1];

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
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> Xs[i] >> Ys[i];

  ll left = 0, right = 1e18;
  while (left < right) {
    ll mid = (left + right) / 2;
  
    iota(parent, parent + N + 1, 0);
    fill(usz, usz + N + 1, 1);
    for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) {
      ll dist = (Xs[i] - Xs[j]) * (Xs[i] - Xs[j]) + (Ys[i] - Ys[j]) * (Ys[i] - Ys[j]);
      if (dist <= mid) Union(i, j);
    }

    if (usz[Find(1)] == N) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
