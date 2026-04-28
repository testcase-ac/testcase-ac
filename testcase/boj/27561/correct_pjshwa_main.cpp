#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int gc = 0, hc = 0;
  for (char& c : S) {
    if (c == 'G') gc++;
    if (c == 'H') hc++;
  }

  int gf, hf;
  for (int i = N; i >= 1; i--) {
    if (S[i - 1] == 'G') gf = i;
    if (S[i - 1] == 'H') hf = i;
  }

  int E[N + 1];
  for (int i = 1; i <= N; i++) cin >> E[i];

  int guc = 0, huc = 0;
  for (int i = gf; i <= E[gf]; i++) {
    if (S[i - 1] == 'G') guc++;
  }
  for (int i = hf; i <= E[hf]; i++) {
    if (S[i - 1] == 'H') huc++;
  }

  int gfv = gc == guc, hfv = hc == huc, both = gfv && hfv;
  int ans = both;
  for (int i = 1; i <= N; i++) {
    if (S[i - 1] == 'G') {
      if (hfv && i <= hf && hf <= E[i]) {
        if (!both || i != gf) ans++;
      }
    }
    else {
      if (gfv && i <= gf && gf <= E[i]) {
        if (!both || i != hf) ans++;
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
