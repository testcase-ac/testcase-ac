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
int G[MAXG + 1];

void solve() {
  ll K, T; cin >> K >> T;
  while (T--) {
    ll a, b; cin >> a >> b;

    ll nxt = a - 1, ans = 0;
    while (nxt < b) {
      ll hgt = 0;
      while (1) {
        if (nxt & (1LL << hgt)) break;
        if (nxt + (1LL << (hgt + 1)) > b) break;
        ++hgt;
      }
      // cout << "nxt: " << nxt << ", hgt: " << hgt << '\n';
      ans ^= G[hgt + 1];
      nxt += (1LL << hgt);
    }
    assert(nxt == b);

    if (ans) cout << "swlee0202\n";
    else cout << "mj1000j\n";
  }
}

int main() {
  fast_io();

  G[1] = 1;
  for (int i = 2; i <= MAXG; ++i) {
    vector<int> Gs{0}; int t = 0;
    for (int j = i - 1; j >= 1; --j) {
      t ^= G[j];
      Gs.push_back(t);
    }
    compress(Gs);

    // calculate mex of Gs
    int mex = 0;
    for (int g : Gs) {
      if (g == mex) ++mex;
    }
    G[i] = mex;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
