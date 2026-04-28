#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXF = 1e4, MAXN = 300;
int dp[MAXF][MAXN], A[MAXN], Fc[MAXF];
vector<int> fs; int Fz, N;

bool rec(int fi, int c) {
  if (dp[fi][c] != -1) return dp[fi][c];

  int f = fs[fi], ret = 0;
  for (int j = 0; j < N; ++j) {
    int g = __gcd(A[j], f);
    int fj = lower_bound(fs.begin(), fs.end(), g) - fs.begin();

    if (c >= Fc[fj] || g == 1) continue;
    ret |= !rec(fj, c + 1);
  }

  return dp[fi][c] = ret;
}

void solve() {
  int X; cin >> N >> X;
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int i = 1; i * i <= X; ++i) {
    if (X % i) continue;
    fs.push_back(i);
    if (i * i != X) fs.push_back(X / i);
  }
  sort(fs.begin(), fs.end());

  Fz = fs.size();
  for (int i = 0; i < Fz; ++i) {
    int f = fs[i];
    for (int j = 0; j < N; ++j) {
      if (__gcd(A[j], f) == f) {
        ++Fc[i];
        // if (f == 3) {
        //   cout << "A[" << j << "] = " << A[j] << "\n";
        //   cout << "gcd with x = " << __gcd(A[j], X) << "\n";
        // }
      }
    }
    // cout << "f = " << f << ", Fc = " << Fc[i] << "\n";
  }

  memset(dp, -1, sizeof(dp));
  cout << (rec(Fz - 1, 0) ? "First" : "Second") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
