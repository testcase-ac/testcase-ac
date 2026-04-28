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

const int MAXN = 10000;
int G[MAXN + 1];

int K;
void solve() {
  vector<int> S;
  while (K--) {
    int x; cin >> x;
    S.push_back(x);
  }
  sort(S.begin(), S.end());

  for (int i = 1; i <= MAXN; ++i) {
    vector<int> Gs;
    for (int s : S) {
      if (i < s) break;
      Gs.push_back(G[i - s]);
    }
    compress(Gs);

    // calculate mex of Gs
    int mex = 0;
    for (int g : Gs) {
      if (g == mex) ++mex;
      else break;
    }
    G[i] = mex;
  }

  int T; cin >> T;
  while (T--) {
    int L, ans = 0; cin >> L;
    while (L--) {
      int x; cin >> x;
      ans ^= G[x];
    }
    cout << (ans ? 'W' : 'L');
  }
  cout << '\n';
}

int main() {
  fast_io();

  while (cin >> K) {
    if (K == 0) break;
    solve();
  }
}
