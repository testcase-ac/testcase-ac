#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50'000;
int S[MAXN];

void solve() {
  int N, M, D, L; cin >> N >> M >> D >> L;
  for (int i = 0; i < N; ++i) cin >> S[i];
  sort(S, S + N);

  vector<int> P[M]; int pi = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] - (int)P[pi].size() * D >= L) {
      P[pi].push_back(S[i]);
      pi = (pi + 1) % M;
    }
  }

  int ans = 0;
  for (auto& v : P) ans += v.size();
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
