#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int A[MAXN], D[MAXN];
int L[MAXN], R[MAXN], H[MAXN];

void solve() {
  int N; cin >> N;
  int maxA = 0, maxi = 0, Lz = 0, Rz = 0;
  for (int i = 0; i < N; ++i) {
    string Ds; cin >> A[i] >> Ds;
    if (Ds == "L") L[Lz++] = A[i];
    else R[Rz++] = A[i], D[i] = 1;
    if (A[i] > maxA) maxA = A[i], maxi = i;
  }
  sort(L, L + Lz);
  sort(R, R + Rz);
  D[maxi] ? --Rz : --Lz;

  int ans = 0;
  for (int s = 0; s < N; ++s) {
    if (D[s] != D[maxi]) continue;
    H[s] = maxA; int cur = 1;
    {
      int Li = Lz, Ri = 0, maxH = 0;
      for (int i = 0; i < s; ++i) if (!D[i]) --Li;
      for (int i = 0; i < s; ++i) {
        if (D[i]) H[i] = R[Ri++];
        else {
          while (Li < Lz && L[Li] < maxH) ++Li;
          if (Li == Lz) break;
          H[i] = L[Li++]; ++cur;
        }
        maxH = max(maxH, H[i]);
      }
    }
    {
      int Li = 0, Ri = Rz, maxH = 0;
      for (int i = N - 1; i > s; --i) if (D[i]) --Ri;
      for (int i = N - 1; i > s; --i) {
        if (!D[i]) H[i] = L[Li++];
        else {
          while (Ri < Rz && R[Ri] < maxH) ++Ri;
          if (Ri == Rz) break;
          H[i] = R[Ri++]; ++cur;
        }
        maxH = max(maxH, H[i]);
      }
    }
    
    ans = max(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
