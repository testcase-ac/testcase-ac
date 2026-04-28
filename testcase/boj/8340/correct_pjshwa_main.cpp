#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
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
  int N;
  cin >> N;
  vector<vector<int>> A(N, vector<int>(2));
  for (int i = 0; i < N; i++) cin >> A[i][0];
  for (int i = 0; i < N; i++) cin >> A[i][1];

  for (int i = 1; i <= N; i++) parent[i] = i;
  for (int i = 0; i < N; i++) Union(A[i][0], A[i][1]);

  set<int> u;
  for (int i = 1; i <= N; i++) u.insert(Find(i));
  cout << (1LL << u.size()) << '\n';
}
 
int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}