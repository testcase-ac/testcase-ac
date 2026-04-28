#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int Rs, Rh; cin >> Rs >> Rh;
  int U = (Rs + Rh) * (Rs + Rh);

  vector<pii> A;

  int N; cin >> N;
  for (int i = 1; i <= N; i++) {
    int x, y; cin >> x >> y;

    int d = x * x + y * y;
    if (d <= U) A.emplace_back(d, 0);
  }

  int M; cin >> M;
  for (int i = 1; i <= M; i++) {
    int x, y; cin >> x >> y;

    int d = x * x + y * y;
    if (d <= U) A.emplace_back(d, 1);
  }

  if (A.empty()) {
    cout << "0 0\n";
    return;
  }

  int nc = 0, mc = 0;

  sort(A.begin(), A.end());
  auto [_, P] = A[0];
  if (P) mc++;
  else nc++;

  for (int i = 1; i < A.size(); i++) {
    auto [d, p] = A[i];
    if (p != P) break;

    if (p) mc++;
    else nc++;
  }

  cout << nc << ' ' << mc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
