#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, U, L; cin >> N >> U >> L;
  int P = (U - L) * 100;

  vector<pii> A;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    A.emplace_back(x, i);
  }
  sort(A.begin(), A.end(), greater<pii>());

  int rank = (N - 1) / 12, cut1, cut2 = A[rank].first;
  if (P == 0) cut1 = cut2;
  else cut1 = rank < N - 1 ? A[rank + 1].first : -P;

  vector<int> P1, P2;
  for (auto& [x, i] : A) {
    if (x - P >= cut1) P1.push_back(i);
    if (x + P >= cut2) P2.push_back(i);
  }

  sort(P1.begin(), P1.end());
  sort(P2.begin(), P2.end());
  for (int e : P1) cout << e << '\n';
  cout << "--------\n";
  for (int e : P2) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
