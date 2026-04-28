#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int N, A[MAXN + 1], P[MAXN + 1], U[MAXN + 1];
int parent[MAXN + 1], usz[MAXN + 1], lb[MAXN + 1], rb[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x); y = Find(y);
  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
  lb[x] = min(lb[x], lb[y]);
  rb[x] = max(rb[x], rb[y]);
}

ll get(int l, int r) {
  int val = P[r] - P[l - 1];
  if (val % 10) val = val + 10 - (val % 10);
  return val;
}

bool is_used(int i) {
  if (i < 1 || i > N) return false;
  return U[i];
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    P[i] = P[i - 1] + A[i];
    parent[i] = i; usz[i] = 1;
    lb[i] = rb[i] = i;
  }

  vector<int> Q(N);
  for (int i = 0; i < N; ++i) cin >> Q[i];
  reverse(Q.begin(), Q.end());

  ll cur = 0, cnt = 0, ans = 0;
  for (int x : Q) {
    if (is_used(x - 1)) {
      if (is_used(x + 1)) {
        --cnt;
        cur -= get(lb[Find(x - 1)], rb[Find(x - 1)]);
        cur -= get(lb[Find(x + 1)], rb[Find(x + 1)]);
        Union(x - 1, x); Union(x, x + 1);
      } else {
        cur -= get(lb[Find(x - 1)], rb[Find(x - 1)]);
        Union(x - 1, x);
      }
    } else {
      if (is_used(x + 1)) {
        cur -= get(lb[Find(x + 1)], rb[Find(x + 1)]);
        Union(x, x + 1);
      } else {
        ++cnt;
      }
    }

    cur += get(lb[Find(x)], rb[Find(x)]);
    U[x] = 1;
    ans = max(ans, cur * cnt);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
