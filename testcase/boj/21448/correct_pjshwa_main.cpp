#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
int parent[MAXN], usz[MAXN];

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
  vector<pii> S;
  for (int i = 0; i < N; ++i) {
    int s, t; cin >> s >> t;
    S.emplace_back(s, s + t);
  }

  iota(parent, parent + N, 0);
  fill(usz, usz + N, 1);

  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    auto [s1, e1] = S[i]; auto [s2, e2] = S[j];
    if (s1 < e2 && s2 < e1) Union(i, j);
  }

  vector<int> sizes;
  for (int i = 0; i < N; ++i) {
    if (Find(i) == i) sizes.push_back(usz[i]);
  }
  cout << "sizes: ";
  for (int s : sizes) cout << s << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
