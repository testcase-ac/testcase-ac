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

const int MAXN = 1000;
int K, dp[MAXN + 1];
int Gp[11] = {0, 1, 0, 1, 2, 0, 2, 0, 1, 0, 1};

// int rec(int i) {
//   if (i == 0) return 0;
//   if (dp[i] != -1) return dp[i];

//   vector<int> Gs{rec(i - 1)};
//   if (i % 2 == 0) {
//     Gs.push_back(rec(K * (i / 2)));
//   }
//   compress(Gs);

//   // calculate mex of Gs
//   int mex = 0;
//   for (int g : Gs) {
//     if (g == mex) ++mex;
//   }
//   return dp[i] = mex;
// }

int G(int i) {
  if (K) {
    if (i <= 10) return Gp[i];
    else {
      if (i & 1) return 0;
      else return 1 + (G(i / 2) == 1);
    }
  }
  else {
    if (i <= 2) return i;
    else return 1 - (i & 1);
  }
}

void solve() {
  int N, ans = 0; cin >> N >> K;
  K &= 1;

  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ans ^= G(x);
  }
  cout << (ans ? "Kevin" : "Nicky") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
