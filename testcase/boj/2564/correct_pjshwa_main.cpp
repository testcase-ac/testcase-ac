#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int X, Y;

int dist(pii A, pii B) {
  auto [ao, ax] = A;
  auto [bo, bx] = B;

  if (ao == bo) return abs(ax - bx);

  if (ao > bo) {
    swap(ao, bo);
    swap(ax, bx);
  }

  if (ao == 1) {
    if (bo == 2) return min(ax + bx, 2 * X - ax - bx) + Y;
    if (bo == 3) return min(ax + bx, 2 * (X + Y) - ax - bx);
    if (bo == 4) return min(X - ax + bx, ax + Y - bx + X + Y);
  }
  if (ao == 2) {
    if (bo == 3) return min(ax + Y - bx, bx + X - ax + X + Y);
    if (bo == 4) return min(X - ax + Y - bx, ax + bx + X + Y);
  }
  if (ao == 3) {
    if (bo == 4) return min(ax + bx + X, 2 * Y - ax - bx + X);
  }

}

void solve() {
  int N;
  cin >> X >> Y >> N;

  vector<pii> A(N);
  for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;

  int co, cx, ans = 0;
  cin >> co >> cx;
  for (int i = 0; i < N; i++) ans += dist(A[i], {co, cx});

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
