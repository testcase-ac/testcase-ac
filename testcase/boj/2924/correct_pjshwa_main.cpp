#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 5e5, LIM = 1e12;
int parent[MAXN + 1], usz[MAXN + 1];

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

ll upto(ll n) {

}

void solve() {
  ll N, A, B, C, D, x; cin >> N >> A >> B >> C >> D; --A; --B;
  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);
  for (int i = 1; i <= N; ++i) cin >> x, Union(i, x);

  ll l = 1;
  for (int i = C + 1; i <= N - D; ++i) {
    l = lcm(l, usz[Find(i)]);
    if (l > B) break;
  }

  auto upto = [&](ll n) {
    if (n < 0) return 0LL;
    return 1 + n / l;
  };
  cout << upto(B) - upto(A - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
