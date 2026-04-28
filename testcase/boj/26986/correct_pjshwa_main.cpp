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

const int MAXV = 10000;
vector<pii> A; vector<int> xs;
int C;

bool check(int S) {

  vector<int> P;
  for (int x : xs) {

    P.clear(); int Z = 0;
    for (auto& [cx, cy] : A) {
      if (cx >= x && cx <= x + S) P.push_back(cy), ++Z;
    }
    sort(P.begin(), P.end());

    // cout << "x = " << x << ", S = " << S << ", P: ";
    // for (int p : P) cout << p << ' ';
    // cout << '\n';

    for (int ll = 0, rr = 0; ll < Z; ++ll) {
      while (rr < Z && P[rr] - P[ll] <= S) ++rr;
      if (rr - ll >= C) return true;
    }

  }

  return false;
}

void solve() {
  int N; cin >> C >> N;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
    xs.push_back(x);
  }
  sort(A.begin(), A.end());
  compress(xs);

  int l = 0, r = 1e4 + 1;
  while (l < r) {
    int S = (l + r) / 2;
    if (check(S)) r = S;
    else l = S + 1;
  }
  cout << l + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
