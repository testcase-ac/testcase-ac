#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

const int MAX = 500;

int N;
void solve() {
  if (N & 1) {
    for (int i = 1; i <= MAX; i++) for (int j = i; j <= MAX; j++) for (int k = j; k <= MAX; k++) {
      if (is_prime(i) && is_prime(j) && is_prime(k) && i + j + k == N * N * N) {
        cout << i << ' ' << j << ' ' << k << '\n';
      }
    }

  }
  else {
    for (int i = 1; i <= MAX; i++) for (int j = i; j <= MAX; j++) {
      if (is_prime(i) && is_prime(j) && i + j == N * N * N) {
        cout << i << ' ' << j << '\n';
      }
    }

  }
  
}

int main() {
  fast_io();

  for (int t = 1; t <= 10; t++) {
    N = t;
    cout << "N = " << N << '\n';
    solve();
  }
}
