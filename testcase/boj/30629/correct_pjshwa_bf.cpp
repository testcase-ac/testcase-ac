#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, M;
vector<int> cur;

void dfs(int i) {
  if (i == N) {
    set<int> range_sums;
    for (int i = 0; i < N; ++i) {
      int sum = 0;
      for (int j = i; j < N; ++j) {
        sum += cur[j];
        range_sums.insert(sum);
      }
    }

    for (int i = 0; i <= M; ++i) {
      if (!range_sums.count(i)) return;
    }
    if (range_sums.size() == M + 1) {
      for (int v : cur) cout << v << " ";
      cout << "\n";
      exit(0);
    }
  }
  else {
    for (int v = 0; v <= 8; ++v) {
      cur.push_back(v);
      dfs(i + 1);
      cur.pop_back();
    }
  }

}

void solve() {
  cin >> N >> M;
  dfs(0);
  cout << -1 << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
