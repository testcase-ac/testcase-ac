#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXH = 10000;
int P[MAXH + 1];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= M; ++i) {
    int h1, h2; cin >> h1 >> h2;
    P[h1] = P[h2] = i;
  }

  deque<int> dq;
  for (int i = 1; i <= MAXH; ++i) {
    if (P[i] == 0) continue;
    dq.emplace_back(P[i]);
  }

  while (N--) {
    int f = dq.front(); dq.pop_front();
    dq.emplace_back(f);
  }
  cout << dq.back() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
