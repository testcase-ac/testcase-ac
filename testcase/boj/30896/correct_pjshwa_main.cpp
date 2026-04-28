#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;
  vector<pii> A;

  int tot = 0;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
    tot += y;
  }
  sort(A.begin(), A.end());

  int ans = INF;
  vector<int> S; S.push_back(0);

  int At = A[0].first, Apre = At * tot, acc = 0;
  for (int i = N - 1; i >= 1; --i) {
    int Bt = A[i].first, v = A[i].second;
    Apre -= At * v;
    int Bpre = Bt * v;

    for (int e : S) {
      int Asum = e, Bsum = acc - e;
      // cout << "e = " << e << ", Asum = " << Asum << ", Bsum = " << Bsum << '\n';
      ans = min(ans, abs(Apre - Bpre + Asum * At - Bsum * Bt));
    }

    vector<int> nS;
    for (int e : S) {
      nS.push_back(e);
      nS.push_back(e + v);
    }
    sort(nS.begin(), nS.end());
    nS.erase(unique(nS.begin(), nS.end()), nS.end());
    swap(S, nS); acc += v;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
