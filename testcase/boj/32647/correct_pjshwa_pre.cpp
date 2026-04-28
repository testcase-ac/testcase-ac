#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 50000, MAXT = 2e5;

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  // int A, B, K; cin >> A >> B >> K;

  for (int A = 1; A <= 1e9; ++A) {
    int B = A + 300;
    vector<int> C;
    for (int p = A; p <= B; ++p) {
      if (is_prime(p)) C.push_back(p);
    }
    int N = C.size();
    // if (N > 50) continue;

    int psum = 0;
    for (int c : C) psum += c - C[0];
    if (psum <= 7000) continue;
    cout << "A: " << A << ", B: " << B << ", N: " << N << ", psum: " << psum << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
