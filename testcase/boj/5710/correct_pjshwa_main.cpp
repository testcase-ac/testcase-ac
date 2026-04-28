#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int A, B;
const int d1 = 200, d2 = d1 + 3 * 9900, d3 = d2 + 5 * 990000;

int f(int use) {
  if (use <= 100) return 2 * use;
  if (use <= 10000) return d1 + 3 * (use - 100);
  if (use <= 1000000) return d2 + 5 * (use - 10000);
  return d3 + 7 * (use - 1000000);
}

void solve() {
  int W;
  if (A > d3) W = (A - d3) / 7 + 1000000;
  else if (A > d2) W = (A - d2) / 5 + 10000;
  else if (A > d1) W = (A - d1) / 3 + 100;
  else W = A / 2;

  int left = 0, right = W / 2 + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    if (f(W - mid) - f(mid) > B) left = mid + 1;
    else right = mid;
  }

  cout << f(left) << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> A >> B;
    if (A == 0 && B == 0) break;
    solve();
  }
}
