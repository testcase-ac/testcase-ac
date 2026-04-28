#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ccw(pii& a, pii& b, pii& c) {
  int u = (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
  if (u > 0) return 1;
  else if (u == 0) return 0;
  else return -1;
}

int N;
void solve() {
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }

  // sort clockwise
  sort(A.begin(), A.end(), [&](pii& a, pii& b) {
    int u = ccw(A[0], a, b);
    if (u == 0) return a < b;
    return u > 0;
  });

  cout << "A = ";
  for (auto& a : A) cout << "(" << a.first << ", " << a.second << ") ";
  cout << '\n';

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    int dx = A[i].first - A[i - 1].first;
    int dy = A[i].second - A[i - 1].second;
    ans += dx + dy;
  }
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
