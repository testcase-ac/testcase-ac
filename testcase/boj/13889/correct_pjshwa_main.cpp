#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 60, MAXV = 12000, MOD = 1e9 + 7;

int N, F;
void solve() {
}

int main() {
  fast_io();

  while (cin >> N >> F) {
    if (N == 0 && F == 0) break;
    solve();
  }
}
