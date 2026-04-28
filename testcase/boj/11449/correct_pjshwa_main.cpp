#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int O[MAX], D[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> O[i] >> D[i];

  ll md = -1e18, cd = 0, co = 0;
  for (int i = 0; i < N; i++) {
    co += O[i];
    cd += D[i];
    md = max(md, cd - co);
  }

  ll cs = 0;
  for (int i = 0; i < N; i++) {
    cs += (D[i] - O[i]);
    if (md == cs) return cout << i + 1 << '\n', void();
  }

  cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
