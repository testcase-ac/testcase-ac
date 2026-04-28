#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_odd(int n) {
  return n & 1;
}

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

bool is_odd_prime(int n) {
  return is_odd(n) && is_prime(n);
}

void solve() {
  int N; cin >> N;
  if (is_prime(N)) {
    cout << "1\n" << N << '\n';
    return;
  }

  vector<int> R;
  if (N & 1) {
    R.push_back(3);
    N -= 3;
  }

  int h = N / 2;
  for (int i = 1;; ++i) {
    if (is_odd_prime(h + i) && is_odd_prime(h - i)) {
      R.push_back(h + i); R.push_back(h - i);
      break;
    }
  }

  cout << R.size() << '\n';

  sort(R.begin(), R.end());
  for (int r : R) cout << r << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
