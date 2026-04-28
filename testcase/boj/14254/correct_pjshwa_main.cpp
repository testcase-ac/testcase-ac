#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50, INF = 0x3f3f3f3f;
int parent[MAX];

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
  string S; int K; cin >> S >> K;

  int N = S.size();
  iota(parent, parent + N, 0);
  for (int i = 0; i < K; i++) Union(i, i + N - K);

  map<int, vector<int>> by_group;
  for (int i = 0; i < N; i++) by_group[Find(i)].push_back(i);

  int ans = 0;
  for (auto& [_, v] : by_group) {
    map<int, int> tally;
    for (int i : v) tally[S[i]]++;

    int maxv = 0;
    for (auto& [_, v] : tally) maxv = max(maxv, v);

    ans += v.size() - maxv;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
