#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int V[MAXN + 1];

void solve() {
  int N, mex = 1; cin >> N;

  vector<int> U;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    V[x] = 1;
    while (V[mex]) ++mex;
    if (mex == i + 1) U.push_back(i);
  }
  fill(V + 1, V + N + 1, 0);

  U.pop_back();
  cout << U.size() << '\n';
  for (int x : U) cout << x << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
