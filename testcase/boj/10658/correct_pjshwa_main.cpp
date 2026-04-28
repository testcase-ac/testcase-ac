#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, A, B; cin >> N >> A >> B;

  vector<pii> V;
  for (int i = 0; i < N; ++i) {
    string S; int W; cin >> S >> W;
    if (S == "S") V.emplace_back(W, 1);
    else V.emplace_back(W, 0);
  }
  sort(V.begin(), V.end());

  V.emplace(V.begin(), -1, V[0].second);
  V.emplace_back(INF, V.back().second);

  ll ans = 0;
  for (int i = 1; i < V.size(); ++i) {
    int px = V[i - 1].first, cx = V[i].first;
    if (A >= cx || px > B) continue;

    int ptype = V[i - 1].second, ctype = V[i].second;
    ans += ptype;

    int gap = cx - px - 1;
    ans += (gap / 2) * (ptype + ctype);
    if (gap & 1) {
      if (ptype == 1 || ctype == 1) ans += 1;
    }

    bool A_in = px <= A && A < cx, B_in = px <= B && B < cx;
    int half = (px + cx) / 2;

    if (A_in) {
      if (ptype == ctype) {
        if (ptype == 1) ans -= A - px;
      }
      else {
        // [px, half] [half + 1, cx)
        if (ptype == 1) {
          if (A > half) ans -= half - px + 1;
          else ans -= A - px;
        }
        else {
          // [px, half - 1] [half, cx)
          if (gap & 1) {
            if (A > half) ans -= A - half;
          }
          // [px, half] [half + 1, cx)
          else {
            if (A > half + 1) ans -= A - half - 1;
          }
        }
      }
    }
    if (B_in) {
      if (ptype == ctype) {
        if (ptype == 1) ans -= cx - B - 1;
      }
      else {
        // [px, half] [half + 1, cx)
        if (ptype == 1) {
          if (B < half) ans -= half - B;
        }
        else {
          // [px, half - 1] [half, cx)
          if (gap & 1) {
            if (B >= half) ans -= cx - B - 1;
            else ans -= cx - half;
          }
          // [px, half] [half + 1, cx)
          else {
            if (B > half) ans -= cx - B - 1;
            else ans -= cx - half - 1;
          }
        }
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
