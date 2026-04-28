#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

const int MAXG = 60;
int G[MAXG + 1], S[MAXG + 1];

int get_grundy(ll x) {
  if (x == 0) return 0;

  vector<int> Gs;
  for (int d = 1; d <= x; ++d) {
    if (S[d]) continue;
    S[d] = 1;
    Gs.push_back(get_grundy(x - d));
    S[d] = 0;
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return mex;
}

void solve() {
  int N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ans ^= G[x];
  }
  if (ans) cout << "koosaga\n";
  else cout << "cubelover\n";
}

int main() {
  fast_io();

  for (int i = 1; i <= MAXG; ++i) {
    int j = 1;
    while (j * j + j <= i * 2) ++j;
    G[i] = j - 1;

    // G[i] = get_grundy(i);
    // cout << i << ' ' << G[i] << endl;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
