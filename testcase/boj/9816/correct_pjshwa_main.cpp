#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll N, cnt;
vector<int> cur;
ll d[17] = {
  0,
  0,
  0,
  8,
  64,
  360,
  1776,
  8216,
  36640,
  159624,
  684240,
  2898296,
  12164608,
  50687208,
  209961648,
  865509848,
  3553389280
};

void dfs(int i) {
  if (i == N) {
    bool f = false;
    set<int> u;
    for (int i = 0; i < N - 1; i++) {
      f |= (abs(cur[i] - cur[i + 1]) == 3);
    }
    for (int i = 0; i < N; i++) u.insert(cur[i]);
    f &= (u.size() >= 3);

    if (f) cnt++;
    return;
  }

  for (int v : {1, 2, 3, 4}) {
    cur.push_back(v);
    dfs(i + 1);
    cur.pop_back();
  }
}

int n;
void solve() {
  cout << n << ": " << d[n] << '\n';
}

int main() {
  fast_io();

  // for (N = 2; N <= 16; N++) {
  //   cnt = 0;
  //   dfs(0);
  //   cout << "N = " << N << ", cnt = " << cnt << endl;
  //   d[N] = cnt;
  // }

  while (cin >> n) {
    if (n == -1) break;
    solve();
  }
}
