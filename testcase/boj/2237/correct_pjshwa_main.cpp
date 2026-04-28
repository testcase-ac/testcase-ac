#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, MAXV = 50000, BIAS = 25000;
bool d[MAX + 1][MAXV + 1];
int A[MAX + 1], N, T;

void solve() {
  cin >> N >> T;
  for (int i = 0; i < N; i++) cin >> A[i];
  if (N == 1) return;

  d[1][A[0] - A[1] + BIAS] = 1;
  for (int i = 2; i < N; i++) {
    for (int v = 0; v <= MAXV; v++) {
      if (v >= A[i]) d[i][v] |= d[i - 1][v - A[i]];
      if (v + A[i] <= MAXV) d[i][v] |= d[i - 1][v + A[i]];
    }
  }

  vector<int> ops;
  int now = T + BIAS;
  assert(d[N - 1][now]);

  for (int i = N - 1; i >= 2; i--) {
    if (d[i - 1][now + A[i]]) {
      ops.push_back(0);
      now += A[i];
    }
    else if (d[i - 1][now - A[i]]) {
      ops.push_back(1);
      now -= A[i];
    }
  }
  assert(now == A[0] - A[1] + BIAS);

  ops.push_back(0);
  reverse(ops.begin(), ops.end());

  int minus_cnt = 0, plus_cnt = 0;
  while (!ops.empty()) {
    if (ops.back()) plus_cnt++;
    else {
      while (plus_cnt) cout << ops.size() + 1 << '\n', plus_cnt--;
      minus_cnt++;
    }
    ops.pop_back();
  }
  while (minus_cnt) cout << "1\n", minus_cnt--;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
