#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, K;
map<int, string> cache;
string cur = "";
int A[40];

void dfs1(int i, int sum) {
  if (i == N / 2) {
    cache[sum] = cur;
    return;
  }

  cur += '1';
  dfs1(i + 1, sum + A[i]);
  cur.pop_back();

  cur += '0';
  dfs1(i + 1, sum);
  cur.pop_back();
}

void dfs2(int i, int sum) {
  if (i == N) {
    if (cache.count(K - sum)) {
      cout << cache[K - sum] << cur << '\n';
      exit(0);
    }
    return;
  }

  cur += '1';
  dfs2(i + 1, sum + A[i]);
  cur.pop_back();

  cur += '0';
  dfs2(i + 1, sum);
  cur.pop_back();
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  cin >> K;

  dfs1(0, 0);
  dfs2(N / 2, 0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
