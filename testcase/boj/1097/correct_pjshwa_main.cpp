#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N;

  string A[N]; int L = 0;
  for (int i = 0; i < N; ++i) cin >> A[i], L += A[i].size();
  cin >> K;

  int p[N], ans = 0; iota(p, p + N, 0);
  do {
    string S = "";
    for (int i = 0; i < N; ++i) S += A[p[i]];

    vector<int> pi(L);
    for (int i = 1, j = 0; i < L; i++) {
      while (j && S[i] != S[j]) j = pi[j - 1];
      if (S[i] == S[j]) pi[i] = ++j;
    }

    int P = pi.back();
    if (P % (L - P)) ans += (K == 1);
    else {
      int R = P / (L - P);
      ans += (R + 1 == K);
    }

  } while (next_permutation(p, p + N));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
