#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 3e6;
int pre[MAXV + 1];

void solve() {
  int N, M; string S; cin >> N >> M >> S;

  int Li = -1, Ri = -1, sum = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'W') sum += 1;
    else sum += 2;
  }
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'T') continue;
    if (Li == -1) Li = i;
    Ri = i;
  }

  if (Li == -1) {
    while (M--) {
      int x; cin >> x;
      if (x % 2 == 1 || x > sum) cout << "NIE\n";
      else cout << "1 " << x / 2 << "\n";
    }
  }
  else {
    int Ld = Li, Rd = N - 1 - Ri, flip = 0;
    if (Ld > Rd) {
      reverse(S.begin(), S.end()); flip = 1;
      Li = -1, Ri = -1;
      for (int i = 0; i < N; ++i) {
        if (S[i] == 'T') continue;
        if (Li == -1) Li = i;
        Ri = i;
      }
    }

    memset(pre, -1, sizeof(pre));
    pre[1] = Li + 1; int acc = 1;
    for (int i = Li + 1; i < N; ++i) {
      if (S[i] == 'W') acc += 1;
      else acc += 2;
      pre[acc] = i + 1;
    }

    vector<pii> ans;
    while (M--) {
      int x; cin >> x;
      if (x > sum) ans.emplace_back(-1, -1);
      else if (x > sum - 2 * Li && (x % 2 != sum % 2)) ans.emplace_back(-1, -1);
      else {
        if (pre[x] != -1) ans.emplace_back(Li + 1, pre[x]);
        else if (pre[x + 1] != -1) ans.emplace_back(Li + 2, pre[x + 1]);
        else {
          int dif = x - acc;
          assert(dif % 2 == 0);
          ans.emplace_back(Li + 1 - dif / 2, N);
        }
      }
    }

    for (auto& [s, e] : ans) {
      if (s == -1) cout << "NIE\n";
      else if (flip) cout << N - e + 1 << " " << N - s + 1 << "\n";
      else cout << s << " " << e << "\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
