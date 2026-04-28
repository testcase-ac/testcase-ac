#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll sum = 0;
priority_queue<int, vector<int>, greater<int>> pq;
int H, N, Q;

void flush() {
  while (!pq.empty() && sum - pq.top() >= H) {
    sum -= pq.top();
    pq.pop();
  }
}

void print_ans() {
  if (sum < H) cout << "-1\n";
  else cout << pq.size() << '\n';
}

void solve() {
  cin >> H >> N >> Q;

  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    pq.push(x); sum += x;
  }
  flush(); print_ans();

  while (Q--) {
    int x; cin >> x;
    pq.push(x); sum += x;
    flush(); print_ans();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
