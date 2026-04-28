#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  vector<int> xs, ys;
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    A[i] = {x, y};
    xs.push_back(x);
    ys.push_back(y);
  }

  vector<int> ans(N, INF);
  for (int X : xs) for (int Y : ys) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto [x, y] : A) {
      pq.push(abs(x - X) + abs(y - Y));
    }

    int acc = 0;
    for (int i = 0; i < N; i++) {
      acc += pq.top();
      pq.pop();
      ans[i] = min(ans[i], acc);
    }
  }

  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
