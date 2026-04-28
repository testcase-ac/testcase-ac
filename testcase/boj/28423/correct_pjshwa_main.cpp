#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int parent[MAX + 10];

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
  iota(parent, parent + MAX + 10, 0);

  for (int i = 1; i <= MAX; i++) {
    string s = to_string(i);

    int sum = 0, mul = 1;
    for (char c : s) {
      int d = c - '0';
      sum += d; mul *= d;
    }

    int t = stoi(to_string(sum) + to_string(mul));
    if (t > MAX) Union(i, MAX + 1);
    else {
      if (i == t) Union(i, 0);
      Union(i, t);
    }
  }

  int L, R, ans = 0; cin >> L >> R;
  for (int i = L; i <= R; i++) {
    if (Find(i) == Find(MAX + 1)) ans--;
    else if (Find(i) == Find(0)) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
