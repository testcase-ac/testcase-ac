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

  int J, P, S, K;
  cin >> J >> P >> S >> K;

  if (S >= K) {
    cout << J * P * K << '\n';
    for (int j = 0; j < J; ++j) {
      for (int p = 0; p < P; ++p) {
        for (int k = 0; k < K; ++k) {
          cout << j + 1 << ' ' << p + 1 << ' ' << (j + p + k) % S + 1 << '\n';
        }
      }
    }
  }
  else {
    cout << J * P * S << '\n';
    for (int j = 0; j < J; ++j) {
      for (int p = 0; p < P; ++p) {
        for (int s = 0; s < S; ++s) {
          cout << j + 1 << ' ' << p + 1 << ' ' << s + 1 << '\n';
        }
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
