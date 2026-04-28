#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2500, INF = 0x3f3f3f3f;

void solve() {
  string S, A[4]; cin >> S >> A[0] >> A[1] >> A[2] >> A[3];
  int N = S.size();

  vector<int> P[4];
  for (int i = 0; i < N; ++i) {
    // check if S[i..] starts with A[j]
    for (int j = 0; j < 4; ++j) {
      if (S.substr(i, A[j].size()) == A[j]) {
        P[j].push_back(i);
      }
    }
  }

  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
