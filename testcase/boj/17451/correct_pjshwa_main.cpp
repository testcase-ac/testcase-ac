#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  ll spd = A[N - 1];
  for (int i = N - 2; i >= 0; i--) {
    if (A[i] > spd) spd = A[i];
    else spd = (spd + A[i] - 1) / A[i] * A[i];
  }
  cout << spd << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
