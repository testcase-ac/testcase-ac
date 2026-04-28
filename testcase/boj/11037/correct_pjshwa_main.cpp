#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<int> U;
int L, cur;
bool vis[10];

void dfs(int i) {
  if (i == L) {
    U.push_back(cur);
    return;
  }

  int prv = cur;
  for (int j = 1; j <= 9; j++) {
    if (vis[j]) continue;

    vis[j] = true;
    cur = cur * 10 + j;
    dfs(i + 1);
    cur = prv;
    vis[j] = false;
  }
}

int main() {
  fast_io();

  for (L = 1; L <= 9; L++) dfs(0);

  int N;
  while (cin >> N) {
    auto it = upper_bound(U.begin(), U.end(), N);
    if (it == U.end()) cout << "0\n";
    else cout << *it << '\n';
  }
}
